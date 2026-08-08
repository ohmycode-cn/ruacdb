# kernel 模块 API - ControllerTable（控制器表）

## 模块概述

`ControllerTable` 类归属于 `ruac::kernel` 命名空间，是内核层的控制器注册表。它采用单例模式（线程安全的函数局部静态变量），以 `uid`（唯一标识符）为键，维护 `controller::Operation` 实例的引用映射，供上层按 uid 注册并检索控制器操作。

`ControllerTable` 自身不持有 `Operation` 的所有权，仅保存指向 `Operation` 的裸指针，因此调用方必须保证被注册的 `Operation` 对象生命周期长于其在表中的使用期。

## 命名空间与头文件

- 命名空间：`ruac::kernel`
- 头文件：`include/kernel/ruac_controller_table.hpp`
- 源文件：`src/kernel/ruac_controller_table.cpp`

## 类定义

```cpp
namespace ruac::kernel {

    class ControllerTable {
      private:
        std::unordered_map<int, ruac::kernel::controller::Operation *> m_controller_table;

      private:
        ControllerTable() = default;
        ~ControllerTable() = default;
        ControllerTable(const ControllerTable &) = delete;
        ControllerTable &operator=(const ControllerTable &) = delete;

      public:
        static auto instance() -> ControllerTable &;
        auto set_controller(int uid, ruac::kernel::controller::Operation &controller) -> bool;
        auto get_controller(int uid) -> ruac::kernel::controller::Operation &;
    };

} // namespace ruac::kernel
```

## 设计说明

- **单例模式**：构造、析构、拷贝构造与拷贝赋值均为 `private` 或 `delete`，仅能通过静态方法 `instance()` 获取唯一实例。`instance()` 内部使用函数局部静态变量，由 C++11 起保证其初始化的线程安全性。
- **存储结构**：内部使用 `std::unordered_map<int, controller::Operation *>`，以 `uid` 为键、`Operation` 指针为值。
- **非拥有式**：表中存储的是 `Operation *` 裸指针，`ControllerTable` 不管理 `Operation` 的生命周期，调用方需自行保证对象有效。

## 成员函数

### instance()

```cpp
static auto instance() -> ControllerTable &;
```

获取 `ControllerTable` 的单例引用。首次调用时构造函数局部静态对象，后续调用直接返回其引用，提供线程安全的单例访问入口。

**返回值**

| 类型               | 说明                           |
|--------------------|--------------------------------|
| `ControllerTable &` | `ControllerTable` 单例的引用。 |

---

### set_controller(int, controller::Operation &)

```cpp
auto set_controller(int uid, ruac::kernel::controller::Operation &controller) -> bool;
```

按 `uid` 注册一个控制器操作。首先在表中查找该 `uid`：

- 若已存在对应条目，则返回 `false`，且不修改表中内容；
- 若不存在，则将传入 `controller` 的地址存入表中，并返回 `true`。

**参数**

| 参数           | 类型                                       | 说明                              |
|----------------|--------------------------------------------|-----------------------------------|
| `uid`          | `int`                                      | 用于查找控制器的唯一标识符。      |
| `controller`   | `ruac::kernel::controller::Operation &`    | 待注册的控制器操作实例的引用。    |

**返回值**

| 类型   | 说明                                                                 |
|--------|----------------------------------------------------------------------|
| `bool` | `true` 表示控制器已成功存入；`false` 表示该 `uid` 已存在条目。       |

---

### get_controller(int)

```cpp
auto get_controller(int uid) -> ruac::kernel::controller::Operation &;
```

按 `uid` 检索已注册的控制器操作。

- 若在表中找到匹配条目，返回所存储 `Operation` 的引用；
- 若未找到匹配条目，抛出 `std::runtime_error`，异常信息描述缺少对应 uid。

**参数**

| 参数    | 类型   | 说明                              |
|---------|--------|-----------------------------------|
| `uid`   | `int`  | 用于查找控制器的唯一标识符。      |

**返回值**

| 类型                                            | 说明                           |
|-------------------------------------------------|--------------------------------|
| `ruac::kernel::controller::Operation &`         | 与 `uid` 关联的控制器操作引用。|

**异常**

| 类型                  | 触发条件                                  |
|-----------------------|-------------------------------------------|
| `std::runtime_error`  | 表中不存在与 `uid` 匹配的条目时抛出。     |

## 使用示例

```cpp
#include "kernel/ruac_controller.hpp"
#include "kernel/ruac_controller_table.hpp"

using namespace ruac::kernel;

// 创建并配置控制器操作
controller::Operation op;
op.setObjectStrategy(object::Single::obitan());

// 注册到控制器表
auto &table = ControllerTable::instance();
bool ok = table.set_controller(1001, op);   // 返回 true

// 按 uid 检索
auto &got = table.get_controller(1001);     // 返回 op 的引用
(void)got;

// 重复注册同一 uid 将失败
bool dup = table.set_controller(1001, op);  // 返回 false

// 检索不存在的 uid 将抛出异常
try {
    table.get_controller(9999);
} catch (const std::runtime_error &e) {
    // e.what() == "Controller not found for the given UID"
}
```

## 注意事项

- `ControllerTable` 不接管 `Operation` 的所有权，调用方必须确保被注册的 `Operation` 对象在表使用期间始终有效，否则 `get_controller` 返回的引用将悬垂。
- `set_controller` 在 `uid` 已存在时直接返回 `false` 而不会覆盖既有条目，如需替换需调用方自行管理（当前接口未提供删除或更新方法）。
- `get_controller` 在 `uid` 缺失时抛出 `std::runtime_error`，调用方应做好异常处理或确保 uid 已通过 `set_controller` 注册。
