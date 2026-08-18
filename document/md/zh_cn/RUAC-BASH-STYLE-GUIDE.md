# RUAC Bash 脚本规范

本规范适用于 RUAC 项目中所有 `.sh` 脚本（如 `mkd.sh`、`mkf.sh`、`termlite/mkf.sh` 以及共享脚本 `.shared.sh`）。
所有规范均从项目现有脚本中提炼，新增或修改脚本时必须遵循。

## 目录导航

[Bash 文件规范](#Bash文件规范)

[Bash 文件头规范](#Bash文件头规范)

[Bash 列宽与缩进](#Bash列宽与缩进)

[Bash 注释规范](#Bash注释规范)

[Bash 命名规范](#Bash命名规范)

[Bash 变量与常量](#Bash变量与常量)

[Bash 字符串与引用](#Bash字符串与引用)

[Bash 函数规范](#Bash函数规范)

[Bash 条件判断](#Bash条件判断)

[Bash 控制流](#Bash控制流)

[Bash 参数解析](#Bash参数解析)

[Bash 数组规范](#Bash数组规范)

[Bash 输出与日志](#Bash输出与日志)

[Bash 重定向规范](#Bash重定向规范)

[Bash 退出与返回](#Bash退出与返回)

[Bash 共享资源](#Bash共享资源)

## Bash文件规范

- Bash 脚本文件名称必须全部使用小写字母，或者使用下划线分隔单词。禁止使用驼峰命名法。
- Bash 脚本必须使用 UTF-8 编码。
- Bash 脚本必须使用 LF 换行符。
- Bash 脚本第一行必须是 shebang：`#!/bin/bash`。
- Bash 脚本目标解释器为 Bash，禁止使用 `#!/bin/sh`。项目脚本依赖 Bash 5.0+ 特性（如 `${var^^}`、`${var//a/b}`、`[[ ]]`、数组）。
- 共享资源脚本以 `.shared.sh` 命名，并以隐藏文件形式存放于脚本同级或上级目录。

```bash
# 合法文件名
mkd.sh
mkf.sh
.shared.sh

# 非合法文件名
Mkd.sh
mkfScript.sh
```

## Bash文件头规范

- shebang 之后可按需添加 shellcheck 指令，例如 `# shellcheck disable=SC2034`。
- 可执行脚本必须在文件头加入“源载入保护块”，防止被 `source` 执行：

```bash
if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "[EXEC ERROR] The standard safe practice is 'bash ${0} [dirname]'"
    return 1 &>/dev/null
fi
```

- 其后必须包含以 `# [*]` 开头的标准文件头块，字段顺序与写法固定：

```bash
# [*] File   Rule: The code should wrap around 100 columns and force wrap around 120 columns
# [*] Style Guide: RUAC-BASH-STYLE-GUIDE.md
# [*] Author     : ohmycode-cn(https://github.com/ohmycode-cn)
# [*]            : ohmycode-cn(ohcode@163.com)
# [*] Bash Std   : Version 5.0 +
# [*] License    : MIT
# [*] File       : mkf.sh
# [*] Description: File creation script.
```

- `File` 字段必须与实际文件名一致；`Description` 字段必须用英文简述当前脚本职责。
- 纯共享资源脚本（如 `.shared.sh`）无需源载入保护块，但仍需保留 `# [*]` 文件头块。

## Bash列宽与缩进

- 代码应在 100 列处折行，在 120 列处强制折行。
- 缩进统一使用 4 个空格，禁止使用 Tab。
- 续行应保持可读性，可在逻辑运算符或参数分隔处折行。

## Bash注释规范

- 注释语言使用英语；注释内容必须与实际代码保持一致。
- 函数注释必须使用固定四段式结构（`Description` / `Args` / `Returns` / `Echo`）：

```bash
# Description:
#   This function creates include and src directories for a given module name.
# Args:
#   $1 - The directory/module name to create under src/cxx/include and src/cxx/src.
# Returns:
#   0 on success, 1 on validation or creation failure.
# Echo:
#   Success or error messages via ok/error functions.
function main() {
    ...
}
```

- 区段注释使用 `# Highlight:` 或简短英文行内注释标记分组，例如颜色常量分组：

```bash
# Highlight: reset
readonly RESET='\033[0m'

# Highlight: black ~ white
readonly BLACK='\033[30m'   # Black
```

- 行内注释与代码之间以一个空格分隔；右端对齐注释需保持同组对齐。

## Bash命名规范

- 函数名称必须全部使用小写字母，或使用下划线分隔单词。禁止使用驼峰命名法，禁止使用任何前缀或后缀。
- 全局变量与常量必须全部使用大写字母，并使用下划线分隔单词（UPPER_SNAKE_CASE）。
- 局部变量必须全部使用小写字母，并使用下划线分隔单词（lower_snake_case）。
- 布尔型判断函数建议以 `is_` 开头，例如 `is_empty_param`、`is_exist_path`。

```bash
# 合法函数名称
function init_cxx_file() { ... }
function is_exist_file() { ... }

# 非合法函数名称
function InitCxxFile() { ... }
function _init_cxx_file() { ... }

# 合法全局变量 / 常量
PATH_INCLUDE="src/cxx/include"
readonly RESET='\033[0m'

# 合法局部变量
local fpath="${1}"
local cxx_namespace="ruac"
```

## Bash变量与常量

- 常量必须使用 `readonly` 声明。先求值再 `readonly` 的场景允许分两步声明（如 `ONCE_TIME=$(date ...)` 后 `readonly ONCE_TIME`）。
- 全局变量在脚本顶层声明；函数内部变量必须使用 `local` 声明，避免污染全局作用域。
- 对需要保留原值的命令替换结果，使用 `local` 单独承接后再 `readonly`。
- 当函数返回值需要被调用方使用时，禁止直接用 `local x=$(fn)` 吞掉返回码，应显式承接退出码：

```bash
init_c_file "${path}" "${file}"
ret=${?}
```

```bash
# 合法常量声明
readonly BLACK='\033[30m'   # Black
ONCE_TIME=$(date '+%Y-%m-%d-%H-%M-%S')
readonly ONCE_TIME

# 合法局部变量声明
function init_cxx_file() {
    local fpath="${1}"
    local fname="${2}"
    local cxx_namespace
    ...
}

# 非合法写法：未使用 local，污染全局作用域
function init_cxx_file() {
    fpath="${1}"
    fname="${2}"
}
```

## Bash字符串与引用

- 所有变量展开必须使用花括号：`${var}`，禁止使用 `$var`。
- 所有变量展开与命令替换必须使用双引号包裹，防止词分割与通配展开。
- 命令替换必须使用 `"$(...)"`，禁止使用反引号。
- 颜色等含转义序列的字符串使用单引号定义常量，输出时通过 `echo -e` 或 `printf` 解释。

```bash
# 合法引用
local include="src/cxx/include/${dirname}"
if [[ -z "${dirname}" ]]; then ...
CURRENT_AUTHOR="$(grep -E "ISUSER=" .current_author.ini | cut -d'=' -f2)"

# 非合法引用
local include="src/cxx/include/$dirname"
if [[ -z $dirname ]]; then ...
CURRENT_AUTHOR=`grep -E "ISUSER=" .current_author.ini`
```

## Bash函数规范

- 函数定义必须使用 `function` 关键字加括号的形式：`function name() { ... }`。
- 函数体使用 4 空格缩进，`{` 与函数签名同行，`}` 单独成行。
- 函数必须配套四段式注释（见[Bash注释规范](#Bash注释规范)）。
- 函数通过返回码表达成功/失败：`return 0` 表示成功，`return 1` 表示失败。
- 布尔型判断函数返回 `0`（真）/`1`（假），并在条件中直接调用：`if is_exist_path "${x}"; then`。

```bash
# 合法函数定义
function is_exist_file() {
    if [[ -f "${1}" ]]; then
        return 0
    fi
    return 1
}

# 非合法函数定义：缺少 function 关键字
is_exist_file() {
    ...
}
```

## Bash条件判断

- 条件判断必须使用 `[[ ]]`，禁止使用 `[ ]` 或 `test`。
- 字符串判空使用 `[[ -z "${var}" ]]`，非空使用 `[[ -n "${var}" ]]`，相等使用 `[[ "${a}" == "${b}" ]]`。
- 文件判断使用 `[[ -d "${path}" ]]`（目录）、`[[ -f "${path}" ]]`（普通文件）。
- 数值比较使用 `[[ ${a} -eq ${b} ]]`、`-ne`、`-gt`、`-lt` 等；变量两端可不加引号，但建议加引号以保持一致性。
- 命令执行结果判断使用 `if ! cmd; then` 形式。

```bash
# 合法条件判断
if [[ -z "${dirname}" ]]; then ...
if [[ -d "${include}" ]]; then ...
if [[ ${SPLOCK} -eq 1 ]]; then ...
if ! mkdir -p "${include}"; then ...
if is_exist_file "${cxx_include}/${fhpp}" || ! is_exist_path "${cxx_src}"; then ...

# 非合法条件判断
if [ -z "${dirname}" ]; then ...
if [ "$dirname" = "" ]; then ...
```

## Bash控制流

- `if`/`then`/`fi` 中 `then` 必须与 `if` 同行，`fi` 单独成行。
- `else` 单独成行，`elif` 与 `then` 同行。
- `case`/`esac` 中每个分支的模式与 `)` 之间留一个空格；多模式使用 `|` 合并；分支以 `;;` 结束。
- `while`/`for` 循环体同样使用 4 空格缩进，`do` 与 `while`/`for` 同行。

```bash
# 合法 if/else
if [[ -z "${fpath}" ]]; then
    pub_cxx_paths=(" * include/${fhpp}" " * src/${fcpp}")
else
    pub_cxx_paths=(" * include/${fpath}/${fhpp}" " * src/${fpath}/${fcpp}")
fi

# 合法 case
case "${1}" in
-m | --mode)
    mode="${2}"
    shift 2
    ;;
--nosrc)
    nosrc=1
    shift
    ;;
*)
    error "Unknown option: ${1}"
    return 1
    ;;
esac

# 合法 while
while [[ $# -gt 0 ]]; do
    ...
done

# 合法 for
for itme in "${sparray[@]}"; do
    printf "\r%s %s" "${itme}" "${message}"
    sleep 0.1
done
```

## Bash参数解析

- 命令行参数必须使用 `while [[ $# -gt 0 ]]; do case ... esac done` 模式解析。
- 每个选项同时提供短选项与长选项，使用 `|` 合并：`-m | --mode)`。
- 带值选项使用 `shift 2`，布尔标志选项使用 `shift`。
- 未识别选项必须进入 `*)` 分支并调用 `error` 报错后 `return 1`。
- 可选位置参数约定使用字面量 `"nll"` 作为“未提供”哨兵值，而非空字符串，以便区分“显式省略”与“空输入”。

```bash
function main() {
    local mode="cxx"
    local path="nll"
    local file="nll"

    while [[ $# -gt 0 ]]; do
        case "${1}" in
        -m | --mode)
            mode="${2}"
            shift 2
            ;;
        -p | --path)
            path="${2}"
            shift 2
            ;;
        -f | --file)
            file="${2}"
            shift 2
            ;;
        *)
            error "Unknown option: ${1}"
            return 1
            ;;
        esac
    done
    ...
}
```

## Bash数组规范

- 数组声明使用圆括号，每个元素以双引号包裹：`arr=( "a" "b" )`。
- 访问数组所有元素必须使用 `"${arr[@]}"`，禁止使用 `${arr[*]}` 或不加引号的 `${arr[@]}`。
- 输出数组优先使用 `printf "%s\n" "${arr[@]}"`，而非循环 `echo`。
- 多段数组写入同一文件时，使用 `{ ... } >file` 块重定向合并写入，减少 IO 次数。

```bash
# 合法数组声明
PUB_CONTENT=(
    "/**"
    " * Style Guide: RUAC-CCXX-STYLE-GUIDE.md"
    " * Author: ${CURRENT_AUTHOR}"
)

# 合法数组遍历
for itme in "${sparray[@]}"; do
    ...
done

# 合法数组合并写入
{
    printf "%s\n" "${PUB_CONTENT[@]}"
    printf "%s\n" "${pub_cxx_paths[@]}"
    printf "%s\n" "${prv_hpp_content[@]}"
} >"${cxx_include}/${fhpp}"

# 非合法写法
for itme in ${sparray[@]}; do ... done          # 未加引号
for itme in "${sparray[*]}"; do ... done        # 错误使用 *
```

## Bash输出与日志

- 日志输出必须通过 `.shared.sh` 提供的统一函数：`info`、`ok`、`warning`、`error`，禁止在业务脚本中直接 `echo` 普通信息。
- 需要解释转义序列（如颜色）时使用 `echo -e`；输出数组或需要格式控制时使用 `printf`。
- 时间戳格式统一为 `YYYY-MM-DD-HH-MM-SS@3N`（毫秒），由 `now()` 函数生成。
- 颜色常量统一由 `.shared.sh` 定义，业务脚本不得自行定义颜色转义序列。
- `error` 用于失败场景并通常伴随 `return 1`；`warning` 用于可继续的非致命提示；`ok` 用于成功；`info` 用于过程性信息。

```bash
# 合法日志
error "Dirname is empty"
return 1

warning "Path is not specified, use default path:"
ok "Create directory ${include} and ${src} success"
info "mode: ${mode}, path: ${path}, file: ${file}"

# 非合法写法：直接 echo 业务信息
echo "create directory success"
```

## Bash重定向规范

- 丢弃全部输出使用 `&>/dev/null`；仅丢弃标准错误使用 `2>/dev/null`。
- 文件写入使用 `>"${file}"`（覆盖）或 `>>"${file}"`（追加），重定向符与文件名之间不留空格，文件名必须加引号。
- 多条命令写入同一文件时，使用 `{ ... } >file` 或 `{ ... } >>file` 块重定向。
- 后台进程与 `kill`/`wait` 配合时，必须将标准错误重定向到 `/dev/null`，避免终止时污染输出。

```bash
# 合法重定向
return 1 &>/dev/null
kill ${SPPID} 2>/dev/null
wait ${SPPID} 2>/dev/null

{
    printf "%s\n" "${PUB_CONTENT[@]}"
} >"${cxx_include}/${fhpp}"

printf "%s\n" "${PUB_CONTENT[@]}" >"${c_include}/${fh}"
{
    printf "%s\n" "${pub_cxx_paths[@]}"
    printf "%s\n" "${prv_h_content[@]}"
} >>"${c_include}/${fh}"

# 非合法写法
> "${file}"            # 重定向符后多了空格
>${file}               # 文件名未加引号
```

## Bash退出与返回

- 可执行脚本必须在末尾调用入口函数并 `exit`：`main "${@}"` 随后 `exit 0`。
- 脚本退出码语义：业务成功为 `0`；业务失败由 `main` 内部 `return` 表达，外层统一以 `exit 0` 退出（失败信息已通过 `error` 输出）。
- 函数内部禁止使用 `exit`，必须使用 `return` 退出函数，避免提前终止整个脚本。
- 需要承接子调用退出码时，使用独立变量承接：`cmd; ret=${?}`，禁止 `local x=$(cmd)` 隐式丢弃退出码。

```bash
# 合法脚本结尾
main "${@}"
exit 0

# 合法退出码承接
local ret
if [[ "${mode}" = "c" ]]; then
    init_c_file "${path}" "${file}"
    ret=${?}
else
    init_cxx_file "${path}" "${file}"
    ret=${?}
fi
return ${ret}

# 非合法写法：函数内直接 exit
function main() {
    if [[ -z "${1}" ]]; then
        exit 1
    fi
}
```

## Bash共享资源

- 公共能力（日志、颜色、时间戳、spinner）必须集中存放于 `.shared.sh`，业务脚本通过 `source` 引入。
- `source` 路径相对于当前脚本位置：根目录脚本使用 `source .shared.sh`，子目录脚本使用 `source ../.shared.sh`。
- `.shared.sh` 提供的标准对外接口：`now`、`info`、`ok`、`warning`、`error`、`enable_spinner`、`cancel_spinner`，以及颜色常量（`RESET`/`BLACK`..`WHITE` 等）。
- 业务脚本不得重复实现 `.shared.sh` 已有能力；新增通用能力应统一沉淀到 `.shared.sh`。
- spinner 为可选能力，使用前调用 `enable_spinner "msg"`，结束后必须调用 `cancel_spinner` 恢复光标。

```bash
# 合法引入（根目录脚本）
source .shared.sh

# 合法引入（子目录脚本）
source ../.shared.sh

# 合法使用共享能力
info "Init cxx file !"
error "Path ${cxx_include} or ${cxx_src} not exist."
```
