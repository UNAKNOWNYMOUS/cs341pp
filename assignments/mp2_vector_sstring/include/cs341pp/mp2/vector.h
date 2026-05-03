// Copyright 2026  Ahssan Javed  UNAKNOWNYMOUS@protonmail.com
//
// Description: This file provides my own short implementation of the vector
// class
//
// Project:
// https://github.com/UNAKNOWNYMOUS/cs341pp/tree/main/assignments/mp2_vector_sstring
#ifndef CS341PP_MP2_VECTOR_H_
#define CS341PP_MP2_VECTOR_H_

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

namespace cs341pp::mp2 {

template <typename T> class Vector {
public:
  // Implementing Rule of 5
  Vector() = default;
  ~Vector() { ClearAndFree_(); }

  Vector(const Vector &other) { CopyFrom_(other); }
  Vector &operator=(const Vector &other) {
    // self assignment guard
    if (this != &other) {
      ClearAndFree_();
      CopyFrom_(other);
    }
    return *this;
  }

  Vector(Vector &&other) noexcept { MoveFrom_(std::move(other)); }
  Vector &operator=(Vector &&other) noexcept {
    // self assignment guard
    if (this != &other) {
      ClearAndFree_();
      MoveFrom_(std::move(other));
    }
    return *this;
  }

  std::size_t size() const { return size_; }
  std::size_t capacity() const { return capacity_; }
  bool empty() const { return size_ == 0; }

  // Overloading operator for mutable and immutable objects
  T &operator[](std::size_t i) { return data_[i]; }
  const T &operator[](std::size_t i) const { return data_[i]; }

  // Overloading operator for mutable and immutable objects
  T &at(std::size_t i) {
    assert(i < size_);
    return data_[i];
  }
  const T &at(std::size_t i) const {
    assert(i < size_);
    return data_[i];
  }

  // Iterators (will allow me to do a for each loop)
  T *begin() { return data_; }
  T *end() { return data_ == nullptr ? nullptr : data_ + size_; }
  const T *begin() const { return data_; }
  const T *end() const { return data_ == nullptr ? nullptr : data_ + size_; }

  void push_back(const T &value) { PushBackImpl_(value); }

  // Using 'std::move' because even though value is an r-value in C++ a name is
  // an l-value so it will trigger a copy when passed elsewhere
  void push_back(T &&value) { PushBackImpl_(std::move(value)); }

  void pop_back() {
    assert(size_ > 0);
    std::allocator_traits<std::allocator<T>>::destroy(alloc_,
                                                      data_ + size_ - 1);
    --size_;
  }

  void clear() {
    if (data_ != nullptr) {
      for (std::size_t i{}; i < size_; ++i) {
        std::allocator_traits<std::allocator<T>>::destroy(alloc_, data_ + i);
      }
      size_ = 0;
    }
  }

  void reserve(std::size_t new_cap) {
    if (new_cap > capacity_) {
      EnsureCapacityFor_(new_cap);
    }
  }

  // TODO: Write comment explaining why using list initializer that assignment
  // r-value to l-value const ref i.e. it is efficient
  void resize(std::size_t new_size, const T &value = T{}) {
    if (new_size > capacity_) {
      EnsureCapacityFor_(new_size);
    }
    // smaller
    while (size_ > new_size) {
      std::allocator_traits<std::allocator<T>>::destroy(alloc_,
                                                        data_ + size_ - 1);
      --size_;
    }
    // bigger
    while (size_ < new_size) {
      std::allocator_traits<std::allocator<T>>::construct(
          alloc_, data_ + size_++, value);
    }
  }

  // Does not support r-value inserts
  void insert(std::size_t index, const T &value) {
    assert(index <= size_);
    // AI said that value maybe be somewhere inside the vector and when I
    // shift/destroy - this may effect the referenced object
    const T temp_value = value;
    EnsureCapacityFor_(size_ + 1);
    for (std::size_t i{size_}; i > index; --i) {
      std::allocator_traits<std::allocator<T>>::construct(
          alloc_, data_ + i, std::move(data_[i - 1]));
      std::allocator_traits<std::allocator<T>>::destroy(alloc_, data_ + i - 1);
    }
    std::allocator_traits<std::allocator<T>>::construct(alloc_, data_ + index,
                                                        temp_value);
    ++size_;
  }

  void erase(std::size_t index) {
    assert(index < size_);
    for (std::size_t i{index}; i < size_ - 1; ++i) {
      data_[i] = std::move(data_[i + 1]);
    }
    std::allocator_traits<std::allocator<T>>::destroy(alloc_,
                                                      data_ + size_ - 1);
    --size_;
  }

private:
  // Evaluated at compile time
  static constexpr std::size_t kInitialCapacity = 8;

  template <typename U>
  void PushBackImpl_(U &&value) { // type is being deduced - forwarding refernce
    EnsureCapacityFor_(size_ + 1);

    // Add element
    std::allocator_traits<std::allocator<T>>::construct(
        alloc_, data_ + size_++,
        std::forward<U>(
            value)); // perfect forwarding - using universal/forwarding refernce
  }

  void ClearAndFree_() {
    if (data_ != nullptr) {
      for (std::size_t i{}; i < size_; ++i) {
        std::allocator_traits<std::allocator<T>>::destroy(alloc_, data_ + i);
      }
      alloc_.deallocate(data_, capacity_);
    }
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  void CopyFrom_(const Vector &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (other.capacity_ != 0) {
      data_ = alloc_.allocate(other.capacity_);
    }
    for (std::size_t i{}; i < other.size_; ++i) {
      std::allocator_traits<std::allocator<T>>::construct(alloc_, data_ + i,
                                                          other[i]);
    }
  }

  void MoveFrom_(Vector &&other) {
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  void EnsureCapacityFor_(std::size_t desired_capacity) {
    if (desired_capacity <= capacity_) {
      return;
    }

    std::size_t new_capacity = capacity_;
    if (!new_capacity) {
      new_capacity = kInitialCapacity;
    }

    while (new_capacity < desired_capacity) {
      new_capacity *= 2;
    }

    ReallocateTo_(new_capacity);
  }

  void ReallocateTo_(std::size_t new_capacity) {
    T *new_data{alloc_.allocate(new_capacity)};
    for (std::size_t i{}; i < size_; ++i) {
      std::allocator_traits<std::allocator<T>>::construct(alloc_, new_data + i,
                                                          std::move(data_[i]));
      std::allocator_traits<std::allocator<T>>::destroy(alloc_, data_ + i);
    }
    if (data_ != nullptr) {
      alloc_.deallocate(data_, capacity_);
      data_ = nullptr;
    }
    data_ = new_data;
    capacity_ = new_capacity;
  }

  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::allocator<T> alloc_; // stateless - does not store anything "personal"
                            // that effects how it functions
};

} // namespace cs341pp::mp2

#endif
