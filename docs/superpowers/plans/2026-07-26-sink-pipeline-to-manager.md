# Sink Pipeline 职责转移到 Manager

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 将指针对象（Output/Format）的生成与析构从 Allocator 转移到 Manager，Allocator 仅负责返回 AllocatorParamList。

**Architecture:** Allocator 保持纯配置解析角色，只产出 `AllocatorParamList`；Manager 接管 sink pipeline 的生命周期管理（创建、持有、析构 Output/Format 对象）。`SinkPair` 和 `AllocatorSinkPipeline` 结构体随职责转移到 Manager 侧。

**Tech Stack:** C++20, 裸指针 + 手动 delete（保持现有风格）

## Global Constraints

- 遵循 RUAC-CCXX-STYLE-GUIDE.md（100 列软换行，120 列硬换行）
- 保持现有命名风格（`m_` 前缀成员变量）
- Output/Format 基类已有虚析构函数，裸指针 delete 安全

---

### Task 1: 精简 Allocator — 移除 sink pipeline 相关代码

**Files:**
- Modify: `include/rstd/logsystem/ruac_allocator.hpp`
- Modify: `src/rstd/logsystem/ruac_allocator.cpp`

**Interfaces:**
- Produces: `Allocator` 仅暴露 `get_param_list()` 和 `out_loader_msg()`

- [ ] **Step 1: 修改 `ruac_allocator.hpp`**

从 `ruac_allocator.hpp` 中移除：
- `SinkPair` 结构体（匿名 namespace 内，第 37-41 行）
- `AllocatorSinkPipeline` 结构体（第 44-47 行）
- `Allocator` 类中的 `m_sink_pipeline` 成员（第 56 行）
- `Allocator` 类中的 sink 创建/销毁私有方法声明（第 71-74 行）
- `init_sink_pipeline()` 和 `over_sink_pipeline()` 声明（第 79-80 行）
- `get_sink_pipeline()` 公有方法声明（第 87 行）

同时移除不再需要的 include：`ruac_output.hpp`、`ruac_format.hpp`

**最终 `ruac_allocator.hpp` 应为：**

```cpp
#pragma once
#ifndef RUAC_ALLOCATOR_HPP
#define RUAC_ALLOCATOR_HPP

#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_loader.hpp"

namespace ruac::rstd::logsystem {

    struct AllocatorParamList {
        logenum::Output m_term_output{logenum::Output::CONSOLE};
        logenum::Output m_file_output{logenum::Output::CONSOLE};
        logenum::Format m_term_format{logenum::Format::TEXT};
        logenum::Format m_file_format{logenum::Format::TEXT};
        logenum::Level m_term_level{logenum::Level::DEBUG};
        logenum::Level m_file_level{logenum::Level::DEBUG};
        logenum::Level m_mini_level{logenum::Level::DEBUG};
        bool m_enable_ht{false};
        bool m_enable_bf{false};
        bool m_enable_ce{true};
    };

    class Allocator {
      private:
        logtype::string m_wf_path{""};
        logtype::string m_wf_name{""};
        logtype::string m_limit_f{""};

      private:
        AllocatorParamList m_param_list{};
        logtype::strmap m_default_map{};
        logtype::strmap m_loader_map{};
        logtype::strmap m_std_map{};
        logtype::string m_loader_msg{""};
        bool m_once_lock_guard{false};

      private:
        void parser_config_bool_value(logtype::strmap &map_, const logtype::string key_, bool &val_);
        void parser_config_output(logtype::strmap &map_, const logtype::string key_, logenum::Output &val_, bool isf_);
        void parser_config_format(logtype::strmap &map_, const logtype::string key_, logenum::Format &val_, bool isf_);
        void parser_config_log_level(logtype::strmap &map_, const logtype::string key_, logenum::Level &val_);

      private:
        void init_default_map();
        void parser_verify_configure_map();

      public:
        Allocator(const LoaderParamList &loader_param_list = {});
        ~Allocator() = default;

      public:
        auto get_param_list() -> AllocatorParamList;
        void out_loader_msg();
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_ALLOCATOR_HPP
```

- [ ] **Step 2: 修改 `ruac_allocator.cpp`**

从 `ruac_allocator.cpp` 中移除：
- `#include "rstd/logsystem/ruac_output_console.hpp"`
- `#include "rstd/logsystem/ruac_output_file.hpp"`
- `#include "rstd/logsystem/ruac_format_json.hpp"`
- `#include "rstd/logsystem/ruac_format_text.hpp"`
- `#include "rstd/logsystem/ruac_format_xml.hpp"`
- `#include "rstd/logsystem/ruac_confmap.hpp"`（仍需保留，因为 `init_default_map()` 使用）
- 析构函数 `Allocator::~Allocator()`（改为 default，从头文件移除声明即可）
- `create_sink_output()` 方法（第 183-196 行）
- `create_sink_format()` 方法（第 208-224 行）
- `delete_sink_output()` 方法（第 235-241 行）
- `delete_sink_format()` 方法（第 252-258 行）
- `init_sink_pipeline()` 方法（第 351-356 行）
- `over_sink_pipeline()` 方法（第 366-371 行）
- `get_sink_pipeline()` 方法（第 280-282 行）

构造函数中移除 `init_sink_pipeline()` 调用，析构函数移除 `over_sink_pipeline()` 调用（析构改为 default）。

**构造函数最终形态：**

```cpp
Allocator::Allocator(const LoaderParamList &loader_param_list) {
    {
        Loader loader(loader_param_list);
        m_loader_map = loader.getmap();
        m_loader_msg = loader.outmap_string(m_loader_map);
        init_default_map();
    }
    parser_verify_configure_map();
}
```

- [ ] **Step 3: 编译验证**

```bash
cd /home/repox/Engdev/ruacdb && cmake --build build
```

---

### Task 2: Manager 接管 Sink Pipeline 生命周期

**Files:**
- Modify: `include/rstd/logsystem/ruac_manager.hpp`
- Modify: `src/rstd/logsystem/ruac_manager.cpp`

**Interfaces:**
- Consumes: `Allocator::get_param_list()` → `AllocatorParamList`
- Produces: `Manager` 持有 `AllocatorSinkPipeline`，负责创建/析构 Output/Format 对象

- [ ] **Step 1: 修改 `ruac_manager.hpp`**

在 `ruac_manager.hpp` 中添加 sink pipeline 结构体和相关声明：

```cpp
#pragma once

#ifndef RUAC_MANAGER_HPP
#define RUAC_MANAGER_HPP

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logmaps.hpp"
#include "rstd/logsystem/ruac_format.hpp"
#include "rstd/logsystem/ruac_output.hpp"
#include <memory>

namespace ruac::rstd::logsystem {

    namespace {
        struct SinkPair {
            Output *m_output_{nullptr};
            Format *m_format_{nullptr};
        };
    } // namespace

    struct SinkPipeline {
        SinkPair m_term_sink;
        SinkPair m_file_sink;
    };

    class Manager {
      private:
        logtype::strmap m_text_level_map_{logmaps::get_text_level_map()};
        logtype::strmap m_ansi_level_map_{logmaps::get_ansi_level_map()};

      private:
        bool m_guard_marker{false};
        std::unique_ptr<Allocator> m_allocator{nullptr};
        SinkPipeline m_sink_pipeline{};

      private:
        void create_sink_output(Output *&out_, logenum::Output &enum_out_,
                                const logtype::string &wf_path_,
                                const logtype::string &wf_name_);
        void create_sink_format(Format *&fmt_, logenum::Format &enum_fmt_);
        void delete_sink_output(Output *&out_);
        void delete_sink_format(Format *&fmt_);

      private:
        void init_sink_pipeline(const AllocatorParamList &params_);
        void over_sink_pipeline();

        void out_stream(
            Format *&format_,
            Output *&output_,
            const logtype::strmap &strmap_,
            const logtype::string &time_,
            const logtype::string &level_,
            const logtype::seqnum &sequence_,
            const logtype::string &message_,
            const logtype::string &file_,
            logtype::sd_int line_);

      public:
        Manager() = default;
        ~Manager();

      public:
        void init(const LoaderParamList &params_ = {});
        void write(logenum::Level level_, const logtype::string &message_,
                   const logtype::string &file_, logtype::sd_int line_);
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_MANAGER_HPP
```

关键变化：
- 新增 `SinkPair`、`SinkPipeline` 结构体（从 Allocator 搬来）
- `Manager` 新增 `m_sink_pipeline` 成员
- 新增 `create_sink_output`、`create_sink_format`、`delete_sink_output`、`delete_sink_format`、`init_sink_pipeline`、`over_sink_pipeline` 私有方法
- 析构函数改为显式 `~Manager()`（需实现清理逻辑）

- [ ] **Step 2: 修改 `ruac_manager.cpp`**

将 sink 工厂方法和生命周期管理实现搬到 Manager，`create_sink_output` 需要接收文件路径参数（原 Allocator 成员）。

```cpp
#include "rstd/logsystem/ruac_manager.hpp"
#include "rstd/logsystem/ruac_output_console.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"

namespace ruac::rstd::logsystem {

    Manager::~Manager() {
        over_sink_pipeline();
    }

    void Manager::create_sink_output(Output *&out_, logenum::Output &enum_out_,
                                     const logtype::string &wf_path_,
                                     const logtype::string &wf_name_) {
        if (nullptr != out_) {
            return;
        }
        switch (enum_out_) {
        case logenum::Output::FILE:
            out_ = new OutputFile(wf_path_, wf_name_, true);
            break;
        case logenum::Output::CONSOLE:
            out_ = new OutputConsole();
            break;
        }
    }

    void Manager::create_sink_format(Format *&fmt_, logenum::Format &enum_fmt_) {
        if (nullptr != fmt_) {
            return;
        }
        switch (enum_fmt_) {
        case logenum::Format::JSON:
            fmt_ = new FormatJson();
            break;
        case logenum::Format::TEXT:
            fmt_ = new FormatText();
            break;
        case logenum::Format::XML:
            fmt_ = new FormatXML();
            break;
        }
    }

    void Manager::delete_sink_output(Output *&out_) {
        if (nullptr == out_) {
            return;
        }
        delete out_;
        out_ = nullptr;
    }

    void Manager::delete_sink_format(Format *&fmt_) {
        if (nullptr == fmt_) {
            return;
        }
        delete fmt_;
        fmt_ = nullptr;
    }

    void Manager::init_sink_pipeline(const AllocatorParamList &params_) {
        // 需要文件路径信息，从 Allocator 获取
        // 暂时使用空字符串，后续通过 Allocator 暴露路径 getter 或在 ParamList 中添加
        create_sink_output(m_sink_pipeline.m_file_sink.m_output_,
                           params_.m_file_output, "", "");
        create_sink_output(m_sink_pipeline.m_term_sink.m_output_,
                           params_.m_term_output, "", "");
        create_sink_format(m_sink_pipeline.m_file_sink.m_format_,
                           params_.m_file_format);
        create_sink_format(m_sink_pipeline.m_term_sink.m_format_,
                           params_.m_term_format);
    }

    void Manager::over_sink_pipeline() {
        delete_sink_output(m_sink_pipeline.m_file_sink.m_output_);
        delete_sink_output(m_sink_pipeline.m_term_sink.m_output_);
        delete_sink_format(m_sink_pipeline.m_file_sink.m_format_);
        delete_sink_format(m_sink_pipeline.m_term_sink.m_format_);
    }

    void Manager::out_stream(Format *&format_, Output *&output_,
                             const logtype::strmap &strmap_,
                             const logtype::string &time_,
                             const logtype::string &level_,
                             const logtype::seqnum &sequence_,
                             const logtype::string &message_,
                             const logtype::string &file_,
                             logtype::sd_int line_) {
        if (nullptr == format_ || nullptr == output_) {
            return;
        }
        auto time = logtime::get_time();
        auto strs = format_->format(strmap_, time, level_, sequence_,
                                    message_, file_, line_);
        output_->output(strs);
    }

    void Manager::init(const LoaderParamList &params_) {
        m_allocator = std::make_unique<Allocator>(params_);
        init_sink_pipeline(m_allocator->get_param_list());
    }

    void Manager::write(logenum::Level level_, const logtype::string &message_,
                        const logtype::string &file_, logtype::sd_int line_) {
    }

} // namespace ruac::rstd::logsystem
```

- [ ] **Step 3: 编译验证**

```bash
cd /home/repox/Engdev/ruacdb && cmake --build build
```

---

### Task 3: 补充 Allocator 的文件路径 getter（解决 init_sink_pipeline 参数问题）

**Files:**
- Modify: `include/rstd/logsystem/ruac_allocator.hpp`
- Modify: `src/rstd/logsystem/ruac_allocator.cpp`
- Modify: `include/rstd/logsystem/ruac_manager.hpp`（可选，如果选择在 ParamList 中加字段）
- Modify: `src/rstd/logsystem/ruac_manager.cpp`

**Interfaces:**
- Produces: Allocator 提供 `get_wf_path()` / `get_wf_name()` getter

- [ ] **Step 1: 在 Allocator 中添加 getter**

在 `ruac_allocator.hpp` 的 `Allocator` 类 public 区域添加：

```cpp
auto get_wf_path() -> const logtype::string &;
auto get_wf_name() -> const logtype::string &;
```

在 `ruac_allocator.cpp` 中实现：

```cpp
auto Allocator::get_wf_path() -> const logtype::string & {
    return m_wf_path;
}

auto Allocator::get_wf_name() -> const logtype::string & {
    return m_wf_name;
}
```

- [ ] **Step 2: 更新 Manager::init_sink_pipeline 使用真实路径**

```cpp
void Manager::init_sink_pipeline(const AllocatorParamList &params_) {
    const auto &wf_path = m_allocator->get_wf_path();
    const auto &wf_name = m_allocator->get_wf_name();
    create_sink_output(m_sink_pipeline.m_file_sink.m_output_,
                       params_.m_file_output, wf_path, wf_name);
    create_sink_output(m_sink_pipeline.m_term_sink.m_output_,
                       params_.m_term_output, wf_path, wf_name);
    create_sink_format(m_sink_pipeline.m_file_sink.m_format_,
                       params_.m_file_format);
    create_sink_format(m_sink_pipeline.m_term_sink.m_format_,
                       params_.m_term_format);
}
```

- [ ] **Step 3: 编译验证**

```bash
cd /home/repox/Engdev/ruacdb && cmake --build build
```

---

### Task 4: 更新测试代码

**Files:**
- Modify: `src/test/ruac_test_logsystem.cpp`

- [ ] **Step 1: 确认测试代码编译通过**

测试中 `test_allocator()` 直接使用 `Allocator` 实例，不涉及 sink pipeline，应无需修改。验证编译即可。

```bash
cd /home/repox/Engdev/ruacdb && cmake --build build
```

如果编译报错（如缺少被移除的头文件引用），更新 include。
