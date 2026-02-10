#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

void homework_0_1_1();
void homework_0_1_2();
void write_triangle(int n);
void homework_0_1_3();
void homework_0_1_4();
void homework_0_1_5();
void homework_0_chapter2();

int main() {
  /* Answers to Homework 0 */
  homework_0_1_1();
  homework_0_1_2();
  homework_0_1_3();
  homework_0_1_4();
  homework_0_1_5();
  homework_0_chapter2();
  return 0;
}

/* Homework 0, Chapter 1, Exercise 1 */
void homework_0_1_1() {
  cout << "\nHomework 0, Chapter 1, Exercise 1" << endl;
  cout << "Hello, World! (system call style) Write a program that uses "
          "'write()' to print out 'Hi! My name is <Your Name>'."
       << endl;
  write(1, "Hi! My name is UNAKNOWNYMOUS\n", 29);
}

/* Homework 0, Chapter 1, Exercise 2 */
void homework_0_1_2() {
  cout << "\nHomework 0, Chapter 1, Exercise 2" << endl;
  cout << "Hello, Standard Error Stream! Write a function to print out a "
          "triangle of height 'n' to standard error. Your function should have "
          "the signature 'void write_triangle(int n)' and should use 'write()'."
       << endl;
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
  cout << "\nHomework 0, Chapter 1, Exercise 3" << endl;
  cout << "Writing to files Take your program from 'Hello, World!' modify it "
          "write to a file called 'hello_world.txt'. Make sure to use correct "
          "flags and a correct mode for 'open()' ('man 2 open' is your friend)."
       << endl;
  mode_t mode = S_IRUSR | S_IWUSR;
  int my_fd = open("hello_world.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
  write(my_fd, "Hello, World!1\n", 14);
  close(my_fd);
}

/* Homework 0, Chapter 1, Exercise 4 */
void homework_0_1_4() {
  cout << "\nHomework 0, Chapter 1, Exercise 4" << endl;
  cout << "Not everything is a system call Take your program from "
          "'Writing to files' and replace 'write()' with 'printf()'. Make "
          "sure to print to the file instead of standard out!"
       << endl;
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
  cout << "\nHomework 0, Chapter 1, Exercise 5" << endl;
  cout << "What are some differences between 'write()' and 'printf()'" << endl;
  cout << "The difference between 'write()' and 'printf()' is as "
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
       << endl;
}

/* Homework 0, Chapter 2 */
void homework_0_chapter2() {
  cout << "\nHomework 0, Chapter 2" << endl;
  cout << "Sizing up C types and their limits, 'int' and 'char' arrays, and "
          "incrementing pointers"
       << endl;

  /* Question 1 */
  cout << "1. How many bits are there in a byte?" << endl;
  cout << "A: At least 8 bits" << endl;

  /* Question 2 */
  cout << "2. How many bytes are there in a 'char'?" << endl;
  cout << "A: 1 byte." << endl;

  /* Question 3 */
  cout << "3. How many bytes the following are on your machine? 'int', "
          "'double', 'float', 'long', and 'long long'"
       << endl;
  cout << "A:" << endl;
  cout << "Size of int is: " << sizeof(int) << "bytes" << endl;
  cout << "Size of double is: " << sizeof(double) << "bytes" << endl;
  cout << "Size of float is: " << sizeof(float) << "bytes" << endl;
  cout << "Size of long is: " << sizeof(long) << "bytes" << endl;
  cout << "Size of long long is: " << sizeof(long long) << "bytes" << endl;

  /* Question 4 */
  cout << "4. On a machine with 8 byte integers, the declaration for the "
          "variable 'data' is 'int data[8]'. If the address of data is "
          "'0x7fbd9d40', then what is the address of 'data+2'?"
       << endl;
  cout << "A: 0x7fbd9d50" << endl;

  /* Question 5 */
  cout << "5. What is 'data[3]' equivalent to in C? Hint: what does C convert "
          "'data[3]' to before dereferencing the address? Remember, the type "
          "of a string constant 'abc' is an array."
       << endl;
  cout << "A: char * and it is equivalent to '*(data + 3)'." << endl;

  /* Question 6 */
  cout << "6. Why does this SEGFAULT?" << endl;
  cout << "char *ptr = \"hello\";\n*ptr = 'J';" << endl;
  cout << "A: Constant literals are readonly so this is trying to write to "
          "that - which is invalid."
       << endl;

  /* Question 7 */
  cout << "7. What is the value of the variable 'str_size'?" << endl;
  cout << "ssize_t str_size = sizeof(\"Hello\0World\");";
  cout << "A: 12 bytes" << endl;

  /* Question 8 */
  cout << "8. What is the value of the variable 'str_len'" << endl;
  cout << "ssize_t strlen = strlen(\"Hello\0World\");" << endl;
  cout << "A: 5" << endl;

  /* Question 9 */
  cout << "9. Give an example of X such that 'sizeof(X)' is 3" << endl;
  cout << "A: 'sizeof(\"hi\");'" << endl;

  /* Question 10 */
  cout << "10. Give an example of Y such that 'sizeof(Y)' might be 4 or 8 "
          "depending on the machine."
       << endl;
  cout << "A: long" << endl;
}
