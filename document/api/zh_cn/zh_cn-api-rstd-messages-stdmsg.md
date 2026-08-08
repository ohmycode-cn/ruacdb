# rstd 模块 API - Messages StdMsg（标准消息输出）

## 模块概述

`StdMsg` 类归属于 `ruac::rstd::messages` 命名空间，是项目标准库提供的线程安全消息输出工具。它采用单例模式，通过一个全局开关 `m_enable_msg` 控制是否实际输出消息，并提供模板化的 `print` 方法向 `stdout` 或 `stderr` 写入。

`StdMsg` 是 RUACDB 交互式 Shell 中 `stdmsg on` / `stdmsg off` 命令的底层实现：开关开启时，通过 `print` 提交的消息会被输出；关闭时，`print` 静默返回，不产生任何输出。该机制常与 `StdDug`（调试格式化工具）配合使用——`StdDug` 负责生成带文件/行号的调试追踪字符串，`StdMsg` 负责按开关决定是否输出。

## 命名空间与头文件

- 命名空间：`ruac::rstd::messages`
- 头文件：`include/rstd/messages/ruac_stdmsg.hpp`
- 源文件：`src/rstd/messages/ruac_stdmsg.cpp`

### 依赖头文件

| 头文件        | 提供内容                              |
|---------------|---------------------------------------|
| `<syncstream>` | `std::osyncstream`，同步流输出       |
| `<iostream>`   | `std::cout` / `std::cerr`            |
| `<mutex>`      | `std::mutex` / `std::lock_guard`     |

## 类定义

```cpp
namespace ruac::rstd::messages {

    class StdMsg {
      private:
        StdMsg() = default;
        ~StdMsg() = default;
        StdMsg(const StdMsg &) = delete;
        StdMsg &operator=(const StdMsg &) = delete;

      private:
        std::mutex m_print_mtx;
        bool m_enable_msg{false};

      public:
        template <typename T>
        void print(const T &msg_, const bool &stdout_ = true);

      public:
        static auto instance() -> StdMsg &;
        void enable_stdmsg(const bool enable_);
    };

} // namespace ruac::rstd::messages
```

## 设计说明

- **单例模式**：构造、析构、拷贝构造与拷贝赋值均为 `private` 或 `delete`，仅能通过静态方法 `instance()` 获取唯一实例。`instance()` 内部使用函数局部静态变量，保证初始化的线程安全性。
- **全局开关**：`m_enable_msg` 默认为 `false`，即默认不输出消息。通过 `enable_stdmsg()` 切换开关状态。
- **双重线程安全**：`print` 内部先用 `std::lock_guard<std::mutex>` 加锁保护对 `m_enable_msg` 的读取与输出过程，再通过 `std::osyncstream` 保证流写入的原子性，避免多线程交错输出。

## 成员函数

### instance()

```cpp
static auto instance() -> StdMsg &;
```

获取 `StdMsg` 的单例引用。首次调用时构造函数局部静态对象，后续调用直接返回其引用。

**返回值**

| 类型          | 说明                       |
|---------------|----------------------------|
| `StdMsg &`    | `StdMsg` 单例的引用。      |

---

### enable_stdmsg(const bool)

```cpp
void enable_stdmsg(const bool enable_);
```

启用或禁用消息输出。将传入的布尔值存入内部开关 `m_enable_msg`，控制后续 `print` 调用是否实际输出。

**参数**

| 参数       | 类型           | 说明                                   |
|------------|----------------|----------------------------------------|
| `enable_`  | `const bool`   | `true` 启用输出；`false` 禁用输出。    |

**说明**

- 该方法对应交互式 Shell 中的 `stdmsg on` / `stdmsg off` 命令：
  - `stdmsg on` → `enable_stdmsg(true)`
  - `stdmsg off` → `enable_stdmsg(false)`

---

### print(const T &, const bool &)

```cpp
template <typename T>
void print(const T &msg_, const bool &stdout_ = true);
```

向 `stdout` 或 `stderr` 输出一条消息。该方法为模板函数，定义于头文件中。

执行流程：

1. 通过 `std::lock_guard<std::mutex>` 加锁；
2. 若 `m_enable_msg` 为 `false`，直接返回，不输出；
3. 根据 `stdout_` 选择目标流：
   - `stdout_` 为 `true` → 通过 `std::osyncstream(std::cout)` 输出；
   - `stdout_` 为 `false` → 通过 `std::osyncstream(std::cerr)` 输出；
4. 输出内容后追加换行（`std::endl`）。

**模板参数**

| 参数   | 说明                                   |
|--------|----------------------------------------|
| `T`    | 消息类型，需支持 `operator<<` 流插入。 |

**参数**

| 参数       | 类型             | 默认值  | 说明                                        |
|------------|------------------|---------|---------------------------------------------|
| `msg_`     | `const T &`      | -       | 待输出的消息内容。                          |
| `stdout_`  | `const bool &`   | `true`  | `true` 输出到 `stdout`；`false` 输出到 `stderr`。 |

**返回值**

无（`void`）。

## 与 StdDug 的配合使用

`StdMsg` 常与同命名空间的 `StdDug`（调试格式化工具）配合：`StdDug::ostrs()` 负责生成带 `[ TEMP DEBUG:( ]` 前缀及文件/行号信息的格式化字符串，`StdMsg::print()` 负责按开关决定是否输出该字符串。这种分工使得调试追踪的「格式化」与「输出门控」解耦。

## 使用示例

```cpp
#include "rstd/messages/ruac_stdmsg.hpp"

using namespace ruac::rstd::messages;

// 1. 启用标准消息输出（等价于 Shell 中的 stdmsg on）
StdMsg::instance().enable_stdmsg(true);

// 2. 输出到 stdout
StdMsg::instance().print("operation done");
StdMsg::instance().print(42);

// 3. 输出到 stderr
StdMsg::instance().print("warning occurred", false);

// 4. 禁用后，print 静默返回
StdMsg::instance().enable_stdmsg(false);
StdMsg::instance().print("this will not be printed");
```

配合 `StdDug` 的典型用法（与项目内核中 `CreateDatabase` 等节点的调试追踪一致）：

```cpp
#include "rstd/messages/ruac_stdmsg.hpp"
#include "rstd/messages/ruac_stddug.hpp"

using namespace ruac::rstd::messages;

// StdDug 负责格式化，StdMsg 负责按开关输出
StdMsg::instance().print(
    StdDug::instance().ostrs("Class: CreateDatabase", __FILE__, __LINE__));
```

## 注意事项

- **默认关闭**：`m_enable_msg` 默认为 `false`，必须先调用 `enable_stdmsg(true)` 才能看到 `print` 的输出。
- **线程安全**：`print` 通过互斥锁与 `osyncstream` 双重保证线程安全，可在多线程环境下并发调用。
- **换行行为**：`print` 会在消息末尾自动追加 `std::endl`，调用方无需自行添加换行。
- **模板定义位置**：`print` 为模板函数，其完整实现位于头文件中，支持任意可流式输出的类型。
- **非拥有式门控**：`StdMsg` 仅控制是否输出，不负责消息内容的格式化；格式化逻辑应由调用方或 `StdDug` 完成。
