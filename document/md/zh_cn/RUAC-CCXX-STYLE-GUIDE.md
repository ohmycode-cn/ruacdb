# RUAC C 与 C++ 代码规范

# C++ 代码规范

## 目录导航

[C++ 命名空间](#CXX命名空间)
[C++ 类](#CXX类)


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
}

// 非合法类
class TargetOther {
public:
    // 不需要使用构造函数或者析构函数但是没有使用`=default`关键字
    TargetOther(); 
    ~TargetOther();
}

class Target_Other { ... } // 非合法类
class targetOther { ... } // 非合法类
class Targetother { ... } // 非合法类

// struct / enum / enum class / union 以此类推
```