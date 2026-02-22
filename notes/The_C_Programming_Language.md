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
### Input / Output
- Every process has three streams of data when it starts execution: standard input, standard output, standard error.
- They're file descriptors are 0, 1, 2 respectively.
- 2 is reserved for standard error which by library convention is unbuffered (i.e. IO operations are performed immediately).
- ISO defines three types of stream:
  - Unbuffered, where the contents of the stream reach their destination as soon as possible.
  - Line Buffered, where the contents of the stream reach their destination as soon as a newline is provided.
  - Fully Buffered, where the contents of the stream reach their destination as soon as the buffer is full.
- One can force a write by calling `fflush()` on the stream.
### stdin oriented functions
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
