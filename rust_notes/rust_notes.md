---
id: rust_notes
aliases: []
tags: []
---

# Rust Basics
## Rust: Defining Variables
### Variables
- In Rust, variables are defined using the `let` keyword.
```rust
let team_name = "Rustaceans";
```
- By default, Rust variables are immutable.
- Once defined, its value can't be changed.
```rust
let team_name = "Rustaceans";
team_name = "Crustaceans"; // This raises an error!
```
- Question: What keyword is used to define a variable in Rust?
- Answer: `let`
### Mutability
- The `mut` keyword can be used to define a variable that can change, i.e. a "mutable" variable.
```rust
let team_name = "Rustaceans";
team_name = "Crustaceans"; // This raises an error!

let mut mutable_team_name = "Rustaceans";
mutable_team_name = "Crustaceans"; // This doesn't error
```
- Question: How do you define a mutable variable?
- Answer: `let mut name = "Norm";`
### Summary
- In this concept, we learned about the following:
  - Variables: The `let` keyword is used to define variables. Variables are immutable by default.
  - Mutability: The `mut` keyword is used to make variables mutable.
## Rust: Printing to console
- The most common way to write to console in Rust is using `println!`:
```rust
// This prints "Hello world" to the console
println!("Hello world");
```
- Rust offers other ways to print to console too, like `print!`, `eprint!`, and `eprintln!`.
- Question: Which of the following prints to console in Rust?
- Answer: `println!("Hello world");`
- `print!` is similar to `println!`, but it doesn't append a newline.
```rust
// Prints "This is a single line"
print!("This is a single");
print!("line");
```
- `eprint!` and `eprintln!` print to stderr (standard error stream) instead of stdout. They're commonly used when printing error messages.
```rust
println!("Printing to stdout");
eprintln!("Printing to stderr");
```
- The `e` prefix stands for "error".
### Summary
- We covered the following utilities in the Rust standard library:
  - `println!` - Prints a string to console and appends a newline at the end.
  - `print!` - Similar to `println!` but doesn't append a newline at the end.
  - `eprintln!` - Similar to `println!` but prints to stderr instead of stdout.
  `eprint!`- Similar to `print!` but prints to stderr instead of stdout.
## Rust: Data Types Overview
- Being a statically typed language, Rust requires that every variable's type is known at compile time.
### Type Annotations
- To specify a variable's type, you'd add a type annotations like this:
```rust
// Here, we're specifying that 'flag' is of type 'bool'
let flag: bool = true;
```
- Question: In the code block below, what does ` : bool` do?
```rust
let need_coffee: bool = true;
```
- Answer: It's specifies that the variable's type is `bool`.
### Type Inference
- In many cases, a type annotation might not be required. The Rust compiler is clever; it can infer the type we intend to use based on the value and how it's used.
```rust
// Here the compiler infers 'flag' is a bool due to its value being 'true'
let flag = true;
```
- Question: How does Rust infer types if a type annotation is not present?
- Answer: Infers based on the value and its usage.
### Scalar types
- A scalar type represents a single value.
- Rust has 4 scalar types -- integers, floating-point numbers, booleans, and characters.
```rust
let x = 42; // Integer
let x = 4.2; // Float
let x = true; // Boolean
let x = 'a'; // Char
```
### Compound types
- Compound types group multiple values into a single type.
- The two primary compound types in Rust are tuples and arrays. Here's a quick overview:
```rust
// This is a tuple. It can group multiple values of different types.
let chess_square = (5, 'A');

// This is an array. It can group multiple values of the same type.
let array_of_ints = [1, 2, 3];
```
### Summary
  - Type inference: Rust can infer variable types at compile time, but sometimes it needs explicit annotations for clarity.
  - Scalar types: types that hold a single value. Examples: integers, floating-point numbers, booleans, characters.
  - Compound types: types that group multiple values. Examples: tuples, arrays.
