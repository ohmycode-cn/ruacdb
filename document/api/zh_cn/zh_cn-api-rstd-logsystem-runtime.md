# rstd 模块 API - LogSystem Runtime（日志运行时）

## 模块概述

`api` 命名空间归属于 `ruac::rstd::logsystem`，提供日志运行时入口 `LogRuntime`。该类采用单例模式，作为日志系统对外的统一运行时接口，负责：

- 接收运行时参数（如是否启用日志运行时）；
- 委托 `Manager` 完成日志系统的初始化（加载配置文件、构建输出/格式化管线）；
- 提供带防护逻辑的 `write` 方法写入日志消息；
- 提供一组便捷宏，自动填充源文件名与行号。

`LogRuntime` 自身不直接处理格式化与输出，而是将实际日志写入委托给内部持有的 `Manager` 实例。

## 命名空间与头文件

- 命名空间：`ruac::rstd::logsystem::api`
- 头文件：`include/rstd/logsystem/ruac_api_log_runtime.hpp`
- 源文件：`src/rstd/logsystem/ruac_api_log_runtime.cpp`

### 依赖头文件

| 头文件                                        | 提供内容                                          |
|-----------------------------------------------|---------------------------------------------------|
| `rstd/logsystem/ruac_manager.hpp`             | `Manager` 类、`LoaderParamList`（间接包含）       |
| `rstd/logsystem/ruac_logtime.hpp`             | `logtime::get_time()`，时间获取                   |
| `rstd/logsystem/ruac_message.hpp`             | `Message` 单例，标准输出/错误输出                 |
| `rstd/logsystem/ruac_debugt.hpp`              | `DebugT` 单例，调试追踪信息生成                   |
| `<memory>`                                    | `std::unique_ptr`                                 |

## 关联类型

### logenum::Level

定义于 `ruac::rstd::logsystem::logenum`，为 `enum class`，表示日志严重级别，由低到高依次为：

| 枚举值     | 说明       |
|------------|------------|
| `DEBUG`    | 调试       |
| `INFO`     | 信息       |
| `WARNING`  | 警告       |
| `ERROR`    | 错误       |
| `FATAL`    | 致命       |

### logtype::string 与 logtype::sd_int

定义于 `ruac::rstd::logsystem::logtype` 的类型别名：

| 别名        | 实际类型         | 说明                   |
|-------------|------------------|------------------------|
| `string`    | `std::string`    | 日志系统统一字符串类型 |
| `sd_int`    | `int`            | 有符号整型（行号等）   |

### LoaderParamList

定义于 `ruac::rstd::logsystem`，用于配置日志配置文件的路径与文件名，作为 `init()` 的入参：

```cpp
struct LoaderParamList {
    logtype::string m_fpath{logpath::G_READ_LOG_CONFIG_FILE_PATH};
    logtype::string m_fname{logpath::G_READ_LOG_CONFIG_FILE_NAME};
};
```

| 成员       | 类型               | 说明                       |
|------------|--------------------|----------------------------|
| `m_fpath`  | `logtype::string`  | 配置文件路径，默认为全局常量。 |
| `m_fname`  | `logtype::string`  | 配置文件名，默认为全局常量。 |

## 数据结构

### LogRuntimeParamList

```cpp
struct LogRuntimeParamList {
    bool m_enable_log_runtime{false};
};
```

`LogRuntime` 的运行时参数集合，用于控制日志运行时的行为。

**成员**

| 成员                   | 类型   | 默认值   | 说明                                   |
|------------------------|--------|----------|----------------------------------------|
| `m_enable_log_runtime` | `bool` | `false`  | 是否启用日志运行时。为 `false` 时 `write` 直接返回。 |

## 类定义

```cpp
namespace ruac::rstd::logsystem::api {

    class LogRuntime {
      private:
        LogRuntimeParamList m_params;
        LogRuntime() = default;
        ~LogRuntime() = default;
        LogRuntime(const LogRuntime &) = delete;
        LogRuntime &operator=(const LogRuntime &) = delete;

      private:
        std::unique_ptr<Manager> m_manager{nullptr};
        bool m_init_done{false};
        bool m_once_msgs{false};

      public:
        void setting(const LogRuntimeParamList &params_ = {});
        static auto instance() -> LogRuntime &;
        void init(const LoaderParamList &params_ = {});
        void write(logenum::Level level_, const logtype::string &message_, const logtype::string &file_,
                   logtype::sd_int line_);
    };

} // namespace ruac::rstd::logsystem::api
```

## 设计说明

- **单例模式**：构造、析构、拷贝构造与拷贝赋值均为 `private` 或 `delete`，仅能通过静态方法 `instance()` 获取唯一实例。`instance()` 内部使用函数局部静态变量，保证初始化的线程安全性。
- **两阶段使用**：典型使用顺序为先调用 `setting()` 配置运行时开关，再调用 `init()` 完成底层 `Manager` 初始化，最后通过 `write()` 或便捷宏写入日志。
- **防护逻辑**：`write()` 在委托 `Manager` 之前执行三段式防护（未初始化一次性告警、运行时开关检查），避免在未就绪状态下访问空指针。

## 成员函数

### instance()

```cpp
static auto instance() -> LogRuntime &;
```

获取 `LogRuntime` 的单例引用。首次调用时构造函数局部静态对象，后续调用直接返回其引用。

**返回值**

| 类型            | 说明                          |
|-----------------|-------------------------------|
| `LogRuntime &`  | `LogRuntime` 单例的引用。     |

---

### setting(const LogRuntimeParamList &)

```cpp
void setting(const LogRuntimeParamList &params_ = {});
```

设置运行时参数。将传入的参数列表拷贝存储至内部 `m_params`，供后续 `write()` 检查 `m_enable_log_runtime` 开关使用。

**参数**

| 参数       | 类型                            | 默认值 | 说明                       |
|------------|---------------------------------|--------|----------------------------|
| `params_`  | `const LogRuntimeParamList &`   | `{}`   | 运行时参数列表。           |

**说明**

- 默认参数为 `{}`，即 `m_enable_log_runtime` 默认为 `false`，调用方需显式置为 `true` 才能启用日志写入。
- 该方法可在 `init()` 之前或之后调用；`write()` 每次都会读取最新的 `m_params`。

---

### init(const LoaderParamList &)

```cpp
void init(const LoaderParamList &params_ = {});
```

初始化日志运行时。内部通过 `std::make_unique` 创建 `Manager` 实例，委托 `m_manager->init(params_)` 加载配置文件并构建输出/格式化管线，最后将 `m_init_done` 置为 `true`。

**参数**

| 参数       | 类型                          | 默认值 | 说明                             |
|------------|-------------------------------|--------|----------------------------------|
| `params_`  | `const LoaderParamList &`     | `{}`   | 加载器参数列表（配置文件路径/文件名）。 |

**说明**

- 必须在 `write()` 能正常写入日志之前调用。若未初始化，`write()` 会输出一次性告警并直接返回。
- 默认参数为 `{}`，使用 `logpath` 命名空间中的全局默认路径与文件名。
- 重复调用 `init()` 会创建新的 `Manager` 并替换旧实例（旧实例由 `unique_ptr` 释放）。

---

### write(logenum::Level, const logtype::string &, const logtype::string &, logtype::sd_int)

```cpp
void write(logenum::Level level_,
           const logtype::string &message_,
           const logtype::string &file_,
           logtype::sd_int line_);
```

写入一条日志消息。在委托底层 `Manager` 执行实际写入前，执行三段式防护逻辑：

1. **未初始化检查**：若 `m_init_done` 为 `false` 且 `m_once_msgs` 为 `false`，将 `m_once_msgs` 置为 `true`，拼接一条包含当前时间与调试追踪信息的告警，通过 `Message::instance().stdout_err()` 输出到标准错误，然后返回。该告警仅输出一次。
2. **运行时开关检查**：若 `m_params.m_enable_log_runtime` 为 `false`，直接返回，不写入日志。
3. **委托写入**：调用 `m_manager->write(level_, message_, file_, line_)` 执行实际日志写入。

**参数**

| 参数        | 类型                       | 说明                             |
|-------------|----------------------------|----------------------------------|
| `level_`    | `logenum::Level`           | 日志级别（DEBUG/INFO/WARNING/ERROR/FATAL）。 |
| `message_`  | `const logtype::string &`  | 日志消息内容。                   |
| `file_`     | `const logtype::string &`  | 产生日志的源文件名。             |
| `line_`     | `logtype::sd_int`          | 产生日志的源代码行号。           |

**返回值**

无（`void`）。

**异常**

- 在已初始化且开关开启的正常路径下，异常行为取决于底层 `Manager::write()` 的实现。

## 便捷宏

头文件在类定义之外提供了一组便捷宏，用于简化日志写入调用。宏内部自动调用 `instance()` 获取单例，并通过 `__FILE__` 与 `__LINE__` 自动填充源文件名与行号。

### RUAC_API_LOG_RUNTIME

```cpp
#define RUAC_API_LOG_RUNTIME(level_, message_)
```

通用日志写入宏，展开为：

```cpp
ruac::rstd::logsystem::api::LogRuntime::instance().write(level_, message_, __FILE__, __LINE__);
```

**参数**

| 参数        | 说明                              |
|-------------|-----------------------------------|
| `level_`    | `logenum::Level` 枚举值。         |
| `message_`  | 日志消息内容（字符串）。          |

### 级别专用宏

以下宏基于 `RUAC_API_LOG_RUNTIME` 进一步封装，固定使用对应的日志级别：

| 宏                     | 对应级别                | 说明                     |
|------------------------|-------------------------|--------------------------|
| `RUAC_RUNTIME_DEBUG`   | `logenum::Level::DEBUG` | 写入 DEBUG 级别日志。    |
| `RUAC_RUNTIME_INFO`    | `logenum::Level::INFO`  | 写入 INFO 级别日志。     |
| `RUAC_RUNTIME_WARNING` | `logenum::Level::WARNING` | 写入 WARNING 级别日志。|
| `RUAC_RUNTIME_ERROR`   | `logenum::Level::ERROR` | 写入 ERROR 级别日志。    |
| `RUAC_RUNTIME_FATAL`   | `logenum::Level::FATAL` | 写入 FATAL 级别日志。    |

使用形式：`RUAC_RUNTIME_INFO("some message")`。

## 使用示例

```cpp
#include "rstd/logsystem/ruac_api_log_runtime.hpp"

using namespace ruac::rstd::logsystem;

// 1. 配置运行时参数：启用日志运行时
api::LogRuntimeParamList params;
params.m_enable_log_runtime = true;
api::LogRuntime::instance().setting(params);

// 2. 初始化（使用默认配置文件路径/文件名）
api::LogRuntime::instance().init();

// 3. 通过便捷宏写入日志（自动填充文件名与行号）
RUAC_RUNTIME_DEBUG("debug message");
RUAC_RUNTIME_INFO("info message");
RUAC_RUNTIME_WARNING("warning message");
RUAC_RUNTIME_ERROR("error message");
RUAC_RUNTIME_FATAL("fatal message");

// 4. 也可直接调用 write
api::LogRuntime::instance().write(
    logenum::Level::INFO, "manual info", __FILE__, __LINE__);
```

## 注意事项

- **初始化顺序**：`init()` 必须在期望正常写入日志之前调用。未初始化时 `write()` 仅输出一次标准错误告警，后续调用静默返回。
- **运行时开关**：`m_enable_log_runtime` 默认为 `false`。若未通过 `setting()` 显式启用，即使已初始化，`write()` 也会直接返回而不写入任何日志。
- **一次性告警**：未初始化告警通过 `m_once_msgs` 标志保证仅在首次调用 `write()` 时输出一次，避免日志刷屏。
- **单例不可拷贝**：`LogRuntime` 禁用拷贝构造与拷贝赋值，只能通过 `instance()` 获取引用使用。
- **宏的使用场景**：便捷宏内部使用 `__FILE__` 与 `__LINE__`，因此必须在希望记录真实源码位置的调用点直接使用，无法通过函数转发保留原始位置。
