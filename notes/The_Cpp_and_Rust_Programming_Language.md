---
id: The_Cpp_and_Rust_Programming_Language
aliases: []
tags: []
---

## C++ and Linux
### Big Idea
- C++ does not replace the OS.
- When C++ programs want to interact with Linux, they usually still go through:
  - POSIX APIs
  - System Calls
  - C library / standard library wrappers
- So even in C++, a lot of Linux programming still looks very C-like.
### Everything is a file
- In Linux/POSIX, many things are represented by a file descriptor.
- A file descriptor (fd) is just an integer used to refer to an OS-managed object.
- Examples:
```cpp
int file_fd = open(...);
int socket_fd = socker(...);
int epoll_fd = epoll_create(...);
```
- These all return integers like:
  - file
  - network socket
  - kernel event object
#### Easy note
- fd = integer handle to kernel object.
- The fd is not the object itself.
- It is more like an index / handle the kernel gives your program.
### System Calls
- A system call is how a program asks the kernel to do something.
- Examples:
  - open a file
  - read from a file
  - write to a file
  - create a socket
  - allocate OS resources
- Example:
```cpp
write(file_fd, "hello!", 6);
```
- This asks the kernel to write bytes.
#### Easy note
- System call = request from user program to kernel.
### Why system calls matter
- The kernel runs in privileged mode, and your program runs in user mode.
- Your program cannot directly control hardware or kernel resources, so it must ask through system calls.
#### Easy note
- User space asks, kernel space does.
### System calls can fail
- A system call may fail because:
  - bad file descriptor
  - file closed
  - disk problem
  - interrupted by signal
  - permission denied
- So Linux code must always check for errors.
- Example idea:
```cpp
ssize_t n = write(file_fd, "Hello!", 6):
if (n == -1) {
  // handle error
}
```
#### Easy note
- Always check return values
### System calls are expensive
- System calls cost more than normal function calls because the CPU must switch between:
  - user space
  - kernel space
- So avoid making too many tiny systems when possible.
#### Easy note
- System calls are slower than normal function calls.
### C++ library vs Linux system calls
- Many C++ functions are higher-level wrappers.
- Example:
  - `std::cout` may eventually write to standard output.
  - file streams may eventually use lower-level OS operations
- But under Linux, real OS work still ends up going through lower layers like:
  - C library
  - POSIX functions
  - system calls
#### Easy note
- C++ library code often ends up using C/POSIX/Linux underneath.
### Important idea for C++ on Linux
- C++ gives you:
  - classes
  - RAII
  - safer abstractions
  - containers
  - streams
- Linux gives you:
  - file descriptors
  - processes
  - sockets
  - pipes
  - signals
  - epoll
  - syscalls
- So in systems programming:
- C++ == nicer language tools
- Linux/POSIX == OS interface
### Tiny summary
- Linux uses file descriptors for many resources.
- File descriptor == integer handle.
- Programs interact with Linux through system calls.
- System calls ask the kernel to do work.
- System calls can fail.
- System calls are expensive.
- C++ often uses wrappers, but Linux still happens underneath.
## Rust and Linux
### Big idea
- Rust also does not replace the OS.
- When Rust talks to Linux, it still uses:
  - POSIX APIs
  - Linux syscalls
  - libc / system interfaces
  - Rust wrappers around them
- Rust gives safer language rules, but Linux is still Linux underneath.
### Everything is a file
- In Linux, many resources are represented by a file descriptor.
- A file descriptor is an integer.
- Examples in Rust usually come from wrappers, but concept stays the same:
  - file
  - socket
  - epoll object
  - pipe
#### Easy note
- fd == integer handle to kernel-manage resource.
### System calls
- A system call is how a Rust program asks the Linux kernel to do something.
- Examples:
  - open
  - read
  - write
  - socket
  - close
- Rust often uses standard library wrappers like:
```rust
use std::io::Write;

fn main() {
  std::io::stdout().write_all(b"Hello!\n").unwrap();
}
```
- But underneath, this eventually becomes OS-level output.
#### Easy note
- Rust wrapper on top, kernel underneath.
### User space vs kernel space
- Rust programs run in user space.
- The kernel controls privileged operations.
- So Rust must still ask the kernel through system calls.
#### Easy note
- Rust is safe user-space code; kernel still does the OS work.
### System calls can fail
- Just like in C/C++, Linux operations can fail.
- Rust usually handles this with `Result` instead of just integer error code.
- Example:
```rust
use std::fs::File;

fn main() -> std::io::Result<()> {
  let _file = File::open("hello.txt")?;
  Ok(())
}
```
- If opening fails, Rust returns an error.
#### Easy note
- Rust uses `Result` for OS errors.
### System calls are expensive
- Same Linux rule:
  - system calls are slower than normal function calls
  - avoid unnecessary syscalls
  - buffering helps performance
#### Easy note
- Too many syscalls = slower program.
### Rust standard library vs Linux syscalls
- Rust often gives safer, higher-level APIs:
  - `std::fs::File`
  - `std::net::TcpStream`
  - `std::process`
  - `std::io`
- But underneath, these still rely on the OS.
- So:
- Rust abstraction -> libc / syscall layer -> kernel
### Why Rust feels different
- Rust adds:
  - ownership
  - borrowing
  - safer error handling
  - safer resource cleanup (`Drop`)
  - type safety
- But Linux concepts stay the same:
  - file descriptors
  - read/write
  - sockets
  - processes
  - permissions
  - signals
#### Easy note
- Rust changes how you write the code, not how Linux fundamentally works.
### Tiny summary
- Linux resources are often represented by file descriptors.
- file descriptors == integer handle.
- Rust still talks to Linux using system calls underneath.
- system calls ask the kernel to do work.
- they can fail.
- they are expensive.
- Rust usually wraps them in safer APIs and `Result`.
### Super short compare notes
- C++
  - Uses POSIX/Linux APIs directly very often.
  - Can use C-style file descriptors easily.
  - Higher-level than C, but still close to Linux.
- Rust
  - Same Linux underneath.
  - Often uses safer wrappers.
  - Errors handled with `Result`.
  - Resource cleanup usually automatic.
### One-line memory notes
- Everything is a file == many Linux resources are accessed through file descriptors.
- fd == integer handle to a kernel object.
- system call == request from program to kernel.
- kernel space does privileged work.
- user space must ask through syscalls.
- syscalls can fail.
- syscalls are expensive.
- C++, C, and Rust all still depend on Linux/POSIX underneath.
## Common Linux / C-style Functions - merged notes for C, C++, Rust
### Finding docs
- For Linux/POSIX functions, use man pages.
  - Section 2 = system calls
  - Section 3 = library functions
- Easy note:
  - `open` -> syscall docs
  - `printf` -> library docs
- For C and C++, man pages are directly useful because they both commonly use C/POSIX APIs.
- For Rust, you often use:
  - Rust docs for wrappers like `std::fs::File`
  - man pages for the underlying Linux behavior.
### Error handling
- When talking to Linux or C-style libraries, errors are usually handled by:
  - return values
  - sometimes errno
  - sometimes a function-specific error code
- This matters in C, C++ when using C/POSIX APIs, and sometimes in Rust FFI / low-level crates.
#### C and C++ (C-style APIs)
- Most functions signal failure by return something special:
  - `NULL`
  - `-1`
  - nonzero error code
  - short read/write count
- Then you check `errno` if the man page says so.
- Example:
```cpp
#include <errno.h>
#include <stdio.h>
#include <string.h>

FILE *f = fopen("/does/not/exist.txt", "r");
if (f == NULL) {
  fprintf(stderr, "errno = %d\n", errno);
  fprintf(stderr, "message = %s\n", strerror(errno));
}
```
- Shortcut
```cpp
perror("fopen failed");
```
- Easy note:
  - check return value first
  - then check errno if documented.
#### Important exception
- Not every function uses `errno`.
- Some return their own error code directly.
- Example:
```cpp
int s = getnameinfo(...);
if (s != 0) {
  fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
}
```
- Easy note:
  - some APIs use `errno`
  - some APIs return the error code themselves
  - always check the man page
#### C++ difference
- C++ the language supports exceptions, but POSIX/C library functions do not magically throw exceptions.
- So in Linux systems code, C++ often still looks like C:
```cpp
int fd = open("file.txt" O_RDONLY);
if (fd == -1) {
  perror("open");
}
```
- Why:
  - Linux/POSIX APIs are C-based.
  - they use return-value error handling, not C++ exceptions.
#### Rust difference
- Rust usually uses `Result<T, E>` instead of raw `errno` in normal code.
- Rust example:
```rust
use std::fs::File;

fn main() {
  match File::open("missing.txt") {
    Ok(file) => {
      let _ = file;
    }
    Err(e) => {
      eprintln!("open failed: {}", e);
    }
  }
}
```
- Why:
  - Rust wraps OS failures in `Result`.
  - safer and more explicit than raw global error state.
- Easy note:
  - C / POSIX -> return values + maybe `errno`
  - Rust -> usually `Result`
### Standard stream
- Every process starts with 3 standard streams:
  - stdin = input
  - stdout = normal output
  - stderr = erros/debug
- File descriptors:
  - `0` = stdin
  - `1` = stdout
  - `2` = stderr
- Easy note:
  - `stdin = 0`
  - `stdout = 1`
  - `stderr = 2`
- These can point to:
  - terminal
  - file
  - pipe
  - another program
## Buffered vs unbuffered output
- Output is often buffered.
- Kinds of buffering:
  - unbuffered = writes immediately
  - line buffered = writes on newline
  - fully buffered = writes when buffer fills
- Common behavior:
  - `stderr` = usually unbuffered
  - terminal `stdout` = usually line buffered
  - file `stdout` = often fully buffered.
- Easy note:
  - `\n` often flushes terminal output
  - `fflush(stream)` forces flush
## Printing output
- There are two common levels:
  - formatted library output
  - raw OS write
- Example:
  - `printf` = library function
  - `write` = system call
- Easy note:
  - `printf` is higher-level
  - `write` is lower-level
### C / C++
- Basic formatted output: `print` = stdout
- To a specific stream: `fprintf` = choosen `FILE*`
- To a file descriptor: `dprintf` = chosen file descriptor
- To a string buffer: `snprintf` = write into char buffer
#### Impprtant
- Prefer `snprintf` over `sprintf`
- Why:
  - `sprintf` can overflow buffer
  - `snprintf` limits bytes written
