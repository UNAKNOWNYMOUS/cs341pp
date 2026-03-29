---
id: learn_x_in_y_rust
aliases: []
tags: []
---

# Learn X in Y minutes
## Where X=Rust
- Rust combines low-level control over performance with high-level convenience and safety guarantees.
- Although Rust is a relatively low-level language, it has some functional concepts that are generally found in higher-level languages. This makes Rust not only fast, but also easy and efficient to code in.
- `///` are documentation comments and support markdown notation.
- Can add suffixes to integer + floats `13i32` and `1.3f64`.
- Most of the time, the Rust compiler can infer what type a variable is, so you don't have to write an explicit type annotation.
- `String` - a heap-allocated string
  - Stored as a `Vec<u8>` and always holds a valid UTF-8 sequence, which is not null terminated.
```rust
let s: String = "hello world".to_string();
```
- A Rust string slice (`&str`) is an immutable, borrowed view into a sequence of UTF-8 encoded bytes. It's a lightweight reference to data owned by something else (like a `String` or a string literal stored in the program binary) and does not involve memory allocation.
```rust
let s_slice: &str = &s;
```
- A slice - an immutable view into a vector or array.
```rust
let mut vector:Vec<i32> = vec![1, 2, 3, 4];

let slice:&[i32] = &vector;
```
- Use `{:?}` to print something debug-style.
- A tuple is a fixed-size set of values of possible different types.
```rust
let x: {i32, &str, f64} = (1, "hello", 3.4);

// Destructuring `let`
let (a, b, c) = x;
println!("{} {} {}", a, b, c);
```
