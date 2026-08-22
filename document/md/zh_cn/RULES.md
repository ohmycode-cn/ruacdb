# 规则

> 生效日期：2026-08-22 12:49

## Google 测试框架

- 仅仓库管理员有权拉取 / 更新内嵌的 Google Test 框架（`src/cxx/include/google_test/api/googletest/`）。
- 贡献者未经管理员批准，不得修改、重新引入或重新拉取 Google Test 源码目录。

> 生效日期：2026-08-23 14:28

## mk-compile-ruacdb.sh

- Windows 平台目前不支持使用脚本 `mk-compile-ruacdb.sh` 编译生产级二进制文件，需要手动执行编译。

```shell
cmake -B build -DUNIT_TEST=OFF
cmake --build build/ -j<N>
```
 - `-j<N>`：将 `<N>` 替换为适合当前设备的并行编译任务数（例如 9 核及以上机器使用 `-j9`）。请勿省略该数值——不带数字的 `-j` 会让构建系统使用无限制并行，在低核心设备上可能导致内存耗尽。
