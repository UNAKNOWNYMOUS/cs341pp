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

  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::allocator<T> alloc_;
};

} // namespace cs341pp::mp2

#endif
