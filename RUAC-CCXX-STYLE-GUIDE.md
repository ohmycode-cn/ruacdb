# RUAC C And C++ Style Guide

## 1. File Layout

### 1.1 File Header Block

Every source file (`.hpp`, `.cpp`, `.h`, `.c`) must begin with a block comment in the following format:

```cpp
/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: <name>(<email>)
 * <relative-path-to-header>
 * <relative-path-to-implementation>
 * <brief description of the file's purpose>
 *
 */
```

- `Style Guide` — always reference this document.
- `File Rule` — state the column-wrap policy.
- `Author` — `<name>(<email>)`, e.g. `ohmycode-cn(ohcode@163.com)`.
- Lines 5–6 — relative paths to the header (`.hpp`) and its implementation (`.cpp`), one per line.
- Last content line — a concise description of what the file declares or implements.

### 1.2 Include Guard

Use `#pragma once` followed by a traditional `#ifndef` / `#define` / `#endif` guard:

```cpp
#pragma once
#ifndef RUAC_<MODULE>_HPP
#define RUAC_<MODULE>_HPP
// ...
#endif // RUAC_<MODULE>_HPP
```

### 1.3 Include Order

1. Standard library headers
2. Third-party library headers
3. Project headers (quoted `"rstd/..."` paths)

Separate each group with a blank line.

---

## 2. Naming Conventions

| Element             | Convention             | Example                  |
|---------------------|------------------------|--------------------------|
| Namespace           | lowercase, nested      | `ruac::rstd::logsystem`  |
| Class / Struct      | PascalCase             | `Format`, `Colored`      |
| Method              | camelCase              | `format()`, `output()`   |
| Variable            | camelCase              | `sequence_`, `message_`  |
| Constant / Enum     | UPPER_SNAKE_CASE       | `MAX_BUFFER_SIZE`        |
| Template parameter  | PascalCase             | `StringMap`, `Seqnum`    |
| Type alias          | PascalCase             | `using String = ...`     |
| File name           | snake_case with prefix | `ruac_format.hpp`        |

---

## 3. Formatting

### 3.1 Column Limits

- **Soft wrap** around **100** columns.
- **Hard wrap** at **120** columns — lines exceeding this must be broken.

### 3.2 Indentation

- **4 spaces** per indent level inside namespaces.
- **2 spaces** for access-specifier-relative members (`public:`, `private:`, `protected:`).

```cpp
namespace ruac::rstd::logsystem {

    class Foo {
      public:
        void bar();
    };

} // namespace ruac::rstd::logsystem
```

### 3.3 Braces

- Opening brace on the same line as the statement (K&R style).
- Closing brace on its own line, optionally with a trailing comment.

### 3.4 Trailing Return Type

Use C++ trailing return type syntax for methods:

```cpp
auto format(...) -> logtype::String;
```

---

## 4. Documentation Comments

### 4.1 File Header

Described in §1.1.

### 4.2 Class Documentation

Place a `/** */` block immediately before the class declaration:

```cpp
/**
 * @brief One-line summary.
 *
 * Detailed description if needed.
 */
class Foo {
```

### 4.3 Method Documentation

Place a `/** */` block immediately before the method declaration:

```cpp
/**
 * @brief Brief description of what the method does.
 *
 * @param name_  Description of the parameter.
 * @return Description of the return value.
 */
auto doSomething(const logtype::String &name_) -> logtype::String;
```

- Use `@brief`, `@param`, `@return`, `@note`, `@see` tags.
- Parameter names in the doc must match the actual parameter names.

### 4.4 Member Variable Documentation

Use `///` for inline single-line comments when the purpose is obvious, or `/** */` for non-trivial members:

```cpp
    int count_;  ///< Number of entries processed.
```

---

## 5. Class Design

### 5.1 Interfaces (Pure Abstract Classes)

- Class name is a noun describing the contract: `Format`, `Output`.
- All public methods are pure virtual (`= 0`).
- Provide a virtual destructor: `virtual ~ClassName() = default;`
- No data members in interfaces.

### 5.2 Parameter Conventions

- Suffix mutable / by-value parameters with `_` (e.g. `message_`, `time_`).
- Use `const` references for non-trivial types (`std::string`, containers).
- Pass fundamental types by value.

---

## 6. Namespaces

- Use nested form: `ruac::rstd::logsystem`.
- Indent contents by 4 spaces.
- Close with a trailing comment: `} // namespace ruac::rstd::logsystem`

---

## 7. Header Guard Naming

| File                    | Guard Macro             |
|-------------------------|-------------------------|
| `ruac_format.hpp`       | `RUAC_FORMAT_HPP`       |
| `ruac_output.hpp`       | `RUAC_OUTPUT_HPP`       |
| `ruac_logtype.hpp`      | `RUAC_LOGTYPE_HPP`      |

Pattern: `RUAC_<FILENAME_UPPER>_HPP`.
