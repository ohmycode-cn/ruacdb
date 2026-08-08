# kernel 模块 API - Core Data（核心数据结构）

## 模块概述

`data` 命名空间归属于 `ruac::kernel::core`，定义了 RUAC 数据库系统的核心数据结构。该模块采用纯头文件（header-only）结构体形式实现，源文件 `ruac_data.cpp` 为空实现，所有定义均位于头文件中。

核心数据结构按层级组织，自底向上依次为：

```
Database
  └── Table
        ├── Field（字段定义 / 列模式）
        └── Row（行数据）
              └── rval（变体值，单个单元格）
```

- `Field` 描述表中的一列定义（名称、类型、版本、标识）。
- `Row` 描述表中一行数据，以 `rval` 变体向量存储各列的值。
- `Table` 描述一张表，包含字段集合与行数据集合。
- `Database` 为顶层容器，持有一组表的集合。

所有结构体均内置 `version`（版本）与 `id`（唯一标识）字段，以支持模式版本控制与标识追踪。

## 命名空间与头文件

- 命名空间：`ruac::kernel::core::data`
- 头文件：`include/kernel/core/ruac_data.hpp`
- 源文件：`src/kernel/core/ruac_data.cpp`（空实现，header-only）

### 依赖头文件

| 头文件                              | 提供内容                                   |
|-------------------------------------|--------------------------------------------|
| `include/kernel/core/ruac_type.hpp` | `type::rtype` 枚举，运行时类型标识         |
| `include/kernel/core/ruac_vals.hpp` | `vals::rval` 变体别名，多态值存储          |
| `<vector>`                          | `std::vector`，用于集合字段                |

## 关联类型

### type::rtype

定义于 `ruac::kernel::core::type` 命名空间，为 `enum class`，用于标识 `vals::rval` 变体中当前持有的数据类型。支持的全部枚举值如下：

| 枚举值       | 说明                         |
|--------------|------------------------------|
| `NONE`       | 空状态                       |
| `INT64U`     | 无符号 64 位整数             |
| `INT32U`     | 无符号 32 位整数             |
| `INT16U`     | 无符号 16 位整数             |
| `INT8U`      | 无符号 8 位整数              |
| `INT64`      | 有符号 64 位整数             |
| `INT32`      | 有符号 32 位整数             |
| `INT16`      | 有符号 16 位整数             |
| `INT8`       | 有符号 8 位整数              |
| `DOUBLE`     | 64 位浮点数                  |
| `FLOAT`      | 32 位浮点数                  |
| `CHAR32`     | UTF-32 字符                  |
| `CHAR16`     | UTF-16 字符                  |
| `CHAR8`      | UTF-8 字符                   |
| `CHAR`       | ASCII 字符                   |
| `STRING`     | `std::string`                |
| `ERROR_TYPE` | 错误类型                     |

### vals::rval

定义于 `ruac::kernel::core::vals` 命名空间，是 `std::variant` 的类型别名，用于多态值存储。可持有以下任一类型：

```cpp
using rval = std::variant<std::monostate, // null
                          std::uint64_t,  // uint64
                          std::uint32_t,  // uint32
                          std::uint16_t,  // uint16
                          std::uint8_t,   // uint8
                          std::int64_t,   // int64
                          std::int32_t,   // int32
                          std::int16_t,   // int16
                          std::int8_t,    // int8
                          double,         // float64
                          float,          // float32
                          char32_t,       // char32
                          char16_t,       // char16
                          char8_t,        // char8
                          char,           // char
                          std::string>;   // string
```

`std::monostate` 作为第一个备选类型，使变体默认构造时处于空状态。

## 数据结构定义

### Field

```cpp
struct Field {
    std::string name;                     // field name
    ruac::kernel::core::type::rtype type; // data type
    unsigned long long version;           // schema version
    unsigned long long id;                // unique field identifier
};
```

表模式中的单个字段（列）定义，包含字段名称、数据类型及版本与标识信息。

**成员**

| 成员       | 类型                                  | 说明                 |
|------------|---------------------------------------|----------------------|
| `name`     | `std::string`                         | 字段名称。           |
| `type`     | `ruac::kernel::core::type::rtype`     | 字段数据类型。       |
| `version`  | `unsigned long long`                  | 模式版本号。         |
| `id`       | `unsigned long long`                  | 字段唯一标识符。     |

---

### Row

```cpp
struct Row {
    std::vector<ruac::kernel::core::vals::rval> value; // column values
    unsigned long long version;                        // data version
    unsigned long long id;                             // unique row identifier
};
```

行数据容器，以 `rval` 变体向量存储一行中各列的值，并附带版本与标识元数据。

**成员**

| 成员       | 类型                                          | 说明                           |
|------------|-----------------------------------------------|--------------------------------|
| `value`    | `std::vector<ruac::kernel::core::vals::rval>` | 各列的值，按字段顺序排列。     |
| `version`  | `unsigned long long`                          | 数据版本号。                   |
| `id`       | `unsigned long long`                          | 行唯一标识符。                 |

---

### Table

```cpp
struct Table {
    std::string name;           // table name
    std::vector<Field> fields;  // field collection
    std::vector<Row> rows;      // row data
    unsigned long long version; // schema version
    unsigned long long id;      // unique table identifier
};
```

表结构，包含表名、字段定义集合、行数据集合及版本与标识信息。

**成员**

| 成员       | 类型                       | 说明                       |
|------------|----------------------------|----------------------------|
| `name`     | `std::string`              | 表名称。                   |
| `fields`   | `std::vector<Field>`       | 字段（列）定义集合。       |
| `rows`     | `std::vector<Row>`         | 行数据集合。               |
| `version`  | `unsigned long long`       | 模式版本号。               |
| `id`       | `unsigned long long`       | 表唯一标识符。             |

---

### Database

```cpp
struct Database {
    std::string name;           // database name
    std::vector<Table> table;   // table collection
    unsigned long long version; // schema version
    unsigned long long id;      // unique database identifier
};
```

顶层容器，表示一个数据库，包含数据库名称、表集合及版本与标识信息。

**成员**

| 成员       | 类型                       | 说明                 |
|------------|----------------------------|----------------------|
| `name`     | `std::string`              | 数据库名称。         |
| `table`    | `std::vector<Table>`       | 表集合。             |
| `version`  | `unsigned long long`       | 模式版本号。         |
| `id`       | `unsigned long long`       | 数据库唯一标识符。   |

## 使用示例

```cpp
#include "kernel/core/ruac_data.hpp"

using namespace ruac::kernel::core;

// 构造字段定义
data::Field field;
field.name = "id";
field.type = type::rtype::INT64U;
field.version = 1;
field.id = 1;

// 构造行数据
data::Row row;
row.value.emplace_back(std::uint64_t{1001});
row.version = 1;
row.id = 1;

// 构造表
data::Table table;
table.name = "users";
table.fields.push_back(field);
table.rows.push_back(row);
table.version = 1;
table.id = 1;

// 构造数据库
data::Database db;
db.name = "ruacdb";
db.table.push_back(table);
db.version = 1;
db.id = 1;

// 访问变体值
auto &cell = db.table[0].rows[0].value[0];
if (std::holds_alternative<std::uint64_t>(cell)) {
    std::uint64_t v = std::get<std::uint64_t>(cell);
    (void)v;
}
```

## 注意事项

- 本模块为 header-only 结构体集合，`ruac_data.cpp` 为空实现，无独立成员函数，所有字段均为公开成员，可直接读写。
- `Field.type` 与 `Row.value` 中实际持有的变体类型应保持一致：即 `Field.type` 所指示的 `rtype` 应对应 `rval` 变体中当前活动的值类型，一致性需由调用方在写入数据时自行保证。
- `version` 与 `id` 字段均为 `unsigned long long`，其语义由调用方约定：`version` 用于模式/数据版本控制，`id` 用于全局唯一标识。
- 由于结构体间通过 `std::vector` 直接持有子结构（值语义），拷贝开销与数据规模成正比，传递大型 `Database`/`Table` 时建议使用引用或移动语义。
