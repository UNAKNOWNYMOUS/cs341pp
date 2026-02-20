---
id: The_C_Programming_Language
aliases: []
tags: []
---

# Introc
- If you want to teach systems, don't drum up the programmers, sort the issues, and make PRs. Instead, teach them to yearn for the vast and endless C. - Antoine de Saint-Exupery (With edits).
- C is the de-facto programming language to do serious systems programming.
  - Most kernels have their API accessible through C.
## History of C
- C was developed by Dennis Ritchie and Ken Thompson at Bell Labs back in 1973.
- C was two-fold: it was made to target the most popular computers at the time, such as the PDP-7. It tried to remove some of the lower-level constructs (managing registers, and programming assembly for jumps), and create a language that had the power to express programs procedurally (as opposed to mathematically like LISP) with readable code.
  - All this while still having the ability to interface with the operating system.
- The first "real" standardization was with the Brian Kernighan and Dennis Ritchie's book.
- The K&R book is known as the de-facto standard for learning C.
- We will be mainly focusing on is the POSIX C library which extends ISO.
- The Linux kernel fails to be POSIX compliant.
  - Linux developers didn't want to pay the fee for compliance.
  - Did not want to be fully compliant with multitude of different standard because that meant increased development costs to maintain compliance.
- Features of C:
  - Speed
  - Simplicity
  - Manual Memory Management
  - Ubiquity
## Crash course introduction to C
### Preprocessor
- What is the preprocessor?
  - Preprocessing is a copy and paste operation that the compiler performs *before* actually compiling the program.
- There are side effects to the preprocessor though.
  - One problem is that the preprocessor needs to be able to tokenize properly, meaning trying to redefine the internals of the C language with a preprocessor may be impossible.
  - Another problems is that they can't be nested infinitely - there is a bounded depth where they need to stop.
- Macros are also simple text substitutions, without semantics.
- There are also logical problems with the flexibility of certain parameters.
## Language Facilities
### Keywords
- In systems programming, the only type of memory that you can't write to is system write-protected memory.
- If you are going to use abstraction, try not to break it.
- C-structs are contiguous regions of memory that one can access specific elements of each memory as if they were separate variables.
  - Note that there might be padding between elements, such that each variable is memory-aligned (starts at a memory address that is a multiple of its size).
### C data types
### Operators
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
### C System Calls
## Common C Functions
### Handling Errors
### Input / Output
- Every process has three streams of data when it starts execution: standard input, standard output, standard error.
