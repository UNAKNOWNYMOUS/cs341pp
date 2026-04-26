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
  // Implementing Rule of 6 (including Destructor)
  // Asking compiler to generate a default no args constructor
  Vector() = default;
  ~Vector() { ClearAndFree_(); }

  // Copy Constructor
  Vector(const Vector &other) { CopyFrom_(other); }
  // Copy Assignment Constructor
  Vector &operator=(Vector &other) {
    // self assignment guard
    if (this != &other) {
      ClearAndFree_();
      CopyFrom_(other);
    }
    return *this;
  }

  // Move Constructor
  Vector(const Vector &&other) noexcept { MoveFrom_(std::move(other)); }
  // Move Assignment Constructor
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
  T &operator[](std::size_t i) { ; }
  const T &operator[](std::size_t i) const { ; }

  // Overloading operator for mutable and immutable objects
  T &at(std::size_t i) { ; }
  const T &at(std::size_t i) const { ; }

  // Iterators (will allow me to do a for each loop)
  T *begin() { ; }
  const T *begin() const { ; }
  T *end() { ; }
  const T *end() const { ; }

  void push_back(const T &value) { ; }
  // Using 'std::move' because even though value is an r-value in C++ a name is
  // an l-value so it will trigger a copy when passed elsewhere
  void push_back(T &&value) { ; }

  void pop_back() { ; }

  void clear() { ; }
  void reserve(std::size_t new_cap) { ; }
  // TODO: Write comment explaining why using list initializer that assignment
  // r-value to l-value const ref i.e. it is efficient
  void resize(std::size_t new_size, const T &value = T{}) { ; }
  void insert(std::size_t index, const T &value) { ; }
  void erase(std::size_t index) { ; }

private:
  // Evaluated at compile time
  static constexpr std::size_t kInitialCapacity = 8;

  template <typename U> void PushBackImpl_(U &&value) {
    // TODO: Here
    (void)value;
  }

  void ClearAndFree_() {
    // TODO:
  }

  void CopyFrom_(const Vector &other) {
    // TODO:
    (void)other;
  }

  void MoveFrom_(Vector &&other) {
    // TODO:
  }

  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::allocator<T> alloc_;
};

} // namespace cs341pp::mp2

#endif
