---
id: plan
aliases: []
tags: []
---

# MP2 Checklist: `Vector<T>` and `SString`

## A) `Vector<T>` template (in `vector.h`)

### Data members
- [x] `T* data_`
- [x] `size_t size_`
- [x] `size_t capacity_`
- [x] Allocator (recommended): `std::allocator<T> alloc_`

### Core invariants
- [ ] `0 <= size_ <= capacity_`
- [ ] If `capacity_ == 0`, `data_` can be `nullptr`
- [ ] Initial capacity on first growth should be `8` (to mirror CS341 expectations)

### Required API

#### Constructors / destructor
- [x] Default constructor
- [ ] Destructor
  - [ ] Destroys constructed elements
  - [ ] Frees the underlying buffer
- [ ] Copy constructor
- [ ] Copy assignment operator
- [ ] Move constructor
- [ ] Move assignment operator
   - [ ] Should be cheap

#### Capacity / state
- [x] `size()`
- [x] `capacity()`
- [x] `empty()`

#### Element access
- [ ] `T& operator[](size_t i)`
- [ ] `const T& operator[](size_t i) const`
- [ ] `T& at(size_t i)`
- [ ] `const T& at(size_t i) const`
  - [ ] Must bounds-check with `assert(i < size_)`

#### Modifiers
- [ ] `push_back(const T&)`
- [ ] `push_back(T&&)`
- [ ] `pop_back()`
  - [ ] Must `assert` that the vector is non-empty
- [ ] `clear()`
- [ ] `reserve(size_t new_cap)`
- [ ] `resize(size_t new_size, const T& value = T{})`
- [ ] `insert(size_t index, const T& value)`
  - [ ] Valid index range: `[0..size_]`
- [ ] `erase(size_t index)`
  - [ ] Valid index range: `[0..size_-1]`

#### Iterators (minimal)
- [ ] `T* begin()` / `T* end()`
- [ ] `const T* begin() const` / `const T* end() const`

### Rules
- Never use `std::vector` internally
- Use `assert()` for invalid indices / invalid usage
  - This mirrors CS341 guidance around undefined behavior
- Correctly manage non-trivial types
  - Constructors and destructors must stay balanced

---

## B) `SString` (in `sstring.h` + `sstring.cc`)

### Representation
- [ ] Store as `Vector<char>` or your own `char*` buffer
  - [ ] Recommended: `Vector<char>` so it reuses MP2
- [ ] Maintain the invariant that the buffer is NUL-terminated
  - [ ] `"\0"` must always exist at the end

### Required API

#### Constructors
- [ ] Default constructor
  - [ ] Represents an empty string
- [ ] Constructor from `const char*`
- [ ] Constructor from `std::string_view` *(optional)*

#### Basic operations
- [ ] `std::string ToString() const`
  - [ ] Or `const char* c_str()` if you want to add that helper
- [ ] `size_t size() const`
  - [ ] Does **not** count the terminating `"\0"`
- [ ] `void Append(const SString& other)`

#### String algorithms
- [ ] `Vector<std::string> Split(char delim) const`
  - [ ] Behavior should match Python-style splitting on a delimiter
  - [ ] Consecutive delimiters must produce empty fields

- [ ] `int Substitute(size_t offset, std::string_view target, std::string_view replacement)`
  - [ ] Returns `0` if one substitution happened
  - [ ] Returns `-1` if:
    - [ ] the target was not found, or
    - [ ] `offset` is out of range
  - [ ] Must substitute the **first occurrence at or after** `offset`

- [ ] `std::string Slice(size_t start, size_t end) const`
  - [ ] Range is `[start, end)`
  - [ ] `end` is exclusive
  - [ ] Must enforce:
    - [ ] `assert(start <= end)`
    - [ ] `assert(end <= size())`

---

## Suggested implementation order
1. Implement `Vector<T>` first
2. Pass all `Vector<T>` tests
3. Build `SString` on top of `Vector<char>`
4. Pass all `SString` tests
5. Run sanitizers and leak checks
