# Sink Pipeline 职责转移到 Manager

**Goal:** 将指针对象（Output/Format）的生成与析构从 Allocator 转移到 Manager，Allocator 仅负责返回 AllocatorParamList。

**Architecture:** Allocator 保持纯配置解析角色，只产出 `AllocatorParamList`（含文件路径配置）；Manager 接管 sink pipeline 的生命周期管理（创建、持有、析构 Output/Format 对象）。`SinkPair` 和 `SinkPipeline` 结构体定义在 Manager 侧。

**Tech Stack:** C++20, 裸指针 + 手动 delete（保持现有风格）

## 最终状态

### AllocatorParamList（含文件路径配置）
```cpp
struct AllocatorParamList {
    logtype::string m_wf_path{""};
    logtype::string m_wf_name{""};
    logtype::string m_limit_f{""};
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
```

### Allocator — 纯配置解析器
- 仅暴露 `get_param_list()` 和 `out_loader_msg()`
- 无 sink pipeline 相关代码
- 文件路径/名称/限制写入 `m_param_list`

### Manager — Sink Pipeline 生命周期管理
- 持有 `m_wf_path`、`m_wf_name` 成员（从 AllocatorParamList 初始化）
- 持有 `SinkPipeline m_sink_pipeline`
- `create_sink_output(Output *&, const logenum::Output &)` — 使用成员变量 m_wf_path/m_wf_name
- `create_sink_format(Format *&, const logenum::Format &)`
- `delete_sink_output(Output *&)` / `delete_sink_format(Format *&)`
- `init_sink_pipeline(const AllocatorParamList &)` — 设置成员变量并创建 sink
- `over_sink_pipeline()` — 析构所有 sink 对象
- `~Manager()` 调用 `over_sink_pipeline()`
