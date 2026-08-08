# rstd 模块 API - Messages StdDug（标准调试输出）

## 模块概述

`StdDug` 类归属于 `ruac::rstd::messages` 命名空间，是项目标准库提供的调试输出工具。它采用单例模式，负责生成带 `[ TEMP DEBUG:( ]` 前缀、消息内容及源文件/行号信息的格式化调试字符串，并可按配置输出到 `stdout` 或 `stderr`。

`StdDug` 与同命名空间的 `StdMsg` 分工配合：

- `StdDug` 负责**格式化**调试追踪信息（`ostrs` 返回格式化字符串）；
- `StdMsg` 负责**门控输出**（按 `m_enable_msg` 开关决定是否实际输出）。

二者组合使用（`StdMsg::instance().print(StdDug::instance().ostrs(...))`）即可实现「格式化 + 可控输出」的调试追踪，这正是 RUACDB 交互式 Shell 中 `stdmsg on` 时出现 `[ TEMP DEBUG:( ]` 信息、`stdmsg off` 时该信息消失的底层机制。

## 命名空间与头文件

- 命名空间：`ruac::rstd::messages`
- 头文件：`include/rstd/messages/ruac_stddug.hpp`
- 源文件：`src/rstd/messages/ruac_stddug.cpp`

### 依赖头文件

| 头文件        | 提供内容                              |
|---------------|---------------------------------------|
| `<string>`    | `std::string`                         |
| `<syncstream>` | `std::osyncstream`（源文件，同步输出）|
| `<iostream>`   | `std::cout` / `std::cerr`（源文件）  |
| `<sstream>`    | `std::stringstream`（源文件，拼接）  |

## 数据结构

### StdDebugParamList

```cpp
struct StdDebugParamList {
    bool m_enable_color{false};
    bool m_output_std{true}; // true is stdout ,false: is stderr
    bool m_enable_out{true};
    bool m_next_line{true};
};
```

`StdDug` 的输出行为参数集合，通过 `set_param_mode()` 应用。

**成员**

| 成员             | 类型   | 默认值  | 说明                                              |
|------------------|--------|---------|---------------------------------------------------|
| `m_enable_color` | `bool` | `false` | 是否启用 ANSI 彩色表头。启用后表头变为红色高亮。  |
| `m_output_std`   | `bool` | `true`  | 输出目标：`true` 为 `stdout`，`false` 为 `stderr`。 |
| `m_enable_out`   | `bool` | `true`  | 是否启用输出。为 `false` 时 `ostrs` 返回空串、`print` 直接返回。 |
| `m_next_line`    | `bool` | `true`  | 是否在表头前插入换行符。                          |

## 类定义

```cpp
namespace ruac::rstd::messages {

    class StdDug {
      private:
        const char *const M_NEXT_TABS{"\n\t\t "};
        const char *const M_NEXT_LINE{"\n"};
        std::string m_header{"[ TEMP DEBUG:( ] "};
        StdDebugParamList m_param_mode{};

      private:
        StdDug() = default;
        ~StdDug() = default;
        StdDug(const StdDug &) = delete;
        StdDug &operator=(const StdDug &) = delete;

      public:
        void set_param_mode(const StdDebugParamList &params_ = {});
        auto ostrs(const std::string &msg_, const std::string &file_, int line_) -> std::string;
        void print(const std::string &msg_, const std::string &file_, int line_);
        static auto instance() -> StdDug &;
    };

} // namespace ruac::rstd::messages
```

## 设计说明

- **单例模式**：构造、析构、拷贝构造与拷贝赋值均为 `private` 或 `delete`，仅能通过静态方法 `instance()` 获取唯一实例。
- **格式与输出分离**：`ostrs()` 仅格式化并返回字符串，不产生副作用；`print()` 在 `ostrs()` 基础上执行实际输出。这使调用方可灵活选择「仅取字符串」或「直接输出」。
- **彩色表头**：当 `StdDebugParamList::m_enable_color` 为 `true` 时，`set_param_mode()` 会将表头 `m_header` 替换为带 ANSI 转义序列的红色高亮版本。
- **线程安全输出**：`print()` 通过 `std::osyncstream` 包裹 `std::cout`/`std::cerr`，保证多线程下输出不交错。

## 成员函数

### instance()

```cpp
static auto instance() -> StdDug &;
```

获取 `StdDug` 的单例引用。首次调用时构造函数局部静态对象，后续调用直接返回其引用。

**返回值**

| 类型          | 说明                       |
|---------------|----------------------------|
| `StdDug &`    | `StdDug` 单例的引用。      |

---

### set_param_mode(const StdDebugParamList &)

```cpp
void set_param_mode(const StdDebugParamList &params_ = {});
```

更新输出参数。将 `params_` 中的 `m_enable_out`、`m_output_std`、`m_next_line` 逐一拷贝到内部 `m_param_mode`；当 `params_.m_enable_color` 为 `true` 时，将表头 `m_header` 设置为带 ANSI 转义序列的红色高亮版本：

```cpp
"[ \033[40m\033[1;31mTEMP DEBUG:(\033[0m ] "
```

**参数**

| 参数       | 类型                            | 默认值 | 说明                 |
|------------|---------------------------------|--------|----------------------|
| `params_`  | `const StdDebugParamList &`     | `{}`   | 输出行为参数列表。   |

**说明**

- 默认参数为 `{}`，即各字段取其默认值（彩色关闭、输出到 stdout、启用输出、插入换行）。
- 注意：`m_enable_color` 仅在为 `true` 时生效；为 `false` 时不会将表头恢复为普通版本，表头保持上一次设置不变。

---

### ostrs(const std::string &, const std::string &, int)

```cpp
auto ostrs(const std::string &msg_, const std::string &file_, int line_) -> std::string;
```

格式化调试消息为字符串并返回，不执行任何输出。

执行流程：

1. 若 `m_param_mode.m_enable_out` 为 `false`，直接返回空字符串；
2. 使用 `std::stringstream` 拼接：
   - 若 `m_next_line` 为 `true`，先插入换行符 `M_NEXT_LINE`；
   - 插入表头 `m_header` 与消息内容 `msg_`；
   - 若 `msg_` 非空，插入制表缩进 `M_NEXT_TABS`；
   - 插入 `FILE: <file_>` 与 `M_NEXT_TABS`；
   - 插入 `LINE: <line_>`；
3. 返回拼接结果。

**参数**

| 参数      | 类型                      | 说明                       |
|-----------|---------------------------|----------------------------|
| `msg_`    | `const std::string &`     | 调试消息内容。             |
| `file_`   | `const std::string &`     | 源文件路径。               |
| `line_`   | `int`                     | 源代码行号。               |

**返回值**

| 类型            | 说明                                         |
|-----------------|----------------------------------------------|
| `std::string`   | 格式化后的字符串；输出禁用时返回空字符串。   |

**输出格式示例**

当 `m_next_line` 为 `true` 且消息非空时，返回形如：

```
\n[ TEMP DEBUG:( ] <msg_>\n\t\t  FILE: <file_>\n\t\t  LINE: <line_>
```

---

### print(const std::string &, const std::string &, int)

```cpp
void print(const std::string &msg_, const std::string &file_, int line_);
```

格式化并输出一条调试消息。**`StdDug` 自身提供独立的打印方法**，在 `ostrs()` 基础上直接执行实际写入，无需依赖 `StdMsg`。

> **特别说明**：`StdDug::print()` 与 `StdMsg::print()` 是两个独立的输出通道，二者互不影响：
> - `StdDug::print()` 的输出仅受 `StdDug` 自身的 `m_param_mode.m_enable_out` 开关控制；
> - 它**不受** `StdMsg::enable_stdmsg()` 设置的 `m_enable_msg` 开关影响。
>
> 这意味着：即便 Shell 执行了 `stdmsg off`（`StdMsg` 开关关闭），通过 `StdDug::print()` 直接输出的调试消息**仍然会输出**。若希望调试输出随 `stdmsg on/off` 切换，应改用 `StdMsg::print(StdDug::ostrs(...))` 的组合方式（见下文「与 StdMsg 的配合使用」）。

执行流程：

1. 若 `msg_` 为空或 `m_param_mode.m_enable_out` 为 `false`，直接返回；
2. 调用 `ostrs(msg_, file_, line_)` 获取格式化字符串；
3. 根据 `m_param_mode.m_output_std` 选择目标流：
   - `true` → `std::osyncstream(std::cout)` 输出；
   - `false` → `std::osyncstream(std::cerr)` 输出；
4. 输出内容后追加换行（`std::endl`）。

**参数**

| 参数      | 类型                      | 说明                       |
|-----------|---------------------------|----------------------------|
| `msg_`    | `const std::string &`     | 调试消息内容。             |
| `file_`   | `const std::string &`     | 源文件路径。               |
| `line_`   | `int`                     | 源代码行号。               |

**返回值**

无（`void`）。

## 两种输出方式对比

`StdDug` 提供两种调试输出途径，关键区别在于「输出门控」归属不同：

| 输出方式                                 | 格式化 | 实际输出 | 受谁控制                                       | 受 `stdmsg on/off` 影响 |
|------------------------------------------|--------|----------|------------------------------------------------|-------------------------|
| `StdDug::print(msg_, file_, line_)`      | `StdDug` | `StdDug`（`osyncstream` 直接写入）          | `StdDug::m_enable_out`  | **否**                  |
| `StdMsg::print(StdDug::ostrs(...))`      | `StdDug` | `StdMsg`（`osyncstream` 写入，经互斥锁门控）| `StdMsg::m_enable_msg`  | **是**                  |

- **方式一（`StdDug::print`）**：`StdDug` 既负责格式化又负责输出，绕过 `StdMsg` 门控。适用于需要无条件、即时输出的调试场景，不受 Shell 的 `stdmsg` 开关约束。
- **方式二（`StdMsg::print` + `StdDug::ostrs`）**：`StdDug` 仅格式化返回字符串，输出门控交由 `StdMsg`。适用于需要随 `stdmsg on/off` 统一开关的调试场景。

## 与 StdMsg 的配合使用

`StdDug` 的 `ostrs()` 返回纯字符串，不涉及输出门控。将返回值交给 `StdMsg::print()` 即可实现「格式化 + 可控输出」。项目内核节点（如 `CreateDatabase`）的调试追踪即采用此模式：

```cpp
StdMsg::instance().print(
    StdDug::instance().ostrs("Class: CreateDatabase", __FILE__, __LINE__));
```

当 Shell 执行 `stdmsg on` 时，`StdMsg` 开关开启，上述调试字符串被输出；执行 `stdmsg off` 时，`StdMsg` 开关关闭，调试字符串不再输出。

> 注意：若改用 `StdDug::instance().print(...)` 直接输出，则不受 `stdmsg on/off` 影响，始终输出（除非通过 `set_param_mode()` 将 `m_enable_out` 置为 `false`）。

## 使用示例

```cpp
#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"

using namespace ruac::rstd::messages;

// 1. 配置调试输出参数（启用彩色、输出到 stderr）
StdDebugParamList params;
params.m_enable_color = true;
params.m_output_std = false;
StdDug::instance().set_param_mode(params);

// 2. 方式一：仅获取格式化字符串，交由 StdMsg 门控输出
StdMsg::instance().enable_stdmsg(true);
StdMsg::instance().print(
    StdDug::instance().ostrs("Class: CreateDatabase", __FILE__, __LINE__));

// 3. 方式二：直接由 StdDug 输出（不受 StdMsg 开关控制）
StdDug::instance().print("direct debug output", __FILE__, __LINE__);
```

## 注意事项

- **StdDug 自带打印方法（重点）**：`StdDug` 提供独立的 `print()` 方法，自行完成格式化与输出，**不经过 `StdMsg` 门控**。其输出仅受 `StdDug::m_param_mode.m_enable_out` 控制，与 `StdMsg::m_enable_msg`（即 `stdmsg on/off`）完全独立。即使执行 `stdmsg off`，`StdDug::print()` 仍会输出。若需调试输出随 `stdmsg on/off` 统一切换，必须使用 `StdMsg::print(StdDug::ostrs(...))` 组合方式，而非 `StdDug::print()`。
- **彩色表头单向生效**：`set_param_mode()` 中 `m_enable_color` 仅在为 `true` 时设置彩色表头；为 `false` 时不会自动恢复普通表头。
- **空消息处理**：`print()` 在 `msg_` 为空时直接返回，不输出；`ostrs()` 在 `msg_` 为空时不插入制表缩进，但仍会输出表头与 FILE/LINE 信息。
- **换行与缩进**：格式化字符串中 `M_NEXT_LINE`（`\n`）与 `M_NEXT_TABS`（`\n\t\t `）用于多行对齐，使 FILE/LINE 信息缩进显示在表头下方。
- **线程安全**：`print()` 通过 `std::osyncstream` 保证输出原子性；`ostrs()` 为纯函数式格式化，无副作用。
