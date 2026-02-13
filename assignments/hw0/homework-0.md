---
id: homework-0
aliases: []
tags: []
---

# Chapter 1
## Hello World (System call style)
- The systemy way of writing "Hello World":
```cpp
#include <unistd.h>

int main() {
  write(1, "Hello\n", 6);
  write(1, "World\n", 6);
  return 0;
}
```
### Hello World (System call style) Exercise
```cpp
#include <unistd.h>

int main() {
  write(1, "It be what it be\n", 17);
  return 0;
}
```
### Homework 0 Exercise
- See `homework0.cc`
## Hello Standard Error Stream
```cpp
#include <unistd.h>

int main() {
  int count;
  for (cout = 5; count; count--) {
    write(STDOUT_FILENO, "Hello\n", 6);
    write(STDERR_FILENO, ".", 1);
  }
  return 42;
}
```
### Hello Standard Error Stream Exercise
```cpp
#include <unistd.h>

int main() {
  int len;
  for (len = 0; len < 7; len++) {
    write(STDOUT_FILENO, "I think", 7 - len);
    write(STDOUT_FILENO, "\n", 1);
  }
  return 0;
  // return 7 -> echo $? == 7
  // return 1023 -> echo $? == 255
}
```
### Homework 0 Exercise
- See `homework0.cc`
## Writing to files
```cpp
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  int count;
  mode_t mode = S_IRUSR | S_IWUSR;
  int fildes = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
  write(fildes, "Great!\n", 7);
  close(fildes);
}
```
### Writing to files Exercise - 1
```cpp
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  mode_t mode = S_IRUSR | S_IWUSR;
  int filedes = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
  write(fildes, "hello!\n", 7);
  close(filedes);
  return 0;
}
```
### Writing to files Exercise - 2
```cpp
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  int my_fd = open("message.txt", O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR | S_IROTH);
  write(my_fd, "hello!\n", 7);
  close(my_fd);
  return 0;
}
```
### Homework 0 Exercise
- See `homework0.cc`
## Not everything is a system call
### Not everything is a system call Exercise
```cpp
#include <unistd.h>
#include <cstdio>

int main() {
  close(2);
  int my_fd = open("errors.txt", O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
  int another_fd = open("", O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
  if (another_fd == -1) {
    std::perror("Open syscall did not work!");
  }
  close(my_fd);
  return 0;
}
```
### Homework 0 Exercise
- See `homework0.cc`
# Chapter 2
## Not all bytes are 8 bits?
### Not all bytes are 8 bits? Exercise
```cpp
#include <cstdio>
#include <climits>

int main() {
  std::printf("Largest value you can store in a short is: %d\n", SHRT_MAX);
  std::printf("Largest value you can store in a long is: %ld\n", LONG_MAX);
  std::printf("There are %d bytes in a short\n", sizeof(short));
  std::printf("There are %d bytes in a long\n", sizeof(long));
  std::printf("There are %d bytes in a float\n", sizeof(float));
  std::printf("There are %d bytes in a double\n", sizeof(double));
  return 0;
}
```
## Follow the int pointer
### Follow the int pointer Exercise
```cpp
#include <cstdio>

int main() {
  int data[5] = {10, 30, 60, 50, 40};
  for (int i{}; i < 5; i++) {
    std::printf("%d, ", *(data + i));
  }
  printf("\n");
  data[0] = data[0] + data[4];
  data[4] = data[0] - data[4];
  data[0] = data[0] - data[4];
  for (int i{}; i < 5; i++) {
    std::printf("%d, ", *(data + i));
  }
  printf("\n");
  return 0;
}
```
## sizeof character arrays, incrementing pointers
- Machine code is readonly along with constant literals.
### sizeof character arrays, incrementing pointers - Exercise
```cpp
#include <cstdio>

int main() {
  char *ptr = "ABC0123";
  while (*ptr != '\0') {
    std::printf("%c %d\n", *ptr, *ptr);
    ptr++;
  }
  char *start_ptr = "dlroW elloH";
  char *end_ptr = start_ptr;
  while (*end_ptr != '\0') {
    end_ptr++;
  }
  while (end_ptr >= start_ptr) {
    std::printf("%c", *end_ptr--);
  }
  std::printf("\n");
  return 0;
}
```
# Chapter 3
## Program arguments argc argv
## Environment Variables
## String searching (Strings are just char arrays)
## Lifetime of automatic variables
# Chapter 4
## Malloc, heap and time
## Heap allocation Gotchas
## struct, typedefs and a linked list
## Duplicating strings, memory allocation and deallocation of structures
