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
