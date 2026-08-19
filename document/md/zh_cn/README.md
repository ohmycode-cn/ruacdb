# RUACDB（运行时统一访问控制数据库）

## 项目简介

RUACDB 是一个由 C/C++/Rust 实现的运行时统一访问控制的 MINI 数据库，大部分功能使用 C++ 编写。项目致力于探索一个更激进的数据库系统架构，因此
可能会在某些节点或特定版本阶段进行重大重构。
RUACDB 经过验证，可以在 Windows 11 / Linux 平台编译运行。

**核心理念：绝对模块化** — 每个模块只需提供定义良好的接口，而无需了解其他模块的内部实现，从而确保长期的可维护性和可扩展性。

## 项目愿景

RUACDB 受 Linux 哲学启发，秉承"小而专注"、"大而全"、"模块化"和"可扩展"的原则。

### 多语言架构

RUACDB 采用多语言实现策略：
- **C++**：大部分功能实现
- **Rust**：内存安全关键部分
- **C**：性能关键部分

这种设计充分发挥了每种语言的优势，在确保开发效率和安全性的同时实现最佳性能。

### 语言标准策略

RUACDB 将彻底摒弃过时的编程范式和语言标准：
- **C++**：采用 C++17，实际使用 C++26
  - ISO 标准：https://isocpp.org
- **C**：直接采用 C23 标准
  - Working Draft：https://www.open-std.org/jtc1/sc22/wg14/
  - ISO 标准：https://www.iso.org/standard/82075.html
- **Rust**：使用官方最新长期支持版本

| 资源 | 地址 |
|------|------|
| 官方网站 | https://www.rust-lang.org/ |
| 中文官网 | https://www.rust-lang.org/zh-CN/ |
| RFC 仓库 | https://github.com/rust-lang/rfcs |
| 标准库文档 | https://doc.rust-lang.org/std/ |
| 源码仓库 | https://github.com/rust-lang/rust |


RUACDB 在 C/C++ 代码中借鉴了 Rust 的"用完即丢"哲学，这种做法虽不符合行业标准，但使代码更安全、更易维护。

### 标准库与系统架构

RUACDB 就像操作系统一样拥有自己的标准库 `rstd`：
- `rstd` 是严格隔离的库模块，各子模块之间禁止任何依赖关系
- 每个子模块只负责自己的功能并提供明确接口
- 未来第三方库将逐渐被项目标准库取代

RUACDB 拥有完整的系统架构：
- 数据库模型
- 内核层
- 用户层（类似 Linux 用户系统，拥有用户空间，默认 root 用户拥有全部权限）
- 网络层

未来还将引入用户+组权限模型。

## 参与须知

RUACDB 是一个复杂的项目，可能会非常具有挑战性！

**注意**：我不是一名专业的软件工程师（也许将来会成为），我只是一个自由软件爱好者。如果你对 RUACDB 感兴趣，欢迎参与开发和讨论。

**重要**：所有参与者必须严格遵守 RUACDB 项目的代码规范和开发流程。如果您无法接受这些规范和流程，您的提交将被拒绝。

### 代码规范

- RUACDB C/C++ 规范指导: `RUAC-CCXX-STYLE-GUIDE.md`
  - [英语](../../RUAC-CCXX-STYLE-GUIDE.md)
  - [中文](RUAC-CCXX-STYLE-GUIDE.md)

- RUACDB Rust 规范指导: `RUAC-RUST-STYLE-GUIDE.md`
  - [英语](../../RUAC-RUST-STYLE-GUIDE.md)
  - [中文](RUAC-RUST-STYLE-GUIDE.md)

- RUACDB BASH 规范指导: `RUAC-BASH-STYLE-GUIDE.md`
  - [英语](../../RUAC-BASH-STYLE-GUIDE.md)
  - [中文](RUAC-BASH-STYLE-GUIDE.md)

## 开发环境与工具链要求

- **IDE 推荐**
  - code ide (visual studio code(/insider)/trae/...)
  - clion (jetbrains)
- **WINDOWS**
  - compile env: clang-cl.exe/clang++.exe
  - qt      env: qt6(>=6.11.0), recommended: msvc2022
- **LINUX**
  - compile env: clang++
  - qt      env: your linux latest qt version (but >= 6.11.0)
- **MACOS**
  - 不支持的平台
- **UNIX**
  - 不支持的平台
- **OTHER**
  - 不支持的平台

### CMakeLists.txt 配置

如果使用 Windows 平台构建 RUACDB，需要创建 `local.cmake` 文件并修改 Qt6 路径：

```cmake
# local.cmake
if (WIN32)
    set(Qt6_ROOT "你的Qt6安装路径")
    set(CMAKE_PREFIX_PATH "${Qt6_ROOT}" CACHE PATH "Qt6 install root")
endif()
```

`local.cmake` 已被添加到 `.gitignore`，不会被提交到版本控制中。

### 模块 API 接口文档

每个模块都有明确的 API 接口，文档详见 `document/api/` 目录。

**注意**：API 接口文档存在更新不及时的滞后性，请在使用时注意版本差异。

## Git 提交规范

- 提交次数不受限制
- 对代码文件进行增删改时，必须先拉取最新代码再进行修改，避免与他人修改冲突
- 提交摘要必须使用英文编写，并详细描述修改内容，包括：
  - 修改的文件
  - 修改的位置
  - 修改的原因

## 许可证

RUACDB 采用 **GNU General Public License v3.0 or later (GPL-3.0-or-later)** 许可证，并依据 GPL-3.0 第 7 条附加了署名条款。完整文本详见 [LICENSE](../../../LICENSE)。
