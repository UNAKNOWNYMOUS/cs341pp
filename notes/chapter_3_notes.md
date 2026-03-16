---
id: chapter_3_notes
aliases: []
tags: []
---

# Systems Programming Notes -- C / C++ / Rust
## 1) What systems programming is
### General
- Systems programming = writing software close to the OS/hardware.
- You work with:
  - memory
  - files
  - processes
  - sockets
  - threads
  - system calls
- C is the classic systems language because OS APIs are usually exposed in a C-friendly way.
- C++ adds abstractions on top of C.
- Rust gives low-level control with stronger safety rules.
### C
```c
#include <stdio.h>

int main(void) {
  printf("Hello\n");
  return 0;
}
```
### C++
```cpp
#include <iostream>

int main() {
  std::cout << "Hello\n";
  return 0;
}
```
### Rust
```rust
fn main() {
  println!("Hello");
}
```
### Key difference / better practice
- C: maximum control, minimum safety.
- C++: control + abstraction like RAII.
- Rust: control + ownership/borrowing safety.
## 2) Compilation idea
### General
- Source code is turned into machine code.
- Before compilation, C/C++ may run a preprocessor.
- Rust does not have a C-style text preprocessor.
### C
```bash
gcc main.c -o main
./main
```
### C++
```bash
g++ main.cpp -o main
./main
```
### Rust
```bash
rustc main.rs
./main
```
### Key difference / better practice
- C/C++: `#include`, `#define` are text substitution tools.
- Rust: uses modules/macros, not raw textual copy-paste like C macros.
## 3) Preprocessor / macros
### General
- A preprocessor does text substitution before compilation.
- This is powerful but dangerous because it has no real type safety.
### C
```c
#define MAX 10
#define MIN(a,b) ((a) < (b) ? (a) : (b))
```
- Bad:
```c
#define MIN(a,b) a < b ? a : b
```
### C++
```cpp
#define MAX 10
#define MIN(a,b) ((a) < (b) ? (a) : (b))
```
- Better C++:
```cpp
template <typename T>
T min_val(T a, T b) {
  return a < b ? a : b;
}
```
### Rust
```rust
const MAX: i32 = 10;

fn min_val<T: Ord>(a: T, b: T) -> T {
  if a < b { a } else { b }
}
```
### Key difference / better practice
- C: macros are common, but risky.
- C++: prefer `cont`, `constexpr`, templates, inline functions.
- Rust: prefer `const`, functions, generics.
## 4) `main`, return values, exit status
### General
- `main` is the program entry point.
- `0` usually means success.
- nonzero usually means failure.
### C
```c
int main(void) {
  return 0;
}
```
### C++
```cpp
int main() {
  return 0;
}
```
### Rust
- Rust `main` usually returns `()`, but can also return a `Result`.
```rust
fn main() {
}
```
- Or:
```rust
fn main() -> Result<(), Box<dyn std::error::Error>> {
  Ok(())
}
```
### Key difference / better practice
- C/C++: return integer status.
- Rust: can return `Result`, which is cleaner for fallible programs.
## 5) Basic types
### General
- Languages all have integers, floating-point types, char/bytes, booleans.
- Exact sizes matter in systems code.
### C
```c
char c = 'A';
int x = 42;
long long y = 1000;
float f = 3.14f;
double d = 3.14;
```
- Fixed-width:
```c
#include <stdint.h>
int32_t a = 10;
uint64_t b = 20;
```
### C++
```cpp
char c = 'A';
int x = 42;
long long y = 1000;
float f = 3.14f;
double d = 3.14;
```
- Fixed-width:
```cpp
#include <cstdint>
int32_t a = 10;
uint64_t b = 20;
```
### Rust
```rust
let c: char = 'A';
let x: i32 = 42;
let y: i64 = 1000;
let f: f32 = 3.14;
let d: f64 = 3.14;
let b: u64 = 20;
```
### Key difference / better practice
- Use fixed-width integers when size matters:
  - C: `int32_t`
  - C++: `std::int32_t`
  - Rust: `i32`, `u64`
## 6) `sizeof` / size of a type
### General
- `sizeof` tells you how many bytes a type/object uses.
- Very important for memory allocation and pointer logic.
### C
```c
int *ptr;
sizeof(ptr); // size of pointer
sizeof(*ptr); // size of int
```
### C++
```cpp
int *ptr;
sizeof(ptr); // pointer size
sizeof(*ptr); // int size
```
### Rust
- Rust uses:
```rust
use std::mem:size_of;

size_of::<*const i32>(); // pointer size
size_of::<i32>(); // int size
```
### Key difference / better practice
- `sizeof(ptr)` is not the size of the thing pointed to.
- `sizeof(*ptr)` is the size of the pointed-to type.
- This is one of the most common beginner mistakes in C/C++.
## 7) Pointers, address-of, dereference
### General
- A pointer stores a memory address.
- Address-of = get address.
- Dereference = access value at address.
### C
```c
int x = 5;
int *p = &x; // address-of
printf("%d\n", *p); // dereference -> 5
```
### C++
```cpp
int x = 5;
int *p = &x;
std::cout << *p << "\n";
```
- Also C++ has references:
```cpp
int x = 5;
int &r = x;
r = 10; // changes x
```
### Rust
- Rust references are safer than raw pointers.
```rust
let x = 5;
let r = &x;
println!("{}", *r);
```
- Raw pointers also exist:
```rust
let x = 5;
let p: *const i32 = &x;
```
### Key difference / better practice
- C: pointers everywhere.
- C++: pointers + references.
- Rust: references are the normal safe way; raw pointers are for low-level/unsafe code.
## 8) Pointer arithmetic
### General
- Pointer arithmetic moves by element size, not by 1 byte unless pointer type is byte-sized.
- `p + 1` means "next element."
### C
```c
int arr[3] = {10, 20, 30};
int *p = arr;
printf("%d\n", *(p + 1)); // 20
```
### C++
```cpp
int arr[3] = {10, 20, 30};
int *p = arr;
std::cout << *(p + 1) << "\n"; // 20
```
### Rust
- Safe Rust normally uses slices/indexing instead.
```rust
let arr = [10, 20, 30];
println!("{}", arr[1]);
```
- Raw pointer arithmetic:
```rust
let arr = [10, 20, 30];
let p = arr.as_ptr();
unsafe {
  println!("{}", *p.add(1));
}
```
### Key difference / better practice
- C/C++: pointer arithmetic is common but error-prone.
- Rust: prefer slices and indexing; raw pointer arithmetic is `unsafe`.
## 9) Arrays vs pointers
### General
- Arrays and pointers are related, but not the same thing.
- Arrays are actual storage.
- Pointers just store addresses.
### C
```c
char str1[] = "hello"; // array, mutable copy
char *str2 = "hello"; // pointer to string literal
```
- `sizeof(str1)` = array size in bytes
- `sizeof(str2)` = pointer size
### C++
```cpp
char str1[] = "hello";
const char *str2 = "hello";
```
- Modern C++ also has:
```cpp
std::string s = "hello";
```
### Rust
```rust
let s1 = "hello"; // string slice: &str
let s2 = String::from("hello"); // owned, growable string
```
### Key difference / better practice
- C/C++: `char[]` vs `char*` matters a lot.
- Rust: `&str` and `String` make this distinction much clearer.
