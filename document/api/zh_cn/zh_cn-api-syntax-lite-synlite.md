# syntax_lite 模块 API - SynLite（轻量语法分析器）

## 模块概述

`SynLite` 类归属于 `ruac::syntax_lite` 命名空间，是 RUAC 数据库的轻量级语法分析入口。该类封装了底层 `tree::Parser` 解析器，对外提供线程安全的单行 RUAC 命令提交接口，内部通过互斥锁保护对解析器的并发访问。

`SynLite` 自身不执行具体的词法分析、AST 构建或预执行逻辑，而是将实际解析工作委托给内部持有的 `tree::Parser` 独占指针实例。调用方通过 `syntax_line_hook()` 逐行提交 RUAC 命令，由 SynLite 完成线程防护后转交 Parser 完成完整的解析管线。

## 命名空间与头文件

- 命名空间：`ruac::syntax_lite`
- 头文件：`include/syntax_lite/ruac_synlite.hpp`
- 源文件：`src/syntax_lite/ruac_synlite.cpp`

### 依赖头文件

| 头文件                                    | 提供内容                                              |
|-------------------------------------------|-------------------------------------------------------|
| `syntax_lite/tree/ruac_parser.hpp`        | `tree::Parser` 类，底层语法解析器                     |
| `<string>`                                | `std::string`，命令行参数类型                         |
| `<mutex>`                                 | `std::mutex` / `std::lock_guard`，线程同步            |
| `<syncstream>`                            | `std::osyncstream`（源文件，空解析器诊断输出）        |
| `<iostream>`                              | `std::cout`（源文件，诊断输出）                       |

## 关联类型

### tree::Parser

定义于 `ruac::syntax_lite::tree` 命名空间，为 SynLite 内部持有的底层语法解析器。SynLite 通过 `std::unique_ptr<tree::Parser>` 独占其所有权。`Parser` 公开的关键方法如下（SynLite 仅调用 `get_query`）：

| 方法                          | 说明                                                              |
|-------------------------------|-------------------------------------------------------------------|
| `void get_query(const std::string &line_)` | 接收一行 RUAC 命令，执行词法分析（Lexer）、语法解析（Parser）、预执行（PrExec）完整管线。 |

## 类定义

```cpp
namespace ruac::syntax_lite {

    class SynLite {
      private:
        std::unique_ptr<ruac::syntax_lite::tree::Parser> M_PARSER;
        std::mutex M_SYN_LITE_MTX;

      public:
        SynLite();
        ~SynLite() = default;

      public:
        void syntax_line_hook(const std::string &line_);
    };

} // namespace ruac::syntax_lite
```

## 设计说明

- **独占式持有 Parser**：内部通过 `std::unique_ptr<tree::Parser>` 持有底层解析器，SynLite 完全管理 Parser 的生命周期，构造时创建、析构时由 `unique_ptr` 自动释放。
- **线程安全防护**：使用 `std::mutex M_SYN_LITE_MTX` 配合 `std::lock_guard`，在 `syntax_line_hook()` 入口处加锁，保证多线程环境下对 Parser 的串行访问，避免 Parser 内部状态被并发读写破坏。
- **空解析器兜底**：`syntax_line_hook()` 在转发前检查 `M_PARSER` 是否为空指针（例如 SynLite 对象被移动后），若为空则通过 `std::osyncstream(std::cout)` 线程安全地输出诊断信息后立即返回，不产生空指针解引用。
- **默认析构**：析构函数显式 `= default`，与 `unique_ptr` 成员的自动析构语义一致，无需自定义清理逻辑。

## 成员函数

### SynLite()

```cpp
SynLite();
```

默认构造函数。在构造阶段通过 `std::make_unique<tree::Parser>()` 创建一个全新的 `Parser` 实例，并将其所有权转移至内部 `M_PARSER` 独占指针，确保后续 `syntax_line_hook()` 调用拥有可用的底层解析器。

**说明**

- 构造过程无参数，Parser 的初始化完全由其自身默认构造函数完成（内部创建 SynxList、PrExec、Lexer 等子组件）。
- 若内存分配失败（`std::make_unique` 抛出 `std::bad_alloc`），异常将传播至调用方。

---

### ~SynLite()

```cpp
~SynLite() = default;
```

默认析构函数。由编译器自动合成，按成员声明逆序析构：先销毁 `M_SYN_LITE_MTX`，再由 `M_PARSER` 的 `unique_ptr` 析构函数自动释放所持有 `Parser` 实例及其内部资源。

---

### syntax_line_hook(const std::string &)

```cpp
void syntax_line_hook(const std::string &line_);
```

提交一行 RUAC 命令进行语法分析。该方法为 SynLite 的核心公开接口，调用后依次执行：

1. **互斥锁加锁**：通过 `std::lock_guard<std::mutex>` 对 `M_SYN_LITE_MTX` 加锁，锁作用域覆盖整个函数体，确保对 Parser 的访问串行化；
2. **空指针检查**：若 `M_PARSER == nullptr`（通常由 SynLite 被移动或手动 `release()` 导致），通过 `std::osyncstream(std::cout)` 输出 `"Not initialized parser."` 并换行，随后直接返回；
3. **委托解析**：调用 `M_PARSER->get_query(line_)`，将命令行转交底层 Parser 完成词法分析、语法解析、AST 分发、预执行等完整流程。

**参数**

| 参数     | 类型                   | 说明                              |
|----------|------------------------|-----------------------------------|
| `line_`  | `const std::string &`  | 待解析的单行 RUAC 命令原始字符串。|

**返回值**

无（`void`）。

**说明**

- 解析结果与副作用由 `Parser::get_query()` 内部处理（包括打印 Token、分发执行节点、输出错误等），`syntax_line_hook()` 不返回任何状态码。
- `line_` 按 `const &` 传递，内部不做修改；空字符串的行为由底层 `Parser::get_query()` 决定。
- 加锁与解锁由 `std::lock_guard` RAII 自动管理，即便 `Parser::get_query()` 内部抛出异常，互斥锁仍会被正确释放，不会死锁。

## 使用示例

```cpp
#include "syntax_lite/ruac_synlite.hpp"

using namespace ruac::syntax_lite;

// 1. 创建 SynLite 实例（内部自动初始化 Parser）
SynLite synlite;

// 2. 逐行提交 RUAC 命令进行解析
synlite.syntax_line_hook("CREATE DATABASE mydb;");
synlite.syntax_line_hook("USE mydb;");
synlite.syntax_line_hook("CREATE TABLE users (id INT64U, name STRING);");
synlite.syntax_line_hook("SHOW TABLES;");

// 3. 多线程场景下并发调用同样安全（内部互斥锁保证串行化）
// std::thread t1([&] { synlite.syntax_line_hook("SHOW DATABASES;"); });
// std::thread t2([&] { synlite.syntax_line_hook("SHOW TABLES;"); });
// t1.join(); t2.join();
```

## 注意事项

- **移动后状态**：若 SynLite 对象被 `std::move` 转移（`M_PARSER` 变为空），后续调用 `syntax_line_hook()` 将输出 `"Not initialized parser."` 诊断并静默返回，不会崩溃。当前接口未提供 `reset()` 或重新初始化方法，移动后的 SynLite 无法恢复解析能力。
- **无返回值设计**：`syntax_line_hook()` 返回 `void`，解析成功/失败的状态由底层 Parser 内部通过输出（标准输出/错误）或其他副作用体现，调用方无法通过返回值直接判断解析结果。
- **锁粒度**：互斥锁覆盖整个 `syntax_line_hook()` 调用周期（包括 Parser 完整解析管线），多线程并发提交命令时会被串行排队执行，高并发场景下可能成为性能瓶颈。
- **诊断信息输出**：空解析器时的 `"Not initialized parser."` 消息直接写入 `stdout`，无法重定向或关闭；如需自定义错误处理，应在上层确保 SynLite 未被移动后再调用。
- **line_ 的格式约束**：SynLite 不做任何预处理（去除空白、注释剥离等），`line_` 内容被原样转交 Parser，通常应为以分号结尾的完整 RUAC 单条命令。
