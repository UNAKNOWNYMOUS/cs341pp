---
id: The_Rust_Programming_Language
aliases: []
tags: []
---

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
