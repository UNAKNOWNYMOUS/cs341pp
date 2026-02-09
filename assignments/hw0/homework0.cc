#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

void homework_0_1_1();
void homework_0_1_2();
void write_triangle(int n);
void homework_0_1_3();
void homework_0_1_4();
void homework_0_1_5();

int main() {
  /* Answers to Homework 0 */
  homework_0_1_1();
  homework_0_1_2();
  homework_0_1_3();
  homework_0_1_4();
  homework_0_1_5();
  return 0;
}

/* Homework 0, Chapter 1, Exercise 1 */
void homework_0_1_1() {
  std::cout << "\nHomework 0, Chapter 1, Exercise 1" << std::endl;
  std::cout << "Hello, World! (system call style) Write a program that uses "
               "'write()' to print out 'Hi! My name is <Your Name>'."
            << std::endl;
  write(1, "Hi! My name is UNAKNOWNYMOUS\n", 29);
}

/* Homework 0, Chapter 1, Exercise 2 */
void homework_0_1_2() {
  std::cout << "\nHomework 0, Chapter 1, Exercise 2" << std::endl;
  std::cout
      << "Hello, Standard Error Stream! Write a function to print out a "
         "triangle of height 'n' to standard error. Your function should have "
         "the signature 'void write_triangle(int n)' and should use 'write()'."
      << std::endl;
  write_triangle(3);
}

void write_triangle(int n) {
  for (int i{}; i < n; i++) {
    for (int j{i}; j >= 0; j--) {
      write(1, "*", 1);
    }
    write(1, "\n", 1);
  }
}

/* Homework 0, Chapter 1, Exercise 3 */
void homework_0_1_3() {
  std::cout << "\nHomework 0, Chapter 1, Exercise 3" << std::endl;
  std::cout
      << "Writing to files Take your program from 'Hello, World!' modify it "
         "write to a file called 'hello_world.txt'. Make sure to use correct "
         "flags and a correct mode for 'open()' ('man 2 open' is your friend)."
      << std::endl;
  mode_t mode = S_IRUSR | S_IWUSR;
  int my_fd = open("hello_world.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
  write(my_fd, "Hello, World!1\n", 14);
  close(my_fd);
}

/* Homework 0, Chapter 1, Exercise 4 */
void homework_0_1_4() {
  std::cout << "\nHomework 0, Chapter 1, Exercise 4" << std::endl;
  std::cout << "Not everything is a system call Take your program from "
               "'Writing to files' and replace 'write()' with 'printf()'. Make "
               "sure to print to the file instead of standard out!"
            << std::endl;
  // close(1);
  int my_fd =
      open("hello_world.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
  std::printf("Hello, World!2\n");
  if (my_fd != -1) {
    close(my_fd);
  }
}

/* Homework 0, Chapter 1, Exercise 5 */
void homework_0_1_5() {
  std::cout << "\nHomework 0, Chapter 1, Exercise 5" << std::endl;
  std::cout << "What are some differences between 'write()' and 'printf()'"
            << std::endl;
  std::cout
      << "The difference between 'write()' and 'printf()' is as "
         "follows:\n'write()' is a low-level interface that directly requests "
         "the operating system kernel to write a specific number of raw bytes "
         "from memory to a file descriptor. It offers less functionality but "
         "provides direct control over I/O operations and can be crucial for "
         "tasks requiring immediate output or in specific system-level "
         "programming contexts.\n'printf()' is a high-level, user-friendly "
         "function for controlled, formatted output of various data types. It "
         "manages an internal buffer and only interacts with the operating "
         "system's 'write()' system call when the buffer is full or flushed, "
         "which is more efficient for performance."
      << std::endl;
}
