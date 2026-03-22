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
## 10) Strings
### General
- C strings are bytes ending with `\0`.
- That NUL terminator is required.
- `"ABC"` needs 4 bytes: `A B C \0`.
### C
```c
char s[] = "ABC";
printf("%s\n", s);
```
- String literal:
```c
char *p = "ABC"; // do not modify through p
```
### C++
```cpp
char s[] = "ABC";
std::cout << s << "\n";

std::string str = "ABC";
std::cout << str << "\n";
```
### Rust
```rust
let s: &str = "ABC";
println!("{}", s);

let owned = String::from("ABC");
println!("{}", owned);
```
### Key difference / better practice
- C: strings are just arrays of chars ending in `\0`.
- C++: prefer `std::string`.
- Rust: prefer `String` or `&str`.
## 11) Common string functions
### General
- Important operations:
  - length
  - compare
  - copy
  - concatenate
  - duplicate
### C
```c
strlen(s);
strcmp(a, b);
strcpy(dest, src);
strcat(dest, src);
strdup(src);
```
- Example:
```c
char a[20] = "Hi";
strcat(a, " there");
```
### C++
- C functions still exist, but modern C++ prefers `std::string`.
```cpp
std::string a = "Hi";
a += " there";

if (a == "Hi there") {
}
```
### Rust
```rust
let a = String::from("Hi");
let b = String::from(" there");
let c = a.clone() + &b;
```
- Compare:
```rust
if c == "Hi there" {
}
```
- Length:
```rust
let n = c.len();
```
### Key difference / better practice
- C: string functions are powerful but unsafe if buffer is too small.
- C++: use `std::string`.
- Rust: use `String` / `&str`.
## 12) String literals
### General
- A string literal is usually stored in read-only memory.
- Treat it as immutable.
### C
```c
char *p = "hello"; // points to read-only literal
char a[] = "hello"; // local mutable copy
```
- Bad:
```c
*p = 'H'; // undefined behavior, often crashes
```
### C++
```cpp
const char *p = "hello";
char a[] = "hello";
```
### Rust
```rust
let s = "hello"; // immutable string slive
```
### Key difference / better practice
- C/C++: string literals should be treated as read-only.
- Rust: immutable by default.
## 13) Stack, heap, static memory
### General
- Three big memory areas to remember:
  - stack: local variables, automatic lifetime
  - heap: dynamic allocation
  - static/global: exists for whole program
### C
```c
int global_x = 1; // static storage

void f(void) {
  int local = 2; // stack
  int *p = malloc(sizeof(int));
  free(p);
}
```
### C++
```cpp
int global_x = 1;

void f() {
  int local = 2;
  int *p = new int(5);
  delete p;
}
```
- Better:
```cpp
auto p = std::make_unique<int>(5);
```
### Rust
```rust
static GLOBAL_X: i32 = 1;

fn f() {
  let local = 2; // stack
  let p = Box::new(5); // heap
}
```
### Key difference / better practice
- C: manual heap management with `malloc/free`.
- C++: prefer RAII objects (`std::string`, `std::vector`, `std::unique_ptr`).
- Rust: ownership drops heap values automatically.
## 14) Heap allocation
### General
- Heap memory lives until you free/drop it.
- Use heap when lifetime/size is dynamic.
### C
```c
int *p = malloc(sizeof *p);
if (p != NULL) {
  *p = 42;
  free(p);
}
```
- `calloc`:
```c
int *p = calloc(10, sizeof *p); // zero-initialized
```
- `realloc`:
```c
p = realloc(p, 20 * sizeof *p);
```
### C++
```cpp
int *p = new int(42);
delete p;
```
- Better:
```cpp
auto p = std::make_unique<int>(42);
```
### Rust
```rust
let p = Box::new(42);
println!("{}", *p);
```
- Growable heap buffer:
```rust
let mut v = Vec::new();
v.push(1);
v.push(2);
```
### Key difference / better practice
- C: `malloc/calloc/realloc`
- C++: avoid raw `new/delete` when possible
- Rust: use `Box`, `Vec`, `String`; cleanup is automatic
## 15) RAII / ownership
### General
- This is one of the biggest cross-language differences.
### C
- No RAII built in.
- You must remember to clean up manually.
```c
FILE *f = fopen("a.txt", "r");
if (!f) return -1;
/* use f */
fclose(f);
```
### C++
- RAII = resource is acquired in constructor, released in destructor.
- Cleanup happens automatically when object goes out of scope.
```cpp
#include <fstream>

void f() {
  std::ifstream file("a.txt");
  // file closes automatically here
}
```
- Smart pointer:
```cpp
auto p = std::make_unique<int>(42);
```
### Rust
- Ownership + `Drop` gives RAII-like cleanup.
- Value is cleaned up automatically when it goes out of scope.
```rust
use std::fs::File;

fn f() {
  let file = File::open("a.txt");
  // cleaned up automatically at end of scope
}
```
### Key difference / better practice
- C: manual cleanup.
- C++: RAII is the standard best practice.
- Rust: ownership/Drop enforces cleanup naturally.
## 16) `const`, mutability, and immutability
### General
- Mutability rules say whether data can be changed.
```c
const int x = 5;
const char *p = "hello"; // pointer to const chars
```
### C++
```cpp
const int x = 5;
const char *p = "hello";
```
### Rust
- Rust is immutable by default.
```rust
let x = 5;
// x = 6; // error
let mut y = 5;
y = 6;
```
### Key difference / better practice
- C/C++: use `const` to express intent.
- Rust: Immutability is default, which prevents many bugs.
## 17) `static`, `extern`, global visibility
### General
- These control lifetime and visibility.
### C
```c
static int file_only = 1; // visible only in this file
extern int shared; // defined elsewhere
```
- Function-local static:
```c
void f(void) {
  static int count = 0; // keeps value across calls
  count++;
}
```
### C++
- Same ideas:
```cpp
static int file_only = 1;
extern int shared;
```
### Rust
- Rust does not use `extern`/`static` the same way for ordinary code.
```rust
static GLOBAL: i32 = 1;
const VALUE: i32 = 10;
```
- For foreign functions:
```rust
extern "C" {
  fn puts(s: *const i8) -> i32;
}
```
### Key difference / better practice
- C/C++: `static` and `extern` are core linkage/storage tools.
- Rust: modules/privacy/ownership are more central; `extern "C"` is for FFI.
## 18) Structs, enums, unions
### General
- `struct` = group fields together.
- `enum` = choose one value from a set.
- `union` = same memory reused as different types.
### C
```c
struct Point {
  int x;
  int y;
};
```
- Enum:
```c
enum Day { MON, TUE, WED };
```
- Union:
```c
union Data {
  int i;
  float f;
}
```
### C++
```cpp
struct Point {
  int x;
  int y;
};
```
- Enum:
```cpp
enum class Day { Mon, Tue, Wed };
```
- Union:
```cpp
union Data {
  int i;
  float f;
};
```
### Rust
- Struct:
```rust
struct Point {
  x: i32,
  y: i32,
}
```
- Enum:
```rust
enum Day {
  Mon,
  Tue,
  Wed,
}
```
- Rust enums are much stronger:
```rust
enum Message {
  Quit,
  Move(i32, i32),
}
```
- Rust union exists but is rare and unsafe.
### Key difference / better practice
- C: structs/enums are simpler, unions are low-level.
- C++: better enum safety with `enum class`.
- Rust: enums are much more powerful than C enums.
## 19) Control flow
### General
- Basic control flow:
  - `if / else`
  - `for`
  - `while`
  - `break`
  - `continue`
  - `switch` / `match`
### C
```c
if (x > 0) { }
for (int i = 0; i < 10; i++) { }
while (x > 0) { }
switch (x) {
  case 1: break;
  default: break;
}
```
### C++
```cpp
if (x > 0) { }
for (int i = 0; i < 10; i++) { }
while (x > 0) { }
switch (x) {
  case 1: break;
  default: break;
}
```
### Rust
```rust
if x > 0 { }

for i in 0..10 { }

while x > 0 { }

match x {
  1 => {}
  _ => {}
}
```
### Key difference / better practice
- C/C++: `switch` can fall through.
- Rust: `match` is safer and more expressive.
- Always use braces in C/C++ to avoid bugs.
## 20) `goto`
### General
- `goto` jumps directly to a label.
- Usually avoided because it hurts readability.
- Sometimes used for cleanup in low-level C.
### C++
- Possible, but rarely needed due to RAII.
```cpp
if (error) goto cleanup;
cleanup:
  return;
```
### Rust
- No `goto`.
- Use structured control flow instead.
### Key difference / better practice
- C: sometimes acceptable for cleanup paths.
- C++/Rust: usually unnecessary because cleanup is automatic or structured.
## 21) Errors: return codes, exceptions, `Result`
### General
- Programs need a way to report failure.
### C
- Usually:
  - return value indicates error
  - `errno` stores extra error info
```c
FILE *f = fopen("missing.txt", "r");
if (f == NULL) {
  perror("fopen");
}
```
### C++
- Can use old C style or exceptions.
```cpp
try {
  throw std::runtime_error("bad");
} catch (const std::exception& e) {
  std::cout << e.what() << "\n";
}
```
### Rust
- Uses `Result<T, E>`.
```rust
use std::fs::File;

fn open_file() -> std::io::Result<File> {
  File::open("missing.txt")
}
```
### Key difference / better practice
- C: return codes + `errno`
- C++: exceptions or error codes
- Rust: `Result` is explicit and very clean for systems code
## 22) Standard I/O vs low-level I/O
### General
- There are two major styles:
  - library I/O: buffered, higher-level
  - system call / POSIX I/O: lower-level, file descriptors
### C standard I/O (`FILE*`)
- Buffered I/O:
```c
#include <stdio.h>

FILE *f = fopen("a.txt", "r");
fclose(f);
```
- Printing:
```c
printf("hello %d\n", 42);
fprintf(stderr, "error\n");
```
### C POSIX I/O
- Unbuffered system-call style:
```c
#include <fcntl.h>
#include <unistd.h>

int fd = open("a.txt", O_RDONLY);
char buf[40];
ssize_t n = read(fd, buf, sizeof(buf));
close(fd);
```
### C++
- Library I/O:
```cpp
#include <fstream>
#include <iostream>

std::ifstream f("a.txt");
std::cout << "hello\n";
```
- Can still use POSIX I/O on Unix:
```cpp
int fd = open("a.txt", O_RDONLY);
```
### Rust
- High-level:
```rust
use std::fs::File;
use std::io::Read;

let mut f = File::open("a.txt")?;
let mut s = String::new();
f.read_to_string(&mut s)?;
```
- Lower-level Unix-style is possible through crates or `std::os` APIs, but ordinary Rust code usually starts with safe wrappers.
### Key difference / better practice
- C stdio / C++ streams / Rust std::fs = easier, often buffered.
- POSIX `open/read/write/close` = lower-level, work with integer file descriptors.
- Use low-level I/O when you need exact OS-style behavior.
## 23) File descriptors
### General
- On Unix-like systems, many resources are handled with file descriptors:
  - files
  - sockets
  - pipes
- A file descriptor is just an integer handle.
### C
```c
int fd = open("a.txt", O_RDONLY);
read(fd, buf, 40);
close(fd);
```
### C++
- Same POSIX idea on Unix:
```cpp
int fd = open("a.txt", O_RDONLY):
```
### Rust
- Rust wraps OS handles in safe types:
```rust
use std::fs:File;
let f = File::open("a.txt")?;
```
### Key difference / better practice
- C/POSIX: raw integer descriptors.
- C++/Rust: usually wrap raw resources in objects/types.
## 24) Buffering of output
### General
- `stdout` is usually buffered.
- `stderr` is usually unbuffered or less buffered.
- This is why print order can look weird.
### C
```c
fprintf(stderr, "Hello ");
fprintf(stdout, "It's a small ");
fprintf(stderr, "World\n");
fprintf(stdout, "place\n");
```
- Possible output order may look mixed because `stdout` is buffered and `stderr` usually is not.
### C++
```cpp
std::cerr << "Hello ";
std::cout << "It's a small ";
std::cerr << "World\n";
std::cout << "place\n";
```
### Rust
```rust
eprint!("Hello ");
print!("It's a small ");
eprint!("World");
println!("place");
```
### Key difference / better practice
- If output order matters, flush explicitly.
#### C
```c
fflish(stdout);
```
#### C++
```cpp
std::cout << std::flush;
```
#### Rust
```rust
use std::io::{self, Write};
io::stdout().flush().unwrap();
```
## 25) Input functions
### General
- Reading input safely matters a lot.
### C
- Prefer:
  - `fgets`
  - `getline`
```c
char buf[10];
fgets(buf, sizeof(buf), stdin);
```
- Dynamic:
```c
char *line = NULL;
size_t n = 0;
getline(&line, &n, stdin);
free(line);
```
- Avoid:
  - `gets` (removed, unsafe)
### C++
```cpp
std::string s;
std::getline(std::cin, s);
```
### Rust
```rust
let mut s = String::new();
std::io::stdin().read_line(&mut s).unwrap();
```
### Key difference / better practice
- C: bounds are your responsibility
- C++/Rust: standard string input is much safer.
## 26) Common memory bugs
### General
- Thee are the classic foot-guns.
### A) Double free
#### C
```c
int *p = malloc(sizeof *p);
free(p);
free(p); //bad
```
#### C++
```cpp
int *p = new int(5);
delete p;
delete p; // bad
```
#### Rust
- Safe Rust prevents this automatically.
### Better practice
- After `free`, set pointer to `NULL` in C if ownership is done.
- In C++, use smart pointers.
- In Rust, ownership solves this.
### B) Use after free
#### C
```c
int *p = malloc(sizeof *p);
free(p);
*p = 5; // bad
```
#### C++
```cpp
int *p = new int(5);
delete p;
std::cout << *p; // bad
```
#### Rust
- Safe Rust prevents this.
### C) Wrong allocation size
#### C
- Bad:
```c
user_t *u = malloc(sizeof(u)); // only pointer size
```
- Good:
```c
user_t *u = malloc(sizeof(*u));
```
#### C++
- Prefer not to raw-allocate structs manually.
#### Rust
- Not a common issue in safe Rust.
### D) Buffer overflow
#### C
```c
char buf[4];
strcpy(buf, "hello"); // bad
```
#### C++
```cpp
char buf[4];
std::strcpy(buf, "hello"); // bad
```
#### Rust
- Bounds checked in safe code:
```rust
let a = [1, 2, 3];
println!("{}", a[10]); // panic, not silent corruption
```
### Key difference / better practice
- C/C++: easy to corrupt memory.
- Rust: safe code prevents most memory corruption.
## 27) `void*`
### General
- `void*` means "pointer to unknown type."
- Good for generic low-level APIs.
- Cannot be dereferenced until cast.
### C
```c
void *p = malloc(10);
char *s = p;
```
### C++
```cpp
void *p = std::malloc(10);
char *s = static_cast<char *>(p);
```
### Rust
- Raw generic pointers exist, but safe Rust prefers typed references.
```rust
let x = 5;
let p = &x as *const i32;
```
### Key difference / better practice
- C: `void*` is very common.
- C++: use templates/generics instead when possible.
- Rust: use generics/references first, raw pointers only when needed.
## 28) `volatile`, `inline`, `restrict`
### C
```c
volatile int flag;
inline int max(int a, int b) { return a > b ? a : b; }
void copy(int * restrict dst, int * restrict src);
```
### C++
```cpp
volatile int flag;
inline int max(int a, int b) { return a > b ? a : b; }
```
- C++ does not really use `restrict` in standard C++ the same way C does.
### Rust
- No direct equivalent in ordinary safe syntax.
  - `inline` exists as an attribute.
```rust
#[inline]
fn max(a: i32, b: i32) -> {
  if a > b { a } else { b }
}
```
### Key difference / better practice
- These are advanced tools.
- Learn them, but don;t rely on them before mastering memory and ownership basics.
## 29) Print formatting
### General
- Printing values is different across the three languages.
### C
```c
printf("%s %d %c %p\n", str, num, ch, ptr);
```
- Common:
  - `%s` string
  - `%d` int
  - `%c` char
  - `%p` pointer
### C++
```cpp
std::cout << str << " " << num << " " << ch << "\n";
```
### Rust
```rust
println!("{} {} {}", s, num, ch);
println!("{:p}", ptr);
```
### Key difference / better practice
- C: format strings are powerful but easy to misuse.
- C++/Rust: stream/format systems are usually safer.
## 30) Best-practice summary
### C
- Know:
  - pointers
  - arrays
  - strings
  - `malloc/free`
  - `printf/fprintf`
  - `open/read/write`
  - `errno`
- Always:
  - check bounds
  - allocate correct size
  - free what you own
  - avoid unsafe string copies
### C++
- Use C knowledge, but prefer:
  - `std::string`
  - `std::vector`
  - `std::unique_ptr`
  - RAII
- Avoid raw `new/delete` unless necessary.
### Rust
- Learn:
  - ownership
  - borrowing
  - `String` vs `&str`
  - `Box`, `Vec`
  - `Result`
- Prefer safe Rust first.
- Use `unsafe` only when required.
## Tiny cross-language comparison cheatsheet
### String ownership
#### C
```c
char *p = "hi"; // borrowed-ish pointer to literal
char a[] = "hi"; // owned mutable array
```
#### C++
```cpp
std::string s = "hi"; // owned string
```
#### Rust
```rust
let s1: &str = "hi"; // borrowed string slice
let s2: String = String::from("hi"); // owned sting
```
### Heap allocation
#### C
```c
int *p = malloc(sizeof *p);
free(p);
```
#### C++
```cpp
auto p = std::make_unique<int>(5);
```
#### Rust
```rust
let p = Box::new(5);
```
### File open
#### C
```c
FILE *f = fopen("a.txt", "r");
```
- or POSIX:
```c
int fd = open("a.txt", O_RDONLY);
```
#### C++
```cpp
std::ifstream f("a.txt");
```
#### Rust
```rust
let f = std::fs:File:open("a.txt")?;
```
## Final "remember this" section
- C strings are bytes ending in `\0`.
- Array != pointer.
- `sizeof(ptr)` != `sizeof(*ptr)`.
- Heap memory lives until freed/dropped.
- String literals should be treated as read-only.
- Pointer arithmetic moves by element size.
- C uses return codes + `errno`.
- POSIX I/O uses file descriptors (`int`).
- stdio/iostream/Rust I/O are usually higher-level wrappers.
- C needs manual cleanup.
- C++ uses RAII.
- Rust uses ownership and borrowing.
