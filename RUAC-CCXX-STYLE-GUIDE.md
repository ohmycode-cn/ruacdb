# RUAC C and C++ Style Guide

# C++ Style Guide

## Table of Contents

[C/C++ Comment Rules](#ccxx-comment-rules)
[C++ File Rules](#cxx-file-rules)
[C++ Namespaces](#cxx-namespaces)
[C++ Global Variables and Constants](#cxx-global-variables-and-constants)
[C++ Member Variables and Constants](#cxx-member-variables-and-constants)
[C++ Parameter Rules](#cxx-parameter-rules)
[C++ Classes](#cxx-classes)
[C++ Function Return Syntax Standard](#cxx-function-return-syntax-standard)
[C++ Function Names](#cxx-function-names)

## CCXX Comment Rules

- The comment language for C/C++ is English.
- Comments for C/C++ must accurately annotate the actual code.
- If only a header file exists, the member functions inside the class must be annotated.
- If both a header file and a source file exist, the member functions declared in the header need not be annotated; annotations should be placed in the source file.
- Function annotations: when a function uses delegation or a relatively complex implementation, an additional description must be provided in `@details`. Optional otherwise.
  - For example:
  ```cpp
  /**
   * @brief
   *
   * @param
   * 
   * @return
   *
   * @details
   *
   */
   auto example(type param_) -> type;
  ```
- Class annotations: the annotation for a class (if a class exists) primarily describes what the class does, whether it is a singleton, polymorphic, has inheritance dependencies, ... etc.
  - For example:
  ```cpp
  /**
   * @brief
   *
   */
   class Example{};
  ```
- Header file annotation header: the annotation header of a header file is a complete description of the header file's functional content.
  - Note: in a header file, the internal declaration content of a class needs no annotations; only the class itself needs to be annotated.
  - For example:
  ```cpp
  /**
   * ...
   * Description of header file function declaration
   * // start adding the hpp file annotation description on this line
   */
  ```
- Source file annotation header: the annotation header of a source file remains unchanged.

## CXX File Rules

- C++ file names must use only lowercase letters, or separate words with underscores.
- C++ files must use UTF-8 encoding.
- C++ files must use LF line endings.
- The creation and initialization of C++ files must use the `mkf.sh` script.


## CXX Namespaces

- This project's C++ code uses `ruac` as the root namespace; all C++ code located inside the RUAC project must be under the `ruac` namespace.
- Namespace management is delegated to the `mkf.sh` script, which is responsible for initializing `.hpp` and `.cpp` files that conform to the project conventions.
- Namespaces must use only lowercase letters, or separate words with underscores. CamelCase is forbidden.
- For example:
```cpp
// Valid namespaces
// For example:
namespace ruac { /* code */ } // namespace ruac
namespace ruac::target { /* code */ } // namespace ruac::target
namespace ruac::target_other { /* code */ } // namespace ruac::target_other

// Invalid namespaces
// For example:
namespace Ruac { /* code */ } // namespace Ruac
namespace ruac::_target { /* code */ } // namespace ruac::_target
namespace ruac::target_ { /* code */ } // namespace ruac::target_

```

## CXX Global Variables and Constants

- C++ global variables must use the `g_` prefix. Global constants must use the `G_` prefix.
- Global variables should use only lowercase letters, or separate words with underscores.
- Global constants should use only uppercase letters, or separate words with underscores.
- Note: the use of global variables should be minimized.

```cpp
// Valid global variables
int g_target = 0; // g_target
int g_target_other = 0; // g_target_other

// Invalid global variables
int g_Target = 0; // g_Target
int g_TargetOther = 0; // g_TargetOther

// Valid global constants
const int G_TARGET = 0; // G_TARGET
const int G_TARGET_OTHER = 0; // G_TARGET_OTHER

// Invalid global constants
const int g_target = 0; // g_target
const int g_target_other = 0; // g_target_other
```

## CXX Member Variables and Constants

- C++ member variables must use the `m_` prefix. Member constants must use the `M_` prefix.
- Member variables should use only lowercase letters, or separate words with underscores.
- Member constants should use only uppercase letters, or separate words with underscores.

```cpp
// Valid member variables
int m_target = 0; // m_target
int m_target_other = 0; // m_target_other

// Invalid member variables
int m_Target = 0; // m_Target
int m_TargetOther = 0; // m_TargetOther

// Valid member constants
const int M_TARGET = 0; // M_TARGET
const int M_TARGET_OTHER = 0; // M_TARGET_OTHER

// Invalid member constants
const int M_target = 0; // M_target
const int M_target_other = 0; // M_target_other
```

## CXX Parameter Rules

- C++ parameters must use only lowercase letters with an underscore suffix, or separate words with underscores.
- Parameters should use only lowercase letters, or separate words with underscores.

```cpp
// Valid parameters
void fn(type param_ = 0); // param_
void fn(type param_, type param_other_ = 0); // param_other_

// Invalid parameters
void fn(type Param_ = 0); // Param_
void fn(type ParamOther_ = 0); // ParamOther_
```



## CXX Classes

- C++ classes include (class/struct/enum/enum class/union ...)
- All classes must use PascalCase (UpperCamelCase).
- Class constructors may use the `=default` keyword.
- Class destructors may use the `=default` keyword.
- For example:
```cpp
// Valid classes
class Target {
public:
    Target() = default;
    ~Target() = default;
};

class TargetOther {
public:
    TargetOther(type param_);
    ~TargetOther() = default;
};

// Invalid classes
class TargetOther {
public:
    // Constructor or destructor not needed but the `=default` keyword is not used
    TargetOther(); 
    ~TargetOther();
};

class Target_Other { ... } // invalid class
class targetOther { ... } // invalid class
class Targetother { ... } // invalid class

// struct / enum / enum class / union and so on
```

## CXX Function Return Syntax Standard

- When the function return type is void, the following syntax standard should be used:
```cpp
// leading return syntax
void fn(type param_, ...);
```
- When the function return type is non-void, the following syntax standard should be used:
```cpp
// trailing return syntax
auto fn(type param_, ...) -> type;
```

## CXX Function Names

- C++ function names must use only lowercase letters, or separate words with underscores.
- C++ function names must not use CamelCase. Any form of prefix or suffix is forbidden.

```cpp
// Valid function names
auto fn_example(type param_, ...) -> type; // fn_example_;
void fn(type param_, ...); // fn_

// Invalid function names
auto Fn_example(type param_, ...) -> type; // fn_example
void Fn(type param_, ...); // fn
auto FnExample(type param_, ...) -> type; // fn_example_example
auto fn_(type param_, ...) -> type; // fn_
auto _fn(type param_, ...) -> type; // _fn_
auto fnExample(type param_, ...) -> type; // fn_example_example
```
