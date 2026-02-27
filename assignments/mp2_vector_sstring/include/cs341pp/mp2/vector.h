#ifndef CS341PP_MP2_VECTOR_H_
#define CS341PP_MP2_VECTOR_H_

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

namespace cs341pp::mp2 {

template <typename T> class Vector {
public:
  /* Using default no args constructor */
  Vector() = default;
  /* Destructor */
  ~Vector() { ClearAndFree_(); }

  /* Copy Constructor */
  Vector(const Vector &other) { CopyFrom_(other); }
  /* Copy Assignment Operator */
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      ClearAndFree_();
      CopyFrom_(other);
    }
    return *this;
  }

  /* Move Constructor */
  Vector(Vector &&other) noexcept { MoveFrom_(std::move(other)); }
  /* Move assignment operator */
  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      ClearAndFree_();
      MoveFrom_(std::move(other));
    }
    return *this;
  }

  /* getter: size */
  std::size_t size() const { return size_; }
  /* getter: capacity */
  std::size_t capacity() const { return capacity_; }
  /* determines if vector is empty */
  bool empty() const { return size_ == 0; }

  /* Subscripting operator */
  T &operator[](std::size_t i) { return data_[i]; }
  /* readonly */
  const T &operator[](std::size_t i) const { return data_[i]; }

  T &at(std::size_t i) {
    assert(i < size_);
    return data_[i];
  }
  const T &at(std::size_t i) const {
    assert(i < size_);
    return data_[i];
  }

  T *begin() { return data_; }
  T *end() { return data_ + size_; }
  const T *begin() const { return data_; }
  const T *end() const { return data_ + size_; }

  void push_back(const T &value) { PushBackImpl_(value); }
  void push_back(T &&value) { PushBackImpl_(std::move(value)); }

  void pop_back() {
    assert(size_ > 0);
    std::allocator_traits<decltype(alloc_)>::destroy(alloc_, data_ + size_);
    --size_;
  }

  void clear() {
    for (std::size_t i{}; i < size_; ++i) {
      std::allocator_traits<decltype(alloc_)>::destroy(alloc_, data_ + i);
    }
    size_ = 0;
  }

  void reserve(std::size_t new_cap) {
    if (new_cap > capacity_) {
      std::size_t new_capacity_{capacity_ + new_cap};
      T *new_data_{alloc_.allocate(new_capacity_)};
      for (std::size_t i{}; i < size_; ++i) {
        std::allocator_traits<decltype(alloc_)>::construct(
            alloc_, new_data_ + i, std::move(data_[i]));
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, data_ + i);
      }
      if (data_ != nullptr)
        alloc_.deallocate(data_, capacity_);
      data_ = new_data_;
      capacity_ = new_capacity_;
    }
  }

  void resize(std::size_t new_size, const T &value = T{}) {
    if (new_size <= size_) {
      for (std::size_t i{size_}; i > new_size; --i) {
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, data_ + i);
      }
      size_ = new_size;
    } else {
      if (new_size > capacity_) {
        std::size_t new_capacity_{new_size * 2};
        T *new_data_{alloc_.allocate(new_size * 2)};
        for (std::size_t i{}; i < size_; ++i) {
          std::allocator_traits<decltype(alloc_)>::construct(
              alloc_, new_data_ + i, std::move(data_[i]));
          std::allocator_traits<decltype(alloc_)>::destroy(alloc_, data_ + i);
        }
        for (std::size_t i{size_}; i < new_size; ++i) {
          std::allocator_traits<decltype(alloc_)>::construct(
              alloc_, new_data_ + i, value);
        }
        if (data_ != nullptr)
          alloc_.deallocate(data_, capacity_);
        data_ = new_data_;
        capacity_ = new_capacity_;
        size_ = new_size;
      }
    }
  }

  void insert(std::size_t index, const T &value) { /* TODO */ }

  void erase(std::size_t index) { /* TODO */ }

private:
  static constexpr std::size_t kInitialCapacity = 8;

  template <typename U> void PushBackImpl_(U &&value) {
    if (!capacity_) {
      capacity_ = kInitialCapacity;
      data_ = alloc_.allocate(capacity_);
    } else if (size_ == capacity_) {
      std::size_t new_capacity_{capacity_ * 2};
      T *new_data_{alloc_.allocate(new_capacity_)};
      for (std::size_t i{}; i < size_; ++i) {
        std::allocator_traits<decltype(alloc_)>::construct(
            alloc_, new_data_ + i, std::move(data_[i]));
        std::allocator_traits<decltype(alloc_)>::destroy(alloc_, data_ + i);
      }
      if (data_ != nullptr)
        alloc_.deallocate(data_, capacity_);
      size_ = capacity_;
      capacity_ = new_capacity_;
      data_ = new_data_;
    }
    std::allocator_traits<decltype(alloc_)>::construct(alloc_, data_ + size_,
                                                       std::forward<U>(value));
    ++size_;
  }

  void ClearAndFree_() {
    if (data_ != nullptr) {
      for (std::size_t i{}; i < size_; ++i) {
        std::allocator_traits<std::allocator<T>>::destroy(alloc_, data_ + i);
      }
      alloc_.deallocate(data_, capacity_);
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }

  void CopyFrom_(const Vector &other) {
    // TODO
    (void)other;
  }

  void MoveFrom_(Vector &&other) {
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::allocator<T> alloc_;
};

} // namespace cs341pp::mp2

#endif // CS341PP_MP2_VECTOR_H_
