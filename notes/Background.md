---
id: Background
aliases: []
tags: []
---

# $ ./a.out
- Sometimes the journey of a thousand steps begins by learning to walk.
- NOTE: There seems to be an extra bullet point here.
## Systems Architecture
### Assembly
- Assembly is the lowest that you'll get to machine language without writing 1's and 0's.
- Each computer has an architecture, and that architecture has an associated assembly language.
  - Each assembly command has a 1:1 mapping to a set of 1's and 0's that tell the computer exactly what to do.
- NOTE: Should be: "For example, the following in the widely used x86 Assembly language adds one to the memory address 20..."
- Why do we mention this?
  - Because it is important that although you are going to be doing most of this class in C, that this is what the code is translated into.
### Atomic Operations
- An operation is atomic if no other processor should interrupt it.
- If an instruction is atomic, it makes sure that only one processor or thread performs any intermediate step at a time. With x86 this is done by the `lock` prefix.
  - Why don't we do this for everything? It makes commands slower! If every time a computer does something it has to make sure that the other cores or processors aren't doing anything, it'll be much slower.
### Caching
- The caching that we are referring to is processor caching.
- If a particular address is already in the cache when reading or writing, the processor will perform the operation on the cache, such as adding and updating the actual memory, later because updating memory is slow.
- If it isn't, the processor requests a chunk of memory from the memory chip and stores it in the cache, kicking out the least recently used page - this depends on caching policy, but Intel's does use this.
- This is done because I3 processor cache is three time faster to reach than the memory in terms of time though exact speeds will vary based on the clock speed and architecture.
- Naturally, this leads to problems because there are two different copies of the same value, in the cited paper this refers to an unshared line.
- This isn't a class about caching, but you should know how this could impact your code.
- A short but non-complete list on how caching could impact your code:
  - Race Conditions! If a value is stored in two different processor caches, then that value should be accessed by a single thread.
  - Speed. With a cache, your program may look faster mysteriously. Just assume that reads and writes that either happened recently or are next to each other in memory are fast.
  - Side effects. Every read or write affects the cache state. While most of the time this doesn't help or hurt, it is important to know. Check the Intel programmer guide on the lock prefix for more information.
### Interrupts
- An interrupt is internally an electrical signal that is delivered to the processor when something happens - this is a hardware interrupt.
  - Then the hardware decides if this is something that it should handle (e.g., handling keyboard or mouse input for older keyboard and mouses) or it should pass to the operating system.
    - The operating system then decides if this is something that it should handle (e.g., paging a memory table from disk) or something the application should handle (e.g., a SEGFAULT).
- If the operating system decides that this is something that the process or program should take care of, it sends a *software fault* and that software fault is then propagated.
- The application then decides if it is an error (SEGFAULT) or not (SIGPIPE for example) and reports to the user.
- Applications can also send signals to the kernel and to the hardware as well. This is an oversimplification because there are certain hardware faults that can't be ignored or masked away, but this class isn't about teaching you to build an operating system.
- An important application of this is how system calls are served!
- There is a well-established set of registers that the arguments go in according to the kernel as well as a system call "number" again defined by the kernel.
- Then the operating system triggers an interrupt which the kernel catches as serves the system call.
- Operating system developers and instruction set developers alike didn't like the overhead of causing an interrupt on a system call. Now, systems use `SYSENTER` and `SYSEXIT` which has a cleaner way of transferring control safely to the kernel and safely back.
### Optional: Hyperthreading
- Hyperthreading allows one physical core to appear as many cirtual cores to the operating system.
- The operating system can then schedule processes on these virtual cores and one core will execute them.
- Each core interleaves processes or threads.
- While the core is waiting for one memory access to complete, it may perform a few instructions of another process thread.
- The overall result is more instructions executed in a shorter time.
- This potentially means that you can divide the number of cores you need to power smaller devices.
## Debugging and Environments
### ssh
- `ssh` is short for the Secure Shell. It is a network protocol that allows you to spawn a shell on a remote machine.
### git
- Git is a version control system.
- What that means is git stores the entire history of a directory.
- We refer to the directory as a repository.
- Git is a decentralized version control system, meaning that you'll need to get a repository onto your VM.
### Editors
### Clean Code
- Make your code modular using helper functions. If there is a repeated task, make them helper functions.
### Asserts
- Use assertions to make sure your code works up to a certain point - and importantly, to make sure you don't break it later.
## Valgrind
- Valgrind is a suite of tools designed to provide debugging and profiling tools to make your programs more correct and detect some runtime issue.
  - The most used of these tools is Memcheck, which can detect many memory-related errors that are common in C and C++ programs and that can lead to crashes and unpredictable behaviour.
- The most used of these tools in Memcheck, which can detect many memory-related errors that are common in C and C++ programs and that can lead to crashes and unpredictable behavior (for example, unfreed memory buffers).
- To run Valgrind on your program:
  - `valgrind --leak-chec=full --show-leak-kinds=all myprogram arg1 arg2`
- Arguments are optional and the default tool that will run is Memcheck.
- Valgrind is a effective tool to check for errors at runtime.
### TSAN
- ThreadSanitizer is a tool from Google, built into clang and gcc, to help you detect race conditions in your code.
- Note, that running with tsan will slow your code down a bit.
## GDB
- GDB is short for the GNU Debugger.
- GDB is a program that helps you track down errors by interactively debugging them.
- A breakpoint is a line of code where you want the execution to stop and give control back to the debugger.
- A useful trick when debugging complex C programs with GDB is setting breakpoints in the source code.
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