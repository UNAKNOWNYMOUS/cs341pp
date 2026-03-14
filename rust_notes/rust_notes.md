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
## Rust: Scalar Data Types
- Rust has 4 scalar data types:
  - Integers
  - Floating-points
  - Booleans
  - Characters
### Integer Types
- Example include `i32`, `u32`, `i64`, and `u64`.
  - The `i` in `i32` and `i64` means they're "signed". They can be negative, zero, or positive.
  - The `u` in `u32` and `u64` means they're "unsigned". They can only be zero or positive.
- The number at the end (like `32` or `64`) indicates how much space the integer uses in memory.
```rust
let x: i32 = -5 // A signed 32-bit integer
let y: u64 = 5000000000; // An unsigned 64-bit integer.
```
- Question: How are the `i32` and `i64` types different?
- Answer: `i64` takes up more memory than `i32`.
### Integer type inference
- If a value is a number and a type annotation is not present, Rust will infer the type as `i32`.
```rust
let x = 5; // Inferred type is 'i32'
```
- However, if a value doesn't fit in `i32`, a type annotation is required.
- For example, 5000000000 is beyond the `i32` limit:
```rust
// This results in a compile-time error!
// let y = 5000000000;

let y: u64 = 5000000000; // This works
```
- In the below code block, what is the inferred type for `x`?
```rust
let x = 42;
```
- Answer: `i32`
### Floating-point types
- Floating-point types are always signed, i.e. they support both positive and negative numbers.
  - `f64` is a 64-bit number, offering a precision up to 15 decimal places. It's the default choice for most applications that prioritize accuracy.
  - `f32` is a 32-bit number, offering a precision up to 7 decimal places. It's chosen when speed is more crucial than precision, such as graphics processing.
```rust
let current_position: f32 = 5.0; // Using f32 for faster graphics rendering
let pi: f64 = 3.141592653589793; // Using f64 for precise representation
```
- Question: In Rust, which floating point type offers the highest precision?
- Answer: `f64`
### Floating-point type inference
- When a value is a float but a type annotation isn't provided, Rust infers the type to be `f64`.
```rust
let pi = 3.141592653589793; // Inferred type as 'f64'
```
- Question: In the below code block, what is the inferred type for `x`?
```rust
let x = 3.14;
```
- Answer: `f64`
### The boolean type
- In Rust, the boolean type is `bool`.
```rust
let rust_is_cool: bool = false; // Explicit type annotation
```
### Boolean type inference
- If the value of a variable is either `true` or `false`, Rust will automatically infer the type to be `bool`.
```rust
let rust_is_cool = true; // Inferred type as 'bool'
```
- Question: Which are the possible values for the `bool` type in Rust?
- Answer: `true` and `false`
### Characters
- The `char` type represents a single unicode character, like `a` or `🦀`.
```rust
let rust_mascot: char = '🦀';
```
- Note that characters need to be defined using single quotes (''), not double quotes.
### Character type inference
- If the value of a variable is defined using single quotes (i.e. it is a "character literal"), Rust will automatically infer the type to be `char`.
```rust
let rust_mascot = '🦀'; // Inferred type as 'char'
```
- Question: In the below code block, what is the inferred type for `rust_mascot`?
```rust
let rust_mascot = '🦀';
```
- Answer: `char`
### Summary
- We covered the 4 scalar data types that Rust supports:
  - Integer types (`i8`, `i16`, ...)
    - Signed (`i*`) and unsigned (`u*`) integers with different sizes.
  - Floating-point type (`f32`, `f64`)
    - `f32` (single precision) and `f64` (double precision).
  - The Boolean type (`bool`)
    - `true` or `false`
  - The Character type (`char`)
    - Represents a Unicode scalar value.
## Rust: Tuples
- Tuple is a Rust data type that is used to group multiple values.
- It's defined using parentheses, for example:
```rust
// Here (char i32) is variable's type, and ('A', 5) is the value assigned to it
let chess_square: (char, i32) = ('A', 5);
```
- Tuples have a fixed length. Their values must always contain the same number of elements as mentioned in the type signature:
```rust
let tuple_with_2_ints: (i32, i32) = (1, 2);
let tuple_with_3_ints: (i32, i32, i32) = (1, 2, 3);

// This is invalid because the value has < 3 elements
// let tuple_with_3_ints: (i32, i32, i32) = (1, 2);

// This is invalid too because the value has > 3 elements
// let tuple_with_3_ints: (i32, i32, i32) = (1, 2, 3, 4);
```
- The elements in a tuple can be of different types, but they should be in the same order as mentioned in the type signature:
```rust
let tuple_with_int_and_char: (i32, char) = (1, 'A');

// This is a compile-time error because the value has 'char' as the first type, not 'i32'
// let tuple_with_int_and_char: (i32, char) = ('A', 1);
```
- Question: If a variable's type is `(i32, i32)` (i.e. a tuple), how many values can it hold?
- Answer: 2 integers
### Type Inference
- In most cases, you don't need to annotate the type for a tuple. If a value is surrounded by parentheses and no type annotation is present, Rust infers the type based on the values used.
```rust
// Here the inferred type is (i32, char)
let tuple_with_int_and_char = (1, 'A');
```
- Question: In the following code block, what is the inferred type of `x`?
```rust
let x = (1, 'A');
```
- Answer: `(i32, char)`
### Accessing elements in a tuple
- The elements in a tuple can be accessed using two primary methods -- indexing and destructuring.
#### Indexing
- Indexing is done by appending `.<index>` to the variable name:
```rust
let chess_square = ('A', 5);

chess_square.0; // Return 'A'
chess_square.1; // Returns '5'
```
- Indexes are 0-based.
- Attempting to access invalid indexes will raise a compile-time error:
```rust
let chess_square = ('A', 5);

chess_square.0; // Returns 'A'
chess_square.1; // Returns '5'

// This'll throw a compile-time error
// chess_square.2;
```
- Question: If a tuple `x` is of type `(i32, i32)`, what happens when you try to access `x.5`?
- Answer: A compile-time error is raised.
### Destructuring
- Destructuring works by assigning multiple variables to the value at once:
```rust
let chess_square = ('A', 5);
let (column, row) = chess_square; // column is 'A', row is 5.
```
- Destructuring requires that the number of variables on the left-hand side match the length of the tuple.
```rust
let chess_square = ('A', 5);

// This fails because the left-hand side only contains one value
// let (column) = chess_square;

// This fails because the left-hand side only contains >2 values
// let (column, row, index) = chess_square;

// This works because the left-hand size contains exactly 2 values
let (column, row) = chess_square;
```
### Summary
- In this concept we covered Tuples, a Rust data type that is used to group multiple values.
  - Tuples have a fixed length
  - Tuples can contain elements of multiple types
  - Tuples types are defined using parentheses like this: `(char, i32)`
  - Elements in a tuple can be accessed using two methods:
    - Indexing -- `chess_square.0`, `chess_square.1`
    - Destructuring -- `let (row, column) = chess_square`
## Rust: Arrays
- Array is a Rust data type that is used to store multiple values of the same type.
- Arrays are defined using square brackets, for example:
```rust
// An array of 3 booleans
let checks: [bool; 3] = [true, false, true];
```
- Question: What of the following is a valid array type in Rust?
- Answer: `[bool; 4]`
- Just like tuples, arrays have a fixed length. Their values must always contain the same number of elements as mentioned in the type signature:
```rust
let array_with_2_ints: [i32; 2] = [1, 2];
let array_with_3_ints: [i32; 3] = [1, 2, 3];

// This is invalid because the value has < 3 elements
// let array_with_3_ints: [i32; 3] = [1, 2];

// This is invalid too because the value has > 3 elements
// let array_with_3_ints: [i32; 3] = [1, 2, 3, 4];
```
- Unlike tuples, elements in an array need to be of the same type.
```rust
// Invalid because the second value isn't an integer
// let array_of_ints: [i32; 2] = [1, 'A']

// Valid because both values are integers
let array_of_ints: [i32; 2] = [1, 2];
```
- Question: How are tuples and arrays different in Rust?
- Answer: Tuples can hold values of different types, arrays can't.
### Type Inference
- In most cases, you don't need to annotate the type for an array. If a value is surrounded by square brackets and no type annotation is present, Rust infers the type based on the values used.
```rust
// Here the inferred type is [i32; 3]
let array_with_3_ints = [1, 2, 3];
```
### Accessing elements in an array
- Similar to tuples, the elements in an array can be accessed using two primary methods - indexing and destructuring.
```rust
let array_with_3_ints = [1, 2, 3];

// Indexation
array_with_3_ints[0]; // Returns 1
array_with_3_ints[1]; // Returns 2
array_with_3_ints[2]; // Returns 3

// Destructuring
let [a1, a2, a3] = array_with_3_ints; // Assigns a1 to 1, a2 to 2, and a3 to 3.
```
### Summary
- In the concept we covered Arrays, a Rust data type that is used to group multiple values of the same type.
  - Arrays have a fixed length
  - Arrays must contain elements of the same type
  - Array types are defined using square brackets like this: `[i32; 4]`
  - Elements in an array can be accessed using two methods:
    - Indexing -- `array_of_values[0`, `array_of_values[1]`
    - Destructuring -- `let [a1, a2, a3] = array_of_values`
## Rust: Control Flow
- In Rust, program execution flow is managed primarily using `if` and various loops.
### The `if` keyword
- Like most language, Rust includes an `if` keyword to conditionally evaluate code.
```rust
let temperature = 8;

if temperature <= 10 {
  println!("The weather is cold");
}

// Outputs: "The weather is cold"
```
- The condition you provide to `if` must be a `bool`.
- If the condition isn't a `bool`, the Rust compiler will complain.
```rust
let temperature = 8;

// This would error! Expected `bool`, found integer
// if temperature {
//    println!("the weather is cold");
//}
```
### Multiple conditions with the `if else` keyword
- You can evaluate multiple conditions by combining `if`, `else`, `else if`.
- For instance:
```rust
let temperature = 15;

if temperature <= 10 {
  println!("The weather is cold");
} else if temperature <= 20 {
  println!("The weather is cool");
} else {
  println!("The weather is warm");
}

// Outputs: "The weather is cool"
```
### Variable assignment with `if` expressions
- You can also assign the result of an `if` expression.
- In the example below, `weather` is getting assigned by the result of the `if` expression.
```rust
let temperature = 15;

let weather = if temperature <= 10 {
  "cold"
} else if temperature <= 20 {
  "cool"
} else {
  "warm"
};

println!("The weather is {}", weather); // The weather is cool
```
- Question: Determine if the code provided below will compile. If it does compile, what is the expected output?
```rust
let first_name = "Norm";
let status = if first_name { "Sinbad" } else { "Sinworse" };

println!("{}", status);
```
- Answer: Program does not compile
### Type consistency in `if` expressions
- Rust requires all branches of an `if` expression to return the same type.
- The last expression of each branch determines the value and type returned by the block.
- For instance:
```rust
let flag = false;

// This would error!
// let six = if flag { 6 } else { "six" };
```
### Looping
- There are three types of loops in Rust -- `loop`, `while`, and `for`.
### The `loop` keyword
- `loop` creates an infinite loop. Use `break` to exit.
```rust
let mut attempts = 0;

loop {
  println!("Connecting...");
  attempts += 1;
  if attempts >= 3 {
    println!("Failed after 3 attempts.");
    break;
  }
}
```
### The `while` keyword
- `while` creates a loop that runs as long as its condition remains true.
```rust
let mut battery_percentage = 100;

while battery_percentage > 0 {
  println!("Battery: {}%", battery_percentage);
  battery_percentage -= 10;
}
```
- Question: When does the `while` loop stop?
- Answer: When its condition becomes false
### The `for` keyword
- `for` creates a loop that runs within a specified range.
- Ranges can be either exclusive or inclusive.
- Exclusive ranges (`..`) include the start value, but exclude the end value.
```rust
// Using exclusive range (..)
for number in 1..4 {
  // This loop iterates over values 1, 2, and 3.
  println!("Count: {}", number);
}
```
- Inclusive ranges (`..=`) include both the start and end values.
```rust
// Using inclusive range (..=)
for inclusive_num in 1..=3 {
  // This loop iterates over values 1, 2, and 3.
  println!("Inclusive count: {}", inclusive_num);
}
```
- Question: Using a `for` loop, how do you iterate over a range of numbers from 1 to 4 (inclusive) in Rust?
- Answer: `for number in 1..=4`
### Summary
- In this concept, we learned about control flows in Rust:
  - Conditional Expressions:
    - The `if` keyword facilitates conditional block evaluations
    - Results of `if` expressions can be assigned to variables using `let`
  - Loop Constructs:
    - `loop`: Initiates an endless loop, which only halts upon encountering a `break` statement or an external intervention.
    - `while`: Iterates as long as the given condition holds true.
    - `for`: Ideal for iterating over sequences, such as array elements or iterator outputs.
## Rust: Functions
- In Rust, we begin functions using `fn`.
### Basic syntax
- Here's a basic function called `sing` that prints a `String`:
```rust
fn sing() {
  println!("la la la LA LA");
}
```
- Question: How do you initiate a function definition in Rust?
- Answer: `fn greet()`
### Parameters and return values
- Functions can take inputs and give back outputs.
- Here's how you can make a function called `add` that takes two numbers and returns their sum:
```rust
fn add(x: i32, y: i32) -> i32 {
  x + y
}
```
- Question: Interpret the function signature below:
```rust
fn always_blue(a: String, b: i32) -> bool
```
- Answer: `always_blue` takes a `String` and an `i32` and returns a `bool`
### Return behavior
- In Rust, a function's last expression is automatically its returned value, as long as it's not followed by a semicolon.
- For example, the following function returns the square of a number.
```rust
fn sqaure(x: i32) -> i32 {
  x * x
}

let result = sqaure(3);
println!("{result}"); // 9
```
- Question: What is implied when a Rust function concludes with an expression that doesn't end in a semicolon?
- Example:
```rust
fn mult(a: i32, b: i32) -> i32 {
  a * b // <- notice no semicolon!
}
```
- Answer: The function will yield a expression as a return value
- What if you add a semicolon to the last expression?
- If you add a semicolon to the end of a function's last expression, it makes the function return `()`. If the function signature specifies a different return type, you'll encounter a compile-timer error.
- For instance:
```rust
fn sqaure(x: i32) -> i32 {
  // x * x; Error! Expected return type `Integer` but found `()`
}
```
- Question: What happens to this function?
```rust
fn sub(a: i32, b: i32) -> {
  a - b;
}
```
- Answer: It will cause a compile-time error due to the wrong return type.
### Using the `return` keyword
- If you prefer to be explicit with your return statements, Rust still supports using the `return` keyword.
```rust
fn square(x: i32) -> i32 {
  return x * x; // <-- also valid!
}
```
- Whether you choose to use the `return` keyword boils down to personal preference.
### Summary
- Function declaration: Functions are declared using the `fn` keyword with types arguments. Return types are defined using the `->` notation.
- Expressive return mechanism: In Rust, the value of the final expression in a function serves as its return value, provided it doesn't end with a semicolon. Ending an expression with a semicolon causes it to return `()`, an empty tuple.
- Explicit `return` keyword: Rust allows the use of the `return` keyword for early exits of clarity, but it's optional when returning the value of the final expression.
## Rust: Ownership
- To ensure thread safety, Rust uses unique concept called ownership.
- In Rust, each piece of data can have only one owner at a time.
### Transferring ownership
- When you assign a value from one variable to another, the ownership can shift.
- For complex types, this means the original variable can't be used anymore:
```rust
let s1 = String::from("hello");
let s2 = s1; // Ownership passes from s1 to s2

println!("{}", s2): // "hello"
// println!("{}", s1); // This would error because s1 can no longer be used
```
- Question: If you transfer the ownership of a variable in Rust, what happens to the original variable?
- Answer: It's rendered unusable
### Copying simple data types
- Not all data types in Rust have strict ownership rules.
- Simple types, like integers, are copied instead of having their ownership transferred:
```rust
let num1 = 5;
let num2 = num1; // num1 is copied, not transferred

println!("{}", num1); // 5, Totally valid!
println!("{}", num2); // 5, Also valid!
```
- Question: Which of the following statements is true regarding integers in Rust?
- Answer: They get copied, not transferred.
### Exceptions to the rule?
- If Rust has such a strict ownership rule, how come some types, like integers, seem to behave differently?
- Let's explore this further.
### Copy vs. non-copy types
- Rust categorizes data types into `Copy` and `non-Copy`.
- This distinction is central to Rust's memory management approach.
- Copy: Simple scalar types like integers, bool, and characters.
- When assigned to another variable, they get copied.
- The original remains untouched.
- For instance:
```rust
let is_active = true;
let is_duplicate = is_active;

println!("{}", is_active); // "true"
println!("{}", is_duplicate); // "true"
```
- Question: You have the following code:
```rust
let a = true;
let b = a;
println!("{}", a);
```
- What is the output of the code?
- Answer: `true`
- Non-Copy: Types such as `String` or `Vec`.
- When assigned, they transfer ownership, making the original unusable.
- For instance:
```rust
let text1 = String::from("Hello, word!");
let text2 = text1;

println!("{}", text2); // Outputs: Hello, world!
// println!("{}", text1); // This would error because text1 can no longer be used
```
- Question: Consider the code:
```rust
let str1 = String::from("Rust");
let str2 = str1;
println!("{}", str1);
```
- What will this code result in?
- Answer: Compilation error due to `str1` being unusable
### Summary
- Ownership in Rust: Rust has a unique ownership model for memory safety. Each data piece has one owner, and using a variable after transferring its ownership leads to an error, ensuring that data isn't modified from multiple locations at the same time.
- Complex data type ownership: Types like `String` strictly adhere to Rust's ownership model. Once their ownership is transferred to another variable, the original becomes unusable.
- Simple data type copy behavior: Unlike complex types, simple data types such as integers implement the `Copy` trait. This means they get duplicated when assigned to another variable, leaving the original variable intact and usable.
## Rust: References
- Rust provides a borrowing system to access data without transferring ownership.
### The borrow symbol
- The `&` symbol signifies a borrow.
```rust
let s = String::from("hello");
let borrowed_s = &s;
```
- Borrowing comes in two flavors: immutable and mutable.
### Immutable borrows
- An immutable borrow lets you read data, but not change it.
```rust
let s = String::from("hello");
let r1 = &s;
let r2 = &s;
```
### Mutable borrows
- A mutable reference lets you alter data.
- Only one mutable reference is allowed within a scope.
- This ensure no data races.
```rust
let mut s = String::from("hello");
let r1 = &mut s;
let r2 = &mut s; // Error: cannot borrow `s` as mutable more than once

println!("{r1}, {r2}");
```
- Multiple immutable borrows can coexist, but not alongside a mutable borrow.
```rust
let mut s = String::from("hello");

let r1 = &s;
let r2 = &s;
let r3 = &mut s; // This would be an error!

println!("{r1}, {r2}, {r3}");
```
- Question: Why does Rust allow only one mutable reference to data in a particular scope?
- Answer: To prevent potential data races
### Dangling references
- Dangling is when a reference's data gets freed while the reference still exists.
- Rust ensures references never "dangle".
```rust
let r;
{
  let s = String::from("hello");
  r = &s;
} // `s` drops here, making `r` a dangling reference.
```
- Question: In the below code example, what is the primary reason Rust prevents the used of the variable `r` after the inner block?
```rust
let r;
{
  let s = String::from("hello");
  r = &s;
} // `s` is dropped here
```
- Answer: To prevent dangling references
### Slices: a quick look
- Slices let you reference collection parts, not the entire collection.
- This way, you can work with collection segments without owning the whole thing.
- This allows for flexible and safe data access.
```rust
let string = String::from("Hello, World!");
let hello_slice = &string[0..5]; // hello_slice = "Hello"
let world_slice = &string[7..12]; // world_slice = "World"
```
- Question: What's the main benefit of slices?
- Answer: Work with parts without owning the entire collection
### Summary
- Rust promotes safe data handling through its borrowing mechanism, allowing data access without complete transfer:
  - Immutable references: Read data without altering. Multiple immutable references can coexist unless there's mutable reference.
  - Mutable references: Modify data. Only one is allowed per scope.
  - Dangling references: Rust ensures all references point to valid data.
  - Slices: Let you reference collections in parts.
