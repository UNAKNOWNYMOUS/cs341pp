#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;

// typedef struct Person Person;
//
// struct Person {
//   char *name;
//   int age;
//   Person **friends;
//   size_t num_friends;
//   size_t cap_friends;
// };

void homework_0_1_1();
void homework_0_1_2();
void write_triangle(int n);
void homework_0_1_3();
void homework_0_1_4();
void homework_0_1_5();
void homework_0_chapter2();
void homework_0_chapter3();
void homework_0_chapter4();
void homework_0_chapter5();
// Person *create(int age, char *name);
void destroy();

int main() {
  /* Answers to Homework 0 */
  homework_0_1_1();
  homework_0_1_2();
  homework_0_1_3();
  homework_0_1_4();
  homework_0_1_5();
  homework_0_chapter2();
  homework_0_chapter3();
  homework_0_chapter4();
  return 0;
}

/* Homework 0, Chapter 1, Exercise 1 */
void homework_0_1_1() {
  cout << endl;
  cout << "==================== Homework 0, Chapter 1, Exercise 1 "
          "==================== "
       << endl;

  cout << "Hello, World! (system call style) Write a program that uses "
          "'write()' to print out 'Hi! My name is <Your Name>'."
       << endl;

  write(1, "Hi! My name is UNAKNOWNYMOUS\n", 29);
}

/* Homework 0, Chapter 1, Exercise 2 */
void homework_0_1_2() {
  cout << endl;
  cout << "==================== Homework 0, Chapter 1, Exercise 2 "
          "==================== "
       << endl;

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
  cout << endl;
  cout << "==================== Homework 0, Chapter 1, Exercise 3 "
          "==================== "
       << endl;

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
  cout << endl;
  cout << "==================== Homework 0, Chapter 1, Exercise 3 "
          "==================== "
       << endl;

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
  cout << endl;
  cout << "==================== Homework 0, Chapter 1, Exercise 5 "
          "==================== "
       << endl;

  cout << "What are some differences between 'write()' and 'printf()'" << endl;
  cout << "A: The difference between 'write()' and 'printf()' is as "
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
  cout << endl;
  cout << "====================       Homework 0, Chapter 2       "
          "==================== "
       << endl;
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

/* Homework 0, Chapter 3 */
void homework_0_chapter3() {
  cout << endl;
  cout << "====================       Homework 0, Chapter 3       "
          "==================== "
       << endl;
  cout << "Program arguments, environment variables, and working with "
          "character arrays (strings)"
       << endl;

  /* Question 1 */
  cout << "1. What are at least two way to find the length of 'argv'?" << endl;
  cout << "A: Using 'argc' or walking the array of strings until the you hit "
          "the null byte."
       << endl;

  /* Question 2 */
  cout << "2. What does 'argv[0]' represent?" << endl;
  cout << "A: The program's name." << endl;

  /* Question 3 */
  cout << "Where are the pointers to enviornment variables stored (on the "
          "stack, the heap, somewhere else)?"
       << endl;
  cout << "A: The stack" << endl;

  /* Question 4 */
  cout
      << "On a machine where pointers are 8 bytes, and with the following code:"
      << endl;
  cout << "char *ptr = \"Hello\";\nchar array[] = \"Hello\";" << endl;
  cout << "What are the values of 'sizeof(ptr)' and 'sizeof(aray)'? Why?"
       << endl;
  cout << "A: 8 bytes on 64-bit systems and 6 bytes. Because for the first one "
          "takes the sizeof a pointer and the second one takes the sizeof the "
          "actual array including the null character."
       << endl;

  /* Question 5 */
  cout << "5. What data structure manages the lifetime of automatic variables?"
       << endl;
  cout << "A: The stack" << endl;
}

/* Homework 0, Chapter 4 */
void homework_0_chapter4() {
  cout << endl;
  cout << "====================       Homework 0, Chapter 4       "
          "==================== "
       << endl;
  cout << "Heap and stack memory, and working with structs." << endl;

  /* Question 1 */
  cout << "1. If I want to use data after the lifetime of the function it was "
          "created in ends, where should I put it? How do I put it there?"
       << endl;
  cout
      << "A: You can return the value, allocate it on the heap, or claim it in "
         "global scope. You accomplish this by using the 'return' keyword, "
         "using new or malloc-related functions, declare the variable outside "
         "of any functions."
      << endl;

  /* Question 2 */
  cout << "What are the differences between heap and stack memory?" << endl;
  cout << "The stack is used for activation records/functions - it is used for "
          "static allocation + is automatically allocates based on which "
          "function is called and the heap is for dynamic memory allocation"
       << endl;
  cout << "A: The stack stores function call frames (activation frames) and "
          "local variables with automatic storage duration. It is allocated "
          "and freed automatically in a LIFO manner as functions are called "
          "and return, and it's typically fast but limited in size. The heap "
          "is used for dynamic memory allocation where memory can outlive a "
          "function call; it is allocated and freed explicitly - is typically "
          "larger but slower, and can suffer from fragmentation."
       << endl;

  /* Question 3 */
  cout << "3. Are there other kinds of memory in a process?" << endl;
  cout << "A: Yes" << endl;

  /* Question 4 */
  cout << "4. Fill in the blank: \"In a good C program, for every malloc there "
          "is a __\""
       << endl;
  cout << "A: free" << endl;

  /* Question 5 */
  cout << "5. What is one reason 'malloc' can fail?" << endl;
  cout << "A: No more space on heap." << endl;

  /* Question 6 */
  cout << "6. What are some differences between 'time()' and 'ctime()'?"
       << endl;
  cout << "A: 'time()' is time after 1970s and 'ctime()' will convert this "
          "into a proper formatted date"
       << endl;

  /* Question 7 */
  cout << "7. What is wrong with this code snippet?" << endl;
  cout << "free(ptr);" << endl;
  cout << "free(ptr);" << endl;
  cout << "A: Double free - the process can be using the memory location for "
          "something -- which we have now just freed"
       << endl;

  /* Question 8 */
  cout << "What is wrong with this code snippet?" << endl;
  cout << "free(ptr);" << endl;
  cout << "printf(\"%s\n\", ptr);" << endl;
  cout << "A: Use after freed" << endl;

  /* Question 9 */
  cout << "9. How can one avoid the previous two mistakes?" << endl;
  cout << "A: By setting ptr to NULL" << endl;

  /* Question 10 */
  cout << "10. Create a 'struct' that represents a 'Person'. Then make a "
          "'typedef', so that 'struct Person' can be replaced with a single "
          "word. A person should contain the following information: their name "
          "(a string), their age (an integer), and a list of their friends "
          "(stored as a pointer to an array of pointers to 'Person's)."
       << endl;

  /* Question 11 */
  cout << "Now make two persons on the heap, \"Agent Smith\" and \"Sonny "
          "Moore\", who are 128 and 256 years old respectively and are friends "
          "with each other. Create functions to create and destroy a Person "
          "(Person's and their names should live on the heap)."
       << endl;
}

/* Homework 0, Chapter 5 */
void homework_0_chapter5() {
  cout << endl;
  cout << "====================       Homework 0, Chapter 4       "
          "==================== "
       << endl;
  cout << "Text input and output and parsing using 'getchar', 'gets', and "
          "'getline'."
       << endl;

  /* Question 1 */
  cout << "1. What functions can be used for getting characters from 'stdin' "
          "and writing them to ''stdout"
       << endl;
  cout << "A: printf, cout, fscanf, sscanf, scanf, getline, getchar, putchar, "
          "puts"
       << endl;

  /* Question 2 */
  cout << "2. Name one issue with 'gets()'." << endl;
  cout << "Buffer overflow - no check" << endl;

  /* Question 3 */
  // use sscanf

  /* Question 4 */
  // GNU SOURCE predirective
}

class Person {
public:
  Person(int age = 0, std::string name = "None", Person **friends = nullptr,
         size_t num_friends = 0, size_t cap_friends = 10)
      : age{age}, name{name}, num_friends{num_friends},
        cap_friends{cap_friends} {
    friends = new Person *[cap_friends];
  }
  ~Person() { delete[] friends; }
  Person **friends;
  size_t num_friends;

private:
  int age;
  std::string name;
  size_t cap_friends;
};

Person *agent_s = new Person(128, "Agent Smith");
Person *sonny_m = new Person(256, "Sonny Moore");
// agent_s->friends[num_friends++] = sonny_m;
// sonny_m->friends[num_firends++] = agent_s;

// Person *create(int age, const char *name) {
//   Person *new_person = (Person *)malloc(sizeof(Person));
//   if (!new_person) {
//     exit(1);
//   }
//   new_person->age = age;
//   new_person->name = (char *)malloc(strlen(name) + 1);
//   if (!new_person->name) {
//     exit(1);
//   }
//   strcpy(new_person->name, name);
//   new_person->num_friends = 0;
//   new_person->cap_friends = 10;
//   new_person->friends = (Person **)malloc(sizeof(Person *) *
//   new_person->cap_friends); memset(new_person->friends, 0, sizeof(Person *) *
//   new_person->cap_friends); if (!new_person->friends) {
//     exit(1);
//   }
//   return new_person;
// }
//
// void destroy(Person **person) {
//   free((*person)->name);
//   free((*person)->friends);
//   free((*person));
//   *person = nullptr;
// }
//
// Person *agent_s = create(128, "Agent Smith");
// Person *sonny_m = create(256, "Sonny Moore");
