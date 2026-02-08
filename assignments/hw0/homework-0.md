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
1. *Hello, World! (system call style)* Write a program that uses `write()` to print out "Hi! My name is <Your Name>".
```cpp
#include <unistd.h>

int main() {
  write(1, "Hi! My name is UNAKNOWNYMOUS\n", 29);
  return 0;
}
```
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

