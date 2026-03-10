---
id: The_C_Programming_Language
aliases: []
tags: []
---

# Introc
- If you want to teach systems, don't drum up the programmers, sort the issues, and make PRs. Instead, teach them to yearn for the vast and endless C. - Antoine de Saint-Exupery (With edits).
- C is the de-facto programming language to do serious systems programming.
  - Most kernels have their API accessible through C.
- C doesn't have abstractions like classes and Resource Acquisition Is Initialization (RAII) to clean up memory.
## History of C
- C was developed by Dennis Ritchie and Ken Thompson at Bell Labs back in 1973.
- C was two-fold: it was made to target the most popular computers at the time, such as the PDP-7. It tried to remove some of the lower-level constructs (managing registers, and programming assembly for jumps), and create a language that had the power to express programs procedurally (as opposed to mathematically like LISP) with readable code.
  - All this while still having the ability to interface with the operating system.
- It sounded like a tough feat. At first, it was only used internally at Bell Labs along with the UNIX operating system.
- The first "real" standardization was with the Brian Kernighan and Dennis Ritchie's book.
  - It is still widely regarded today as the only portable set of C instructions.
- The K&R book is known as the de-facto standard for learning C.
- We will be mainly focusing on is the POSIX C library which extends ISO.
- The Linux kernel fails to be POSIX compliant.
  - Linux developers didn't want to pay the fee for compliance.
  - Did not want to be fully compliant with multitude of different standard because that meant increased development costs to maintain compliance.
- Features of C:
  - Speed - There is little separating a program and the system.
  - Simplicity - C and its standard library comprise a simple set of portable functions.
  - Manual Memory Management - C gives a program the ability to manage its memory. However, this can be a downside if a program has memory errors.
  - Ubiquity - Through foreign function interfaces (FFI) and language bindings of various types, most other languages can call C functions and vice versa. The standard library is also everywhere. C has stood the test of time as a popular language, and it doesn't look like it is going anywhere.
## Crash course introduction to C
- C++:
```cpp
#include <iostream>
int main() {
  std::cout << "Hello, World" << std::endl;
  return 0;
}
```
- Rust:
```rust
// Rust is a modern systems language, it follows many conventions established by C, with a focus on safety and ergonomics
fn main() {
  println!("Hello World");
}
// 'fn main()' is the entry point of every Rust program. Unlike C, you don't need to specify 'void' for no arguments, and you don't explicitly need to return an integer. If the function reaches the end without crashing, Rust assumes a successful exit (return 0).
// 'println!' is a macro (indicated by the !). In C, 'printf' is a standard function, but in Rust, macros are used for printing to allow the compiler to check at compile-time that your format strings and arguments match up, preventing common crashes. The 'println!' macro automatically adds a newline and flushes the output buffer.
// No '#include' is required for basic printing. Rust's prelude automatically imports the most commonly used tools. For external functionality, Rust uses a module system ('use') rather than text-substitution headers.
// In the Rust ecosystem, we typically use Cargo, the built-in package manager and build tool, though you can use the compiler directly:
// rustc main.rs
// ./main
// Hello World
// cargo run handles compiling and executing in one step.
```
### Preprocessor
- What is the preprocessor?
  - Preprocessing is a copy and paste operation that the compiler performs *before* actually compiling the program.
- In modern C++, you use `constexpr` to replace `#define` for array sizing.
```cpp
// Modern C++
constexpr int MAX_LENGTH = 10;
char buffer[MAX_LENGTH];
```
- There are side effects to the preprocessor though.
  - One problem is that the preprocessor needs to be able to tokenize properly, meaning trying to redefine the internals of the C language with a preprocessor may be impossible.
  - Another problems is that they can't be nested infinitely - there is a bounded depth where they need to stop.
- Macros are also simple text substitutions, without semantics.
- There are also logical problems with the flexibility of certain parameters.
```rust
/* Rust doesn't have a preprocessor. Instead of copy-pasting text before compiling, it uses Constants and Hygienic Macros that understand the structure of your code.

Constants vs. #define
In Rust, you use 'const'. Unlike C macros, constants have a type and a scope, so they don't leak everywhere.*/
// Before
const MAX_LENGTH: usize = 10;
let buffer = [0u8; MAX_LENGTH];

// After compilation
let buffer = [0u8; 10];

/* The Double Increment problems
C macros are risky because they are raw text. If you pass x++ to a C macro, it might increment 'x' twice. Rust macros are hygienic; they treat inputs as complete expressions, so they only evaluate once. */
macro_rules! my_min {
  ($a:expr, $b:expr) => {
    if $a < $b { $a } else { $b }
  };
}

let mut x = 4;
let r = my_min!(x, 5); // x becomes 5, not 6

/* Operator Precedence:
Because Rust macros operate on the syntax tree rather than text, you don't need to worry about the '10 + min(99, 100)' math error. The compiler knows 'min' is its own unit and won't let the '10 +' bleed into the logic. */
/* Array Lengths:
The C sizeof trick is unnecessary. In Rust, arrays and slices always "know" their length. Whether it's a fixed array or dynamic memory, you just call '.len()'.*/
let static_array = [0; 10];
let dynamic_vec = vec![0; 10];

println!("{}", static_array.len()); // 10
println!("{}", dynamic_vec.len()); // 10

/* There is no risk of getting the size of a pointer by mistake because Rust distinguishes between the pointer and the data it points to. */
```
## Language Facilities
### Keywords
- `break`
```cpp
#include <iostream>

int main() {
  // Switch behavior
  int x = 1;
  switch(x) {
    case 1:
      std::cout << "1" << std::endl;
      break;
    case 2:
      std::cout << "2" << std::endl;
      break;
  }

  // Loop behavior
  while (true) {
    while (true) {
      break; // Breaks out of the inner-most loop
    }
    break;
  }
  return 0;
}
```
- `const`
```cpp
const int i = 0; // Constant integer
int const j = 0; // same thing

const char* ptr; // Data is constant, pointer is mutable
char const* ptr; // Same thing ^

char* const ptr3; // Pointer is constant, data is mutable
const char *const ptr4; // Both are constant

// The C++ Way to bypass const: const_cast
const i = 10;
int *nonConstI = const_cast<int *>(&i);

// Critical Warning: Undefined Behavior
// In CS341, the example states that bypassing const results in "defined behavior". In C++ this is incorrect.
// If the original variable was declared 'const': Attempting to modify it (even through a pointer cast) is Undefined Behavior. The compiler might optimize the code assuming 'i' never changes, or place it in read-only memory. The program might crash, or it might "work" on one machine but fail on another.
// If the original variable was NOT 'const': But you are accessing it through a 'const' pointer, using 'const_cast' to modify it is safe and defined.

// C++ also adds 'constexpr', which is even stricter than 'const'. It ensures the value is evaluated at compile-time.
constexpr int max_size = 100; // Guaranteed compile-time constant
```
- In systems programming, the only type of memory that you can't write to is system write-protected memory.
- `continue`
```cpp
#include <iostream>

int main() {
  int i = 10;
  while(i--) {
    if (true) {
      continue; // Jumps directly to the 'while(i--)' check
    }

    // This part is never reached
    int *crash = nullptr;
    *crash = 0;
  }
  return 0;
}
```
- `do {} while ();`
```cpp
#include <iostream>

int main() {
  int i = 1;

  do {
    // Body executes first
    std::cout << i-- << std::endl;
  } while (i > 10); // check happens after the body

  // Program continues here after the condition fails (is false)
  return 0;
}
```
- `enum`
```cpp
// Traditional C-style Enum - in C++ you don't need to repeat the 'enum' keyword when declaring a variable
#include <iostream>

enum day {
  monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

// No need to say 'void process_day(enum day foo)'
void process_day(day foo) {
  switch(foo) {
    case monday:
      std::cout << "Go home!" << std::endl;
      break;
  }
}

// Modern C++ "Strongly Typed" Enum ('enum class')
// C++ introduced 'enum class' to solve to problems: name collisions (where two enums have the same member names) and accidental integer conversions.
enum class Day {
  Monday = 0,
  Tuesday = 0, // Perfectly legal, but as you said, risky
  Wednesday = 10,
  Thursday = 11
};

void process_day(Day d) {
  // You must use the 'Day::' prefix
  if (d == Day::Monday) {
    std::cout << "It's Monday." << std::endl;
  }
}
```
- If you are going to use abstraction, try not to break it.
- `extern`
```cpp
// file1.cc
#include <iostream>

// Declaration: Tells the compiler 'panic' exists somewhere else
extern int panic;

void foo() {
  if (panic) {
    std::cout << "NONONONONO" << std::endl;
  } else {
    std::cout << "This is fine" << std::endl;
  }
}

// file2.cpp
// Definition: Actually reserves the memory for the variable
int panic = 1;

// The 'extern "C"' block If you are trying to link C++ code with actual C code (common in systems programming), you must wrap the declaration in 'extern "C"'. This prevents C++ name mangling, which is how C++ handles overloaded functions.
extern "C" {
  extern int panic;
}

// Global Consts: In C++, `const` globals have internal linkage by default (unlike C, where they are external). If you want a `const` variable in `file2.cc` to be seen in `file1.cc`, you must declare it as `extern const int panic = 1;` in the definition file.
```
- `for`
```cpp
#include <iostream>

int main() {
  // Standard declaration inside the loop
  for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
  }
  // i is no longer in scope here; it is destroyed after the loop
  return 0;
}
// You can declare multiple variable in the initialization, but they must be of the same type:
for (int i = 0, j = 10; i < j; ++i, --j);

// Ranged-based for
int arr[] = {1, 2, 3, 4, 5};
for (int val : arr) {
  std::cout << val;
}
```
- Don't use `goto` in modern C++.
- `if else else-if`
```cpp
#include <iostream>
#include <cstdlib> // For exit()

// (1) Bare if
if (connect(...))
  return -1;

// (2) If with an else
if (connect(...)) {
  std::exit(-1);
} else {
  std::cout << "Connected!" << std::endl;
}

// (3) If with else-if
if (connect(...)) {
  std::exit(-1);
} else if (bind(...)) {
  std::exit(-2);
}

// (4) If with else-if and else
if (connect(...)) {
  std::exit(-1);
} else if (bind(...)) {
  std::exit(-2);
} else {
  std::cout << "Successfully bound!" << std::endl;
}

// Modern C++ "Init-Statement" (C++17)
// C++11 and later introduced a very useful feature where you can initialize a variable inside the if statement. This keeps the variable's scope limited to the if/else block, which is cleaner and safe.
// Variable 'status' only exists inside this if/else structure
if (int status = connect(...); status != 0) {
  std::cout << "Error code: " << status << std::endl;
  return -1;
} else {
  std::cout << "Success!" << std::endl;
}
```
- `inline`
```cpp
#include <iostream>

// Defined in a header file usually
inline int max(int a, int b) {
  return (a < b) ? b : a;
}

int main() {
  int x = 5, y = 10;
  // The compiler might replace this call with the actual ternary logic
  std::cout << "Max: " << max(x, y) << std::endl;
  return 0;
}

/* Why 'inline' is different in C++:
  1. Multiple Definitions: In C++, if you define a function in a header file and include it in multiple '.cpp' files, the linker will normally throw an error for "multiple definitions". Adding 'inline' allows that function to exist in multiple translation units without a linker error.
  2. Class Methods: Any function defined inside a class or struct body is automatically considered 'inline' by the compiler.
  3. The "Hint" Reality: Modern C++ compilers (like GCC, Clang, or MSVC) often ignore 'inline' for optimization purposes. They will inline functions that aren't marked 'inline' if they are small, and they might refuse to inline a function marked 'inline' if it's too complex (like having a recursive loop).*/
// In modern C++, we often use 'constexpr' instead of just 'inline'. This not only hints at inlining but also allows the compiler to calculate the result at compile-time if the inputs are known.
constexpr int max(int a, int b) {
  return (a < b) ? b : a;
}
```
- `struct`
```cpp
#include <iostream>

struct Hostname {
  std::string port;
  std::string name;
  std::string resource;
};

int main() {
  // 1. No need to repeat the 'struct' keyword anymore
  Hostname facebook;
  facebook.port = "80";
  facebook.name = "www.facebook.com";
  facebook.resource = "/";

  // 2. Aggregate Initialization (Static initialization)
  Hostname google = {"80", "www.google.com", "/"};

  // 3. Designated Initializers (C++20 and later)
  Hostname github = { .port = "443", .name = "github.com", .resource = "/" };

  return 0;

  /* Key C++ Differences:
      Type Name: In C++, 'struct Hostname' defines a new type named 'Hostname'. You don't have to write 'struct Hostname myVar;' every time (though you can); you just write 'Hostname myVar;'.
      Struct vs Class: In C++, the only difference between a 'struct' and a 'class' is the default visibility. Members of a 'struct' are public by default; members of a 'class' are private.
      Methods: C++ structs can have functions (methods) inside them, as well as constructors and destructors.
      Memory Alignment: Just like C, C++ structs use padding to ensure alignment - just like classes. If you need to stop this (for network packets or binary files), you use compiler-specific pragmas like '#pragma pack(1)'.*/
}
```
- C-structs are contiguous regions of memory that one can access specific elements of each memory as if they were separate variables.
  - Note that there might be padding between elements, such that each variable is memory-aligned (starts at a memory address that is a multiple of its size).
- `using`
```cpp
#include <iostream>
#include <functional> // For std::function

// The Modern C++ way (Type Alias)
using Comparator = int(*)(void*, void*);

int greater_than(void *a, void *b) {
  return a > b;
}

int main() {
  Comparator gt = greater_than;

  // Even better: std::function can hold pointers, lambdas, or functors
  std::function<int(void*, void*)> modern_gt = greater_than;
  return 0;
}
```
- `union`
```cpp
#include <iostream>
#include <cstdint>

union Pixel {
  // Anonymous struct: lets you access 'red' directly from 'Pixel'
  struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
  };
  uint32_t encoded;
};

int main() {
  Pixel p;
  p.encoded = 0xFF0000FF; // Red with full alpha

  std::cout << "Red value: " << (int)p.red << std::endl;

  p.blue = 0xAB; // Modify a single channel
  return 0;
}
```
- `signed`
  - For the most part, unless your code involves bit shifting, it isn't essential to know the difference in behavior with regards to unsigned and signed arithmetic.
- `void`
```cpp
// In C++, 'void foo()' and 'void foo(void)' are exactly the same. C++ assumes a function with empty parentheses takes no arguments by default, so the extra void is considered old-fashioned "C-style" and is rarely used.
void foo() {
  // Returns nothing
}

int main() {
  foo(); // Valid
  // foo(10); // Error: too many arguments
  return 0;
}

// A 'void*' is still just a raw memory address. However, C++ is much stricter about pointers than C.
// No Implicit Conversion: In C, you can do 'int* p = malloc(4);' because 'void*' converts to anything. In C++, this is an error. You must explicitly cast it.
// Incomplete Type: You still cannot dereference a 'void*' or perform pointer arithmetic on it (though some compilers like GCC allow it as an extension, it is not standard C++).
void *ptr = nullptr; // C++ uses nullptr instead of NULL
int x = 10;
ptr = &x; // This is fine

int y = *ptr; // ERROR: Cannot dereference void*
ptr++; // ERROR: Arithmetic on void* is undefined

// You MUST cast it to use it:
int* intPtr = static_cast<int*>(ptr);
std::cout << *intPtr;
```
- `volatile`
```cpp
#include <iostream>

// External function that might change the flag (e.g., in anoher file)
extern void pass_flag(volatile int* f);

int main() {
  volatile int flag = 1;
  pass_flag(flag) {
    // Without 'volatile', the compiler might cache 'flag' in a register and never check the actual memory again, causing an infinite loop. With 'volatile', it is forced to re-read from memory every time.
  }
  return 0;
}
```
- `volatile` for multi-threaded programs is considered bad practice (and often broken) in C++.
- Not Atomic: `volatile` does not make an operation "thread-safe". If two threads increment a `volatile int` at the same time, you can still get a race condition.
- No Memory Barriers: Modern CPUs reorder instructions for speed. `volatile` does not stop the CPU from moving a read or write operation, which can cause subtle bugs in multi-threading.
The Modern C++ Solution: `std::atomic`:
  - If you are doing multi-threading (affecting one sequence of execution with another), you should use `std::atomic` from the `<atomic>` header. It prevents the same optimization as `volatile` but also guarantees thread safety and proper memory ordering.
```cpp
#include <atomic>

std::atomic<int> flag(1);

// Thread A
while (flag.load()) {
  // This is safe, optimized correctly, and thread-aware.
}

// Thread B
flag.store(0);
```
- Rust:
```rust
/* Language Facilities */
/* Rust uses keywords to define behavior, much like C, but with a focus on memory safety and modern syntax */

/* 'break' exits a loop. In Rust, loops can be labeled to break out of specific nested blocks, and values can be returned from a 'loop' block. */
'outer: loop {
  while true {
    break 'outer; // Exits the loop labeled 'outer
  }
}

/* 'match' is the idiomatic alternative to 'switch'. It requires all possible cases to be handled, which helps prevent logic errors. There is no implicit "fall-through" between cases, so 'break' is not required at the end of each arm. */
match x {
  1 => println!("one").
  2 => println!("two"),
  _ => println("anything else"), // The "default" case
}

/* 'const', 'let', and 'mut': Variables in Rust are immutable by default. The 'mut' keyword must be uses to allow modifications. Unlike C, attempting to bypass immutability through pointer casting is generally prohibited by the compiler's safety rules. */
const ID: i32 = 1; // Constant (compile-time)
let x = 5; // Immutable variable
let mut y = 10; // Mutable variable
y = 11; // Allowed

/* 'continue' skips the remainder of the current loop iteration and proceeds to the next one, identical to its function in C. */

/* 'loop' and 'while': Rust provides a 'loop' keyword for intentional infinite loops. While there is no direct 'do-while' construct, the same behavior is achieved using a 'loop' with a conditional 'break' at the end. */

/* 'enum': Rust enums are more versatile than C enums. They are functional sum types, allowing each variant to store different types of data. */
enum Message {
  Quit, // No data
  Move { x: i32, y: i32 }; // Named fields
  Write(String), // Tuple data
}

/* 'extern' is used to facilitate Foreign Function Interface (FFI) calls, typically when linking against C libraries. */
/* 'for': Rust 'for' loops iterate over ranges or collections. This "for-each" style eliminates the need for manual counter management and helps avoid off-by-one errors. */
for i : in 0..10 { // Iterate from 0 to 9
  println!("{}", i);
}

/* 'goto': This keyword is not present in Rust. Structured control flow, such as labeled breaks and the 'Result' type for error handling, is used instead. */

/* 'if' as an expression: In Rust, 'if' is an expression that returns a value. This often replaces the need for the ternary operator found in C. */
let x = if condition { 1 } else { 2 }''

/* 'inline': Similar to C, this is a hint to the compiler to integrate the function body at the call site. It is applied as an attribute: '#[inline]'. */

/* 'restrict': Rust does not have a 'restrict' keyword. Its ownership and borrowing system ensures that mutable references are unique, which provides the compiler with the same aliasing information that 'restrict' provides in C, but with safety guarantees. */

/* 'return': Exits a function and returns a value. Additionally, the final expression in a Rust function is returned automatically if the semicolon is omitted. */
```
### C data types
- `char` Represents exactly one byte of data. The number of bits in a byte might vary.
- `unsigned` and `signed` versions of all data types are always the same size.
- This must be aligned on a boundary (meaning you cannot use bits in between two addresses).
- To use a fixed width integer type, for more portable code, you may use types defined in `<cstdint>` which are of the form `[u]intwidth_t`.
### Operators
- `sizeof` is evaluated at the time of compilation.
- Note that shifting by the word size (e.g. by 64 in a 64-bit architecture) results in undefined behavior.
## The C and Linux
### Everything is a file
- One POSIX mantra is that everything is a file.
  - Although that has become recently outdated, and moreover wrong, it is the convention we still use today.
  - What this statement means is that everything is a file descriptor, which is an integer.
- File object, a network socket, and a kernel object are all references to records in the kernel's file descriptor table.
  - Operations on those objects are done through system calls.
- File descriptors are merely pointers.
- Imagine that each of the file descriptors in the example actually refers to an entry in a table of objects that the operating system picks and chooses from (that is, the file descriptor table).
- Objects can be allocated and deallocated, closed and opened, etc. The program interacts with these objects by using the API specified through system calls, and library functions.
- In C++, the POSIX "everything is a file" philosophy remains identical, as C++ maintains low-level access to the same integer-based file descriptors, sockets, and epoll handles. While systems programming in C++ often uses the same calls, best practice involve wrapping these descriptors in classes to utilize RAII for automatic cleanup.
### System Calls
- A system call is an operation that the kernel carries out.
  - First, the operating system prepares a system call.
  - Next, the kernel executes the system call to the best of its ability in kernel space and is a privileged operation.
    - When we say the kernel tries its best, this includes the possibility that the operation could fail for several reasons.
      - The file is no longer valid.
      - The hard drive failed.
      - The system was interrupted.
      - etc
- The way that a programmer communicates with the outside system is with system calls.
- An important thing to note it that system calls are expensive. Their cost in terms of time and CPU cycles has recently been decreased, but try to use them as sparingly as possible.
- In C++, System Calls function exactly the same as in C since they are the bridge to the Linux kernel.
- While you can still use the raw POSIX `write()` call, C++ usually wraps these in RAII objects (like `std::ofstream`) to handle the "expensive" nature of kernel transitions through buffering.
```cpp
#include <unistd.h> // For raw write()
#include <fstream> // For C++ buffered I/O

// 1. Raw System Call (Direct kernel communication)
// Fast but "expensive" per call; no safety nets.
write(file_fd, "Hello!", 6);

// 2. C++ Standard Library (Abstraction)
// Automatically handles buffering to reduce system call frequency.
std::ofstream file("test.txt");
file << "Hello";
// File closes automatically via destructor (RAII)
```
- Performance: C++ streams (like `cout` or `ofstream`) use an internal buffer. Instead of calling the kernel for every character, they wait and perform one large "expensive" system call.
- Error Handling: Instead of checking a return integer, C++ uses stream states (`file.fail()`) or exceptions.
- RAII: C++ eliminates "leaked" file descriptors by closing them automatically when the object goes out of scope.
### C System Calls
## Common C Functions
- Note the man pages are organized into sections.
  - Section 2 are System calls.
  - Section 3 are C libraries.
### Handling Errors
- Most functions in C handle errors return oriented.
  - This is at odds with programming languages like C++ or Java where the errors are handled with exceptions.
- There are a number of arguments against exceptions:
  - Exceptions make control flow harder to understand.
  - Exception oriented languages need to keep stack traces and maintain jump tables.
  - Exceptions may be complex objects.
- There are a few arguments for exceptions as well:
  - Exceptions can come from several layers deep.
  - Exceptions help reduce global state.
  - Exceptions differentiate business logic and normal flow.
- In C++, you have two ways to handle errors: the C-style (return codes) and the C++ style (exceptions).
- The C-style (still valid in C++)
- C++ remains fully compatible with `errno` and `perror`. You'll use this when calling POSIX system calls or legacy C libraries.
```cpp
#include <cstdio>
#include <cerrno>
#include <cstring>

std::FILE *f = std::fopen("/invalid/path", "r");
if (!f) {
  std::perror("Error opening file");
}
```
- The C++ Style (Exceptions)
- Modern C++ uses `try-catch` blocks. Instead of checking a return value after every line, you wrap the "happy path" logic and handle failures in one place.
```cpp
#include <fstream>
#include <iostream>

try {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit); // Tell stream to throw on error
  file.open("missing.txt");
} catch (const std::exception &e) {
  std::cerr << "Caught: " << e.what() << std::endl;
}
```
- Key Differences:
  - Backwards Compatibility: C++ uses return codes for OS-level calls (Section 2 man pages) because the Kernel doesn't "speak" C++ exceptions.
  - Control Flow: Exceptions separate "what the code should do" from "what happens if it breaks," avoiding the "if-statement pyramid".
  - Thread Safety: Like C, C++ maintain a thread-local `errno`. However, C++ exceptions are also tread-safe and carry their own data up the stack.
### Input / Output
- Every process has three streams of data when it starts execution: standard input, standard output, standard error.
- They're file descriptors are 0, 1, 2 respectively.
- 2 is reserved for standard error which by library convention is unbuffered (i.e. IO operations are performed immediately).
- ISO defines three types of stream:
  - Unbuffered, where the contents of the stream reach their destination as soon as possible.
  - Line Buffered, where the contents of the stream reach their destination as soon as a newline is provided.
  - Fully Buffered, where the contents of the stream reach their destination as soon as the buffer is full.
- Standard Error is defined as "not fully buffered".
- Standard Output and Input are merely defined to be fully buffered if and only if the stream destination is not an interactive device.
- Usually, standard error will be unbuffered, standard input and output will be line buffered if the output is a terminal otherwise fully buffered.
- One can force a write by calling `fflush()` on the stream.
- To print strings and single characters, use `puts(char name)` and `putchat(char c)`.
- To print to other files streams, use: `fprintf(_file_, "Hello %s, score: %d", name, score);`
  - There is a printf equivalent that works with file descriptors, called `dprintf`.
- To print data into a C string, use `sprintf` or better `snprintf`.
  - `snprintf` returns the number of characters written excluding the terminating byte.
### stdin oriented functions
- Programs should use `fgets` or `getline` instead of `gets`.
- Note that, unlike `gets`, `fgets` copies the newline into the buffer.
- `perror` will print the English version of the error to stderr.
- To have a library function parse input in addition to ready it, use `scanf` (or `fscanf` or `sscanf`) to get input from the default input stream, an arbitrary file stream of a C string, respectively.
### string.h
## C Memory Model
### Structs
### Strings in C
### Places for strings
## Pointers
### Pointer Basics
### Pointer Arithmetic
### So what is a void pointer?
## Common Bugs
### Nul Bytes
### Double Frees
### Returning pointers to automatic variables
### Insufficient memory allocation
### Buffer overflow/underflow
### Strings require strlen(s)+1 bytes
### Using uninitialized variables
### Assuming Uninitialized memory will be zeroed
## Logic and Program flow mistakes
### Equal vs. Equality
### Undeclared or incorrectly prototyped functions
### Extra Semicolons
## Topics
## Questions/Exercises
- What does the following print out?
```cpp
int main() {
  fprintf(stderr, "Hello ");
  fprintf(stdout, "It's a small ");
  fprintf(stderr, "World\n");
  fprintf(stdout, "place");
  return 0;
}

// Hello World
// It's a small place
// because of the type of stream (different buffering style)
```
- What are the differences between the following two declarations? What does `sizeof` return for one of them?
```cpp
char str1[] = "first one";
char *str2 = "another one";

// The first one is stored on the stack
// The second one, the string literal is located in the readonly part of the data section which results.
// size of first one is the length of string + null character and for the second one it is the size in bytes of a pointer on that machines architecture.
```
- What is a string in C?
- A: A series/string of characters that are terminated by a null character.
- Code up a simple `my_strcmp`. How about `my_strcat`, `my_strcpy`, or `my_strdup`? Bonus: Code the functions while only going through the strings once.
- What should each of the following lines usually return?
```cpp
int *ptr;
sizeof(ptr); // Size of pointer
sizeof(*ptr); // Size of integer
```
- What is `malloc`? How is it different from `calloc`. Once memory is allocated how can we use `realloc`?
- What is the `&` operator? How about `*`?
  - `&` address of operator or reference type. `*` to declare and dereference operators.
- Pointer Arithmetic. Assume the following addresses. What are the following shifts?
```cpp
char **ptr = malloc(10); //0x100
ptr[0] = malloc(20); // 0x200
ptr[1] = malloc(20); // 0x300

// ptr + 2 is plus 16 bytes == 0x110
// ptr +4 is plus 32 bytes == 0x120
// ptr[0] + 4 is 4 bytes == 0x204
// ptr[1] + 2000 is 2000 * 1 == 0x700
// *((int) (ptr + 1)) + 3 == ptr + 8 - typecast to integer - derefernce it and add 3 == 0x303
```
- How do we prevent double free errors?
  - A: set pointer to null.
- What is the printf specifier to print a string, `int`, or `char`?
  - A: `%s`, `%d`, `%c`.
- Is the following code valid? Why? Where is `output` located?
```cpp
char *foo(int var) {
  static char output[20];
  snprintf(output, 20, "%d", var);
  return output;
}

// Yes variable is static and is stored in data segment, lifespan is lifetime of the program
// The memory for output is located in the BSS or Data Segment
```
- Write a function that accepts a path as a string, and opens that file, prints the file contents 40 bytes at a time but, every other print reverses the string (try using the POSIX API for this).
- What are some differences between the POSIX file descriptor model and C's `FILE*` (i.e. what function calls are used and which is buffered)? Does POSIX use C's `FILE*` internally or vice versa?
## Rapid Fire: Pointer Arithmetic
```cpp
int *int_; // sizeof(int) == 4;
long *long_; // sizeof(long) == 8;
char *char_;
int *short_; // sizeof(short) == 2;
int **int_ptr; // sizeof(int *) == 8;

// How many bytes are moved over from the following additions?
// 1. int_1 + 1 == 4
// 2. long_ + 7 == 56
// 3. short_- 6 == 12 or -12
// 4. short_ - sizeof(long) == 16 or -16
// 5. long_ - sizeof(long) + sizeof(int_) == 0
// 6. long_ - sizeof(long) / sizeof(int) == -16
// 7. (char*)(int_ptr + sizeof(long)) + sizeof(int_) == +64 then 8
```
