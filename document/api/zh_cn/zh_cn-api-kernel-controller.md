# kernel 模块 API - Controller（控制器操作）

## 模块概述

`controller` 命名空间归属于 `ruac::kernel`，提供控制器操作类 `Operation`。该类负责管理对象（object）、状态（state）和轨迹（track）三类策略，每类策略均通过 `std::variant` 同时容纳单例（Single）与多例（Multis）两种实现形态。

`Operation` 类本身不持有具体业务逻辑，而是作为策略的容器与分发入口：调用方通过 `set*Strategy` 注入某一形态的策略，再通过 `get*Strategy` 取回变体（variant）以交由上层进行 `std::visit` 派发。

## 命名空间与头文件

- 命名空间：`ruac::kernel::controller`
- 头文件：`include/kernel/ruac_controller.hpp`
- 源文件：`src/kernel/ruac_controller.cpp`

## 类型别名

策略相关的具体类型通过 `ruac::kernel::defname` 命名空间统一别名声明，`Operation` 内部使用这些别名以简化变体声明：

| 别名    | 实际类型                          | 说明               |
|---------|-----------------------------------|--------------------|
| `objs`  | `ruac::kernel::object::Single`    | 对象单例管理器     |
| `objm`  | `ruac::kernel::object::Multis`    | 对象多例管理器     |
| `stas`  | `ruac::kernel::state::Single`     | 状态单例管理器     |
| `stam`  | `ruac::kernel::state::Multis`     | 状态多例管理器     |
| `tras`  | `ruac::kernel::track::Single`     | 轨迹单例管理器     |
| `tram`  | `ruac::kernel::track::Multis`     | 轨迹多例管理器     |

## 策略变体类型

每类策略的变体类型均为「指向 Single 的裸指针」与「持有 Multis 的独占指针」二选一：

```cpp
// 对象策略变体
std::variant<defname::objs *, std::unique_ptr<defname::objm>>;

// 状态策略变体
std::variant<defname::stas *, std::unique_ptr<defname::stam>>;

// 轨迹策略变体
std::variant<defname::tras *, std::unique_ptr<defname::tram>>;
```

- 当传入 Single 引用时，变体存储其地址（`Single *`），`Operation` 不接管其生命周期。
- 当传入 Multis 的 `std::unique_ptr` 时，变体通过转移所有权持有该多例对象，`Operation` 负责其生命周期。

## 类定义

```cpp
namespace ruac::kernel::controller {

    class Operation {
      private:
        std::variant<defname::objs *, std::unique_ptr<defname::objm>> m_object_strategy;
        std::variant<defname::stas *, std::unique_ptr<defname::stam>> m_state_strategy;
        std::variant<defname::tras *, std::unique_ptr<defname::tram>> m_track_strategy;

      public:
        Operation();
        ~Operation();

      public:
        void set_object_strategy(defname::objs &single_);
        void set_object_strategy(std::unique_ptr<defname::objm> multis_);
        auto get_object_strategy() -> std::variant<defname::objs *, std::unique_ptr<defname::objm>> &;

        void set_state_strategy(defname::stas &state_single_);
        void set_state_strategy(std::unique_ptr<defname::stam> state_multis_);
        auto get_state_strategy() -> std::variant<defname::stas *, std::unique_ptr<defname::stam>> &;

        void set_track_strategy(defname::tras &track_single_);
        void set_track_strategy(std::unique_ptr<defname::tram> track_multis_);
        auto get_track_strategy() -> std::variant<defname::tras *, std::unique_ptr<defname::tram>> &;
    }; // Operation

} // namespace ruac::kernel::controller
```

## 成员函数

### 构造与析构

#### Operation()

```cpp
Operation();
```

默认构造函数，创建一个未注入任何策略的 `Operation` 实例。三个策略变体均处于默认构造的空状态。

#### ~Operation()

```cpp
~Operation();
```

默认析构函数。当任一策略变体持有 `std::unique_ptr<Multis>` 时，由 `unique_ptr` 自动释放对应多例对象；持有 `Single *` 的变体不会释放所指向的单例（其生命周期由单例自身管理）。

---

### 对象策略（Object Strategy）

#### set_object_strategy(defname::objs &)

```cpp
void set_object_strategy(defname::objs &single_);
```

以单例引用形式设置对象策略。内部将传入引用取地址后存入变体，`Operation` 不接管该单例的生命周期。

**参数**

| 参数       | 类型                | 说明                       |
|------------|---------------------|----------------------------|
| `single_`  | `defname::objs &`   | 对象单例 `Single` 的引用。 |

#### set_object_strategy(std::unique_ptr\<defname::objm\>)

```cpp
void set_object_strategy(std::unique_ptr<defname::objm> multis_);
```

以独占指针形式设置对象策略。通过 `std::move` 转移所有权，`Operation` 将接管该多例对象的生命周期。

**参数**

| 参数       | 类型                              | 说明                              |
|------------|-----------------------------------|-----------------------------------|
| `multis_`  | `std::unique_ptr<defname::objm>`  | 指向对象多例 `Multis` 的独占指针。 |

#### get_object_strategy()

```cpp
auto get_object_strategy() -> std::variant<defname::objs *, std::unique_ptr<defname::objm>> &;
```

获取对象策略变体的可变引用，供上层通过 `std::visit` 进行策略派发。

**返回值**

| 类型                                                              | 说明                         |
|-------------------------------------------------------------------|------------------------------|
| `std::variant<defname::objs *, std::unique_ptr<defname::objm>> &` | 对象策略变体的可变引用。     |

---

### 状态策略（State Strategy）

#### set_state_strategy(defname::stas &)

```cpp
void set_state_strategy(defname::stas &state_single_);
```

以单例引用形式设置状态策略。内部将传入引用取地址后存入变体，`Operation` 不接管该单例的生命周期。

**参数**

| 参数              | 类型                | 说明                       |
|-------------------|---------------------|----------------------------|
| `state_single_`   | `defname::stas &`   | 状态单例 `Single` 的引用。 |

#### set_state_strategy(std::unique_ptr\<defname::stam\>)

```cpp
void set_state_strategy(std::unique_ptr<defname::stam> state_multis_);
```

以独占指针形式设置状态策略。通过 `std::move` 转移所有权，`Operation` 将接管该多例对象的生命周期。

**参数**

| 参数              | 类型                              | 说明                              |
|-------------------|-----------------------------------|-----------------------------------|
| `state_multis_`   | `std::unique_ptr<defname::stam>`  | 指向状态多例 `Multis` 的独占指针。 |

#### get_state_strategy()

```cpp
auto get_state_strategy() -> std::variant<defname::stas *, std::unique_ptr<defname::stam>> &;
```

获取状态策略变体的可变引用，供上层通过 `std::visit` 进行策略派发。

**返回值**

| 类型                                                              | 说明                         |
|-------------------------------------------------------------------|------------------------------|
| `std::variant<defname::stas *, std::unique_ptr<defname::stam>> &` | 状态策略变体的可变引用。     |

---

### 轨迹策略（Track Strategy）

#### set_track_strategy(defname::tras &)

```cpp
void set_track_strategy(defname::tras &track_single_);
```

以单例引用形式设置轨迹策略。内部将传入引用取地址后存入变体，`Operation` 不接管该单例的生命周期。

**参数**

| 参数              | 类型                | 说明                       |
|-------------------|---------------------|----------------------------|
| `track_single_`   | `defname::tras &`   | 轨迹单例 `Single` 的引用。 |

#### set_track_strategy(std::unique_ptr\<defname::tram\>)

```cpp
void set_track_strategy(std::unique_ptr<defname::tram> track_multis_);
```

以独占指针形式设置轨迹策略。通过 `std::move` 转移所有权，`Operation` 将接管该多例对象的生命周期。

**参数**

| 参数              | 类型                              | 说明                              |
|-------------------|-----------------------------------|-----------------------------------|
| `track_multis_`   | `std::unique_ptr<defname::tram>`  | 指向轨迹多例 `Multis` 的独占指针。 |

#### get_track_strategy()

```cpp
auto get_track_strategy() -> std::variant<defname::tras *, std::unique_ptr<defname::tram>> &;
```

获取轨迹策略变体的可变引用，供上层通过 `std::visit` 进行策略派发。

**返回值**

| 类型                                                              | 说明                         |
|-------------------------------------------------------------------|------------------------------|
| `std::variant<defname::tras *, std::unique_ptr<defname::tram>> &` | 轨迹策略变体的可变引用。     |

## 使用示例

```cpp
#include "kernel/ruac_controller.hpp"

using namespace ruac::kernel;

// 创建控制器操作
controller::Operation op;

// 方式一：使用单例策略（Operation 不接管生命周期）
auto &obj_single = object::Single::instance();
op.set_object_strategy(obj_single);

// 方式二：使用多例策略（Operation 接管生命周期）
auto track_multis = std::make_unique<track::Multis>();
op.set_track_strategy(std::move(track_multis));

// 取回变体并通过 std::visit 派发
auto &obj_variant = op.get_object_strategy();
std::visit([](auto &&strategy) {
    using T = std::decay_t<decltype(strategy)>;
    if constexpr (std::is_same_v<T, defname::objs *>) {
        // 单例分支
    } else {
        // 多例分支
    }
}, obj_variant);
```

## 注意事项

- 同一类策略的 Single 重载与 Multis 重载为覆盖关系：后一次 `set*Strategy` 调用会替换变体中已存储的策略形态，包括释放此前持有的 `unique_ptr<Multis>`。
- `get*Strategy` 返回的是变体的可变引用，调用方应避免在引用存续期间让 `Operation` 析构或重新设置策略，以免产生悬垂引用。
- 持有 `Single *` 的变体不会释放单例对象，调用方需自行保证单例的生命周期长于 `Operation` 的使用期。
