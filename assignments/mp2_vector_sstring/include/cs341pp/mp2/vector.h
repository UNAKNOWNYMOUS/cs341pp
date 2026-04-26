// Copyright 2026  Ahssan Javed  UNAKNOWNYMOUS@protonmail.com
//
// Description: This file provides my own short implementation of the vector
// class
//
// Project:
// https://github.com/UNAKNOWNYMOUS/cs341pp/tree/main/assignments/mp2_vector_sstring
#ifndef CS341PP_MP2_VECTOR_H_
#define CS341PP_MP2_VECTOR_H_

#include <cstddef>
#include <memory>

namespace cs341pp::mp2 {

template <typename T> class Vector {
public:
  // Implementing Rule of 6 (including Destructor)
  // Asking compiler to generate a default no args constructor
  Vector() = default;
  ~Vector() { ; }

  // Copy Constructor
  Vector(const Vector &other) { ; }
  // Copy Assignment Constructor
  Vector &operator=(Vector &other) { ; }

  // Move Constructor
  Vector(const Vector &&other) noexcept { ; }
  // Move Assignment Constructor
  Vector &operator=(Vector &&other) noexcept { ; }

  std::size_t size() const { ; }
  std::size_t capacity() const { ; }
  bool empty() const { ; }

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

private:
  // Initializing variables
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::allocator<T> alloc_;
};

} // namespace cs341pp::mp2

#endif
