# RUACDB（运行时统一访问控制数据库）

> [!IMPORTANT]
> ## Kernel 阶段说明（0.0.1-beta）
>
> 当前内核（`kernel`）处于 **0.0.1-beta** 阶段，仅作为最小化原型（MVP）用于验证整体架构是否能够运行起来，尚未达到可用于生产或大规模多用户场景的成熟度。
>
> ### 已知缺陷
>
> - **扁平化数据持有与全量拷贝**：数据在 `object::Kernel` 与 `object::Single` / `object::Multis` 之间通过 `getdbs()` 返回副本，`Single` / `Multis` 在构造时各自进行一次全量深拷贝。当启动 N 个用户时，可能产生 N 倍数据量的拷贝，存在严重的数据膨胀与同步问题。
> - **多用户注册一次性限制**：`ControllerPipes::init_pipe` 依赖 `m_once_lock` 标志，仅第一个用户能够完成注册，后续用户会被忽略，导致多用户场景无法正常初始化。
> - **数据写入路径尚未闭环**：`object::Kernel` 当前仅暴露只读副本访问（`getdbs()` 按值返回），缺少将修改同步回权威数据源的写入入口，数据语义（共享 vs 隔离）尚未最终确定。
> - **悬垂引用（裸指针持有）**：`ControllerTable::m_controller_table` 以裸指针 `Operation *` 存储每个用户的控制器，其生命周期由调用方（`main()` 中的 `new`）负责，但该指针从未被 `delete`，既造成内存泄漏，也使 `ControllerTable` 在持有时无人保证被引用对象的存活。一旦 `Operation` 被提前释放或改用栈对象 / 智能指针，表中保存的裸指针将立即悬垂；`ControllerPipes` 中的 `object / state / track` 同样以裸指针保存，存在同样的隐患。
>
> ### 阶段定位
>
> 本阶段的目标是 **让系统先跑起来**、验证最小闭环（登录 → 控制器装配 → 状态初始化 → 交互式 Shell → SQL 语句执行），而非追求数据模型、并发与持久化的正确性。上述缺陷均已知悉，将在后续提交中对内核进行重构（数据共享引用、写入闭环、多用户注册等）后逐步解决。

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

### 项目规则

- 项目规则与贡献限制公告: `RULES.md`
  - [英语](../../RULES.md)
  - [中文](../../RULES.md)
  - 这属于后期添加或者更新的规则。

## 开发环境与工具链要求

- **IDE 推荐**
  - code ide (visual studio code(/insider)/trae/...)
  - clion (jetbrains)
- **换行限制**
  - 对于基于 Code 内核的 IDE，可以添加如下设置到 `settings.json` 以显示列标尺并启用自动换行：
    ```jsonc
    "editor.rulers": [
        {
            "column": 100,
            "color": "#2E7D3250"
        },
        {
            "column": 120,
            "color": "#e6394660"
        }
    ],
    "editor.tabSize": 4,
    "editor.wordWrap": "wordWrapColumn",
    "editor.wordWrapColumn": 120,
    "editor.wrappingIndent": "same"
    ```
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

### 编译构建

RUACDB 提供了构建脚本 `mk-compile-ruacdb.sh` 来简化 CMake 工作流。

**前置条件**：
- CMake >= 4.3.1
- Clang（Linux 使用 clang++，Windows 使用 clang-cl）
- Qt6 Widgets >= 6.11.0
- Bash >= 5.0

**构建模式**：

| 模式 | 命令 | 说明 |
|------|------|------|
| 调试模式（默认） | `bash mk-compile-ruacdb.sh` | 启用单元测试（`UNIT_TEST=ON`），链接 Google Test |
| 生产模式（Release） | `bash mk-compile-ruacdb.sh --off-unit-test` | 禁用单元测试（`UNIT_TEST=OFF`），排除所有测试源码和 Google Test |

**构建流程**（生产级别二进制）：

```bash
# 1.（仅 Windows）创建 local.cmake 并设置 Qt6 路径（见上文）

# 2. 构建生产二进制
bash mk-compile-ruacdb.sh --off-unit-test

# 3. 运行
./out/ruacdb
```

**构建流程**（开发调试，含测试）：

```bash
# 1. 构建并启用单元测试
bash mk-compile-ruacdb.sh

# 2. 运行
./out/ruacdb
```

脚本会自动执行以下操作：
- 检测 CPU 核心数（`nproc` / `sysctl`）以启用并行编译
- 在 `build/` 目录下配置 CMake
- 将二进制输出到 `out/ruacdb`

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
