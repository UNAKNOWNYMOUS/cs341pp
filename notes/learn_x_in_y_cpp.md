---
id: learn_x_in_y_cpp
aliases: []
tags: []
---

- C is a systems programming language.
- C++ is a almost a superset of C.
- `argc` indicates the number of arguments.
- and `argv` is an array of C-style strings (char*) representing the arguments.
- In C++, character literals are chars, therefore the size is 1.
- In C, character literals are ints, therefore the size is 4.
- C++ has strict prototyping:
```cpp
void func(); // function which accepts no arguments
void func(void); // same as earlier
```
- In C:
```c
void func(); // function which may accept any number of arguments with unknown type
void func(void); // function which accepts no arguments
```
- Use `nullptr` instead of `NULL` in C++
- Namespaces provide separate scopes for variable, function, and other declarations.
  - Namespaces can be nested.
- A `::` in the very front indicates global scope.
- C++ strings are mutable.
- Temporary objects are created whenever a function returns an object, and they are destroyed at the end of the evaluation of the enclosing expression. Well this is what the standard says, but compilers are allowed to change this behavior.
- The exception to the "at the end of the enclosing expression" rule is if a temporary object is bound to a const reference, in which case its life gets extended to the current scope:
```cpp
void constReferenceTempObjectFun() {
  // constRef gets the temporary object, and it is valid until the end of this function.
  const std::string &constRef = tempObjectFun();
  ...
}
```
