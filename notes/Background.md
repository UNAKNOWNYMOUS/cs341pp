---
id: Background
aliases: []
tags: []
---

# $ ./a.out
## Systems Architecture
### Assembly
- Assembly is the lowest that you'll get to machine language without writing 1's and 0's.
- Each computer has an architecture, and that architecture has an associated assembly language.
  - Each assembly command has a 1:1 mapping to a set of 1's and 0's that tell the computer exactly what to do.
### Atomic Operations
- An operation is atomic if no other processor should interrupt it.
- If an instruction is atomic, it makes sure that only one processor or thread performs any intermediate step at a time. With x86 this is done by the `lock` prefix.
### Caching
- A short but non-complete list on how caching could impact your code:
  - Race Conditions! If a value is stored in two different processor caches, then that value should be accessed by a single thread.
  - Speed. With a cache, your program may look faster mysteriously. Just assume that reads and writes that either happened recently or are next to each other in memory are fast.
  - Side effects. Every read or write affects the cache state. While most of the time this doesn't help or hurt, it is important to know. Check the Intel programmer guide on the lock prefix for more information.
### Interrupts
- An interrupt is internally an electrical signal that is delivered to the processor when something happens - this is a hardware interrupt.
  - Then the hardware decides if this is something that it should handle or it should pass to the operating system.
    - The operating system then decides if this is something that it should handle or something the application should handle.
### Optional: Hyperthreading
## Debugging and Environments
### ssh
- `ssh` is short for the Secure Shell. It is a network protocol that allows you to spawn a shell on a remote machine.
### git
- Git is a version control system.
- What that means is git stores the entire history of a directory.
- We refer to the directory as a repository.
### Editors
### Clean Code
- Make your code modular using helper functions. If there is a repeated task, make them helper functions.
### Asserts
## Valgrind
- Valgrind is a suite of tools designed to provide debugging and profiling tools to make your programs more correct and detect some runtime issue.
- The most used of these tools in Memcheck, which can detect many memory-related errors that are common in C and C++ programs and that can lead to crashes and unpredictable behavior (for example, unfreed memory buffers).
- To run Valgrind on your program:
  - `valgrind --leak-chec=full --show-leak-kinds=all myprogram arg1 arg2`
### TSAN
- ThreadSanitizer is a tool from Google, built into clang and gcc, to help you detect race conditions in your code.
## GDB
- GDB is short for the GNU Debugger.
- GDB is a program that helps you track down errors by interactively debugging them.
- A breakpoint is a line of code where you want the execution to stop and give control back to the debugger.
### Shell
- A shell is a programming language that is running inside your terminal.
- A terminal is merely a window to input commands.
### Undefined Behavior Sanitizer
- It allows you to compile code with a runtime checker to make sure that you don;t do undefined behavior for various categories.
### Clang Static Build Tools
- Clang provides a great drop-in replacement tools for compiling programs.
- If you want to see if there is an error that may cause a race condition, casting error, etc, all you need to do is the following:
`$ scan-build make`
### strace and ltrace
- strace and ltrace are two programs that trace the system calls and library calls, respectively, of a running program or command.
- ltrace output can clue you in to weird things your program is doing live. Unfortunately, ltrace can't be used to inject faults, meaning that ltrace can tell you what is happening, but it can't tamper with what is already happening.
- strace on the other hand could modify your program.
  - Newer versions of strace can actually inject faults into your program.
### printfs
## Homework 0
- See /cs341pp/assignments/hw0
