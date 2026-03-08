---
id: The_Cpp_Programming_Language
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
