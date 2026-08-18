# RUAC C 与 C++ 代码规范

# C++ 代码规范

## 目录导航

[C-C++ 注解规范](#CCXX注解规范)

[C++ 文件规范](#CXX文件规范)

[C++ 命名空间](#CXX命名空间)

[C++ 全局变量与常量](#CXX全局变量与常量)

[C++ 成员变量与常量](#CXX成员变量与常量)

[C++ 参数规则](#CXX参数规则)

[C++ 类](#CXX类)

[C++ 函数返回语法标准](#CXX函数返回语法标准)

[C++ 函数名称](#CXX函数名称)

## CCXX注解规范

- C/C++ 的注解语言使用英语作为注解语言。
- C/C++ 的注解内容必须根据实际代码进行注解。
- 如果只存在纯头文件，那么需要对类内部的成员函数进行注解。
- 如果存在头文件与源文件，那么不需要对头文件类成员函数进行注解，应当在源文件中进行注解。
- 函数注解：当函数使用了委托或者较为复杂的实现时，需要在@details 进行额外描述说明。其它情况可选
  - 例如：
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
- 类的注解：类的注解（如果存在类）主要描述这个类做了什么，这个类是否单例，多态，继承依赖, ... 类
  - 例如：
  ```cpp
  /**
   * @brief
   *
   */
   class Example{};
  ```
- 头文件注解头：头文件的注解头是对当前头文件功能内容的完整描述
  - 注意：在头文件中，类的内部声明内容无需任何注解，只需要对类进行注解即可。
  - 例如:
  ```cpp
  /**
   * ...
   * Description of header file function declaration
   * // 在此行开始添加hpp文件注解描述
   */
  ```
- 源文件注解头：源码文件的注解头保持不变

## CXX文件规范

- C++ 文件名称必须全部使用小写字母，或者使用下划线分隔单词。
- C++ 文件必须使用UTF-8编码。
- C++ 文件必须使用LF换行符。
- C++ 文件的创建与初始化必须使用`mkf.sh`脚本。


## CXX命名空间

- 该项目的 C++ 代码使用ruac作为根命名空间，所有位于 RUAC 项目内部的 C++ 代码都必须在ruac命名空间下。
- 命名空间的控制交给`mkf.sh`脚本，该脚本负责初始化符合项目规范的`.hpp`与`.cpp`文件。
- 命名空间必须使用全部小写字母，或者使用下划线分隔单词。禁止使用驼峰命名法。
- 例如：
```cpp
// 合法命名空间
// 例如：
namespace ruac { /* code */ } // namespace ruac
namespace ruac::target { /* code */ } // namespace ruac::target
namespace ruac::target_other { /* code */ } // namespace ruac::target_other

// 非合法命名空间
// 例如：
namespace Ruac { /* code */ } // namespace Ruac
namespace ruac::_target { /* code */ } // namespace ruac::_target
namespace ruac::target_ { /* code */ } // namespace ruac::target_

```

## CXX全局变量与常量

- C++ 全局变量必须使用g_前缀。全局常量必须使用G_前缀。
- 全局变量应该全部使用小写字母，或者使用下划线分隔单词。
- 全局常量应该全部使用大写字母，或者使用下划线分隔单词。
- 注意：应当尽量减少使用全局变量。

```cpp
// 合法全局变量
int g_target = 0; // g_target
int g_target_other = 0; // g_target_other

// 非合法全局变量
int g_Target = 0; // g_Target
int g_TargetOther = 0; // g_TargetOther

// 合法全局常量
const int G_TARGET = 0; // G_TARGET
const int G_TARGET_OTHER = 0; // G_TARGET_OTHER

// 非合法全局常量
const int g_target = 0; // g_target
const int g_target_other = 0; // g_target_other
```

## CXX成员变量与常量

- C++ 成员变量必须使用m_前缀。成员常量必须使用M_前缀。
- 成员变量应该全部使用小写字母，或者使用下划线分隔单词。
- 成员常量应该全部使用大写字母，或者使用下划线分隔单词。

```cpp
// 合法成员变量
int m_target = 0; // m_target
int m_target_other = 0; // m_target_other

// 非合法成员变量
int m_Target = 0; // m_Target
int m_TargetOther = 0; // m_TargetOther

// 合法成员常量
const int M_TARGET = 0; // M_TARGET
const int M_TARGET_OTHER = 0; // M_TARGET_OTHER

// 非合法成员常量
const int M_target = 0; // M_target
const int M_target_other = 0; // M_target_other
```

## CXX参数规则

- C++ 参数必须全部使用小写字母加下划线后缀，或者使用下划线分隔单词。
- 参数应该全部使用小写字母，或者使用下划线分隔单词。

```cpp
// 合法参数
void fn(type param_ = 0); // param_
void fn(type param_, type param_other_ = 0); // param_other_

// 非合法参数
void fn(type Param_ = 0); // Param_
void fn(type ParamOther_ = 0); // ParamOther_
```



## CXX类

- C++ 类包含(class/struct/enum/enum class/union ...)
- 所有的类都必须使用大驼峰命名法。
- 类的构造函数允许使用`=default`关键字。
- 类的析构函数允许使用`=default`关键字。
- 例如：
```cpp
// 合法类
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

// 非合法类
class TargetOther {
public:
    // 不需要使用构造函数或者析构函数但是没有使用`=default`关键字
    TargetOther(); 
    ~TargetOther();
};

class Target_Other { ... } // 非合法类
class targetOther { ... } // 非合法类
class Targetother { ... } // 非合法类

// struct / enum / enum class / union 以此类推
```

## CXX函数返回语法标准

- 当函数返回类型为void时，应当使用如下语法标准：
```cpp
// 前置返回语法
void fn(type param_, ...);
```
- 当函数返回类型为非void时，应当使用如下语法标准：
```cpp
// 后置返回语法
auto fn(type param_, ...) -> type;
```

## CXX函数名称

- C++ 函数名称必须全部使用小写字母，或者使用下划线分隔单词。
- C++ 函数禁止使用驼峰命名法。禁止使用任何形式的前缀或者后缀。

```cpp
// 合法函数名称
auto fn_example(type param_, ...) -> type; // fn_example_;
void fn(type param_, ...); // fn_

// 非合法函数名称
auto Fn_example(type param_, ...) -> type; // fn_example
void Fn(type param_, ...); // fn
auto FnExample(type param_, ...) -> type; // fn_example_example
auto fn_(type param_, ...) -> type; // fn_
auto _fn(type param_, ...) -> type; // _fn_
auto fnExample(type param_, ...) -> type; // fn_example_example
```