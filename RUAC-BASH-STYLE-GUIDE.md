# RUAC Bash Style Guide

This guide applies to all `.sh` scripts in the RUAC project (e.g. `mkd.sh`, `mkf.sh`, `termlite/mkf.sh`, and the shared script `.shared.sh`).
Every rule below is distilled from the project's existing scripts and must be followed when adding or modifying scripts.

## Table of Contents

[Bash File Rules](#bash-file-rules)

[Bash File Header](#bash-file-header)

[Bash Column Width and Indentation](#bash-column-width-and-indentation)

[Bash Comment Rules](#bash-comment-rules)

[Bash Naming Rules](#bash-naming-rules)

[Bash Variables and Constants](#bash-variables-and-constants)

[Bash Strings and Quoting](#bash-strings-and-quoting)

[Bash Function Rules](#bash-function-rules)

[Bash Conditionals](#bash-conditionals)

[Bash Control Flow](#bash-control-flow)

[Bash Argument Parsing](#bash-argument-parsing)

[Bash Array Rules](#bash-array-rules)

[Bash Output and Logging](#bash-output-and-logging)

[Bash Redirection Rules](#bash-redirection-rules)

[Bash Exit and Return](#bash-exit-and-return)

[Bash Shared Resources](#bash-shared-resources)

## Bash File Rules

- Bash script file names must use only lowercase letters, or separate words with underscores. CamelCase is forbidden.
- Bash scripts must use UTF-8 encoding.
- Bash scripts must use LF line endings.
- The first line of a Bash script must be the shebang: `#!/bin/bash`.
- The target interpreter is Bash; `#!/bin/sh` is forbidden. Project scripts rely on Bash 5.0+ features (e.g. `${var^^}`, `${var//a/b}`, `[[ ]]`, arrays).
- Shared resource scripts are named `.shared.sh` and stored as a hidden file in the same or parent directory of the scripts that use it.

```bash
# Valid file names
mkd.sh
mkf.sh
.shared.sh

# Invalid file names
Mkd.sh
mkfScript.sh
```

## Bash File Header

- After the shebang, shellcheck directives may be added as needed, e.g. `# shellcheck disable=SC2034`.
- Executable scripts must include a "source-load guard" near the top to prevent execution via `source`:

```bash
if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "[EXEC ERROR] The standard safe practice is 'bash ${0} [dirname]'"
    return 1 &>/dev/null
fi
```

- It must be followed by the standard `# [*]` header block, with fixed field order and wording:

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

- The `File` field must match the actual file name; the `Description` field must briefly state the script's responsibility in English.
- Pure shared resource scripts (e.g. `.shared.sh`) do not need the source-load guard, but must still keep the `# [*]` header block.

## Bash Column Width and Indentation

- Code should wrap at 100 columns and must wrap at 120 columns.
- Indentation uses 4 spaces; tabs are forbidden.
- Continuation lines should remain readable and may wrap at a logical operator or argument separator.

## Bash Comment Rules

- Comments are written in English and must stay consistent with the actual code.
- Function comments must use the fixed four-section structure (`Description` / `Args` / `Returns` / `Echo`):

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

- Section comments use `# Highlight:` or a short inline English comment to mark a group, e.g. for color constants:

```bash
# Highlight: reset
readonly RESET='\033[0m'

# Highlight: black ~ white
readonly BLACK='\033[30m'   # Black
```

- Inline comments are separated from code by one space; right-aligned comments within a group should stay aligned.

## Bash Naming Rules

- Function names must use only lowercase letters, or separate words with underscores. CamelCase is forbidden, as is any prefix or suffix.
- Global variables and constants must use only uppercase letters separated by underscores (UPPER_SNAKE_CASE).
- Local variables must use only lowercase letters separated by underscores (lower_snake_CASE).
- Boolean predicate functions should be prefixed with `is_`, e.g. `is_empty_param`, `is_exist_path`.

```bash
# Valid function names
function init_cxx_file() { ... }
function is_exist_file() { ... }

# Invalid function names
function InitCxxFile() { ... }
function _init_cxx_file() { ... }

# Valid global variables / constants
PATH_INCLUDE="src/cxx/include"
readonly RESET='\033[0m'

# Valid local variables
local fpath="${1}"
local cxx_namespace="ruac"
```

## Bash Variables and Constants

- Constants must be declared with `readonly`. When a value must be computed before being frozen, a two-step declaration is allowed (e.g. `ONCE_TIME=$(date ...)` followed by `readonly ONCE_TIME`).
- Global variables are declared at the top level of the script; variables inside a function must be declared with `local` to avoid polluting the global scope.
- When a command substitution result must be preserved, accept it into a `local` first, then apply `readonly`.
- When a function's return code must be consumed by the caller, do not swallow it with `local x=$(fn)`; capture the exit code explicitly:

```bash
init_c_file "${path}" "${file}"
ret=${?}
```

```bash
# Valid constant declaration
readonly BLACK='\033[30m'   # Black
ONCE_TIME=$(date '+%Y-%m-%d-%H-%M-%S')
readonly ONCE_TIME

# Valid local variable declaration
function init_cxx_file() {
    local fpath="${1}"
    local fname="${2}"
    local cxx_namespace
    ...
}

# Invalid: no local, pollutes the global scope
function init_cxx_file() {
    fpath="${1}"
    fname="${2}"
}
```

## Bash Strings and Quoting

- Every variable expansion must use braces: `${var}`; `$var` is forbidden.
- Every variable expansion and command substitution must be wrapped in double quotes to prevent word splitting and glob expansion.
- Command substitution must use `"$(...)"`; backticks are forbidden.
- Constants holding escape sequences (e.g. colors) are defined with single quotes and interpreted at output time via `echo -e` or `printf`.

```bash
# Valid quoting
local include="src/cxx/include/${dirname}"
if [[ -z "${dirname}" ]]; then ...
CURRENT_AUTHOR="$(grep -E "ISUSER=" .current_author.ini | cut -d'=' -f2)"

# Invalid quoting
local include="src/cxx/include/$dirname"
if [[ -z $dirname ]]; then ...
CURRENT_AUTHOR=`grep -E "ISUSER=" .current_author.ini`
```

## Bash Function Rules

- Functions must be defined with the `function` keyword plus parentheses: `function name() { ... }`.
- The function body is indented 4 spaces; `{` stays on the same line as the signature, `}` stands alone on its own line.
- Every function must carry the four-section comment (see [Bash Comment Rules](#bash-comment-rules)).
- Functions express success/failure via the return code: `return 0` for success, `return 1` for failure.
- Boolean predicate functions return `0` (true) / `1` (false) and are called directly in conditions: `if is_exist_path "${x}"; then`.

```bash
# Valid function definition
function is_exist_file() {
    if [[ -f "${1}" ]]; then
        return 0
    fi
    return 1
}

# Invalid: missing function keyword
is_exist_file() {
    ...
}
```

## Bash Conditionals

- Conditionals must use `[[ ]]`; `[ ]` and `test` are forbidden.
- Empty-string checks use `[[ -z "${var}" ]]`; non-empty checks use `[[ -n "${var}" ]]`; equality uses `[[ "${a}" == "${b}" ]]`.
- File checks use `[[ -d "${path}" ]]` (directory) and `[[ -f "${path}" ]]` (regular file).
- Numeric comparisons use `[[ ${a} -eq ${b} ]]`, `-ne`, `-gt`, `-lt`, etc.; quoting is optional but recommended for consistency.
- Command-result checks use the `if ! cmd; then` form.

```bash
# Valid conditionals
if [[ -z "${dirname}" ]]; then ...
if [[ -d "${include}" ]]; then ...
if [[ ${SPLOCK} -eq 1 ]]; then ...
if ! mkdir -p "${include}"; then ...
if is_exist_file "${cxx_include}/${fhpp}" || ! is_exist_path "${cxx_src}"; then ...

# Invalid conditionals
if [ -z "${dirname}" ]; then ...
if [ "$dirname" = "" ]; then ...
```

## Bash Control Flow

- In `if`/`then`/`fi`, `then` must be on the same line as `if`; `fi` stands alone.
- `else` stands alone; `elif` shares its line with `then`.
- In `case`/`esac`, each branch pattern is separated from `)` by one space; multiple patterns are merged with `|`; each branch ends with `;;`.
- `while`/`for` loops are indented 4 spaces; `do` stays on the same line as `while`/`for`.

```bash
# Valid if/else
if [[ -z "${fpath}" ]]; then
    pub_cxx_paths=(" * include/${fhpp}" " * src/${fcpp}")
else
    pub_cxx_paths=(" * include/${fpath}/${fhpp}" " * src/${fpath}/${fcpp}")
fi

# Valid case
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

# Valid while
while [[ $# -gt 0 ]]; do
    ...
done

# Valid for
for itme in "${sparray[@]}"; do
    printf "\r%s %s" "${itme}" "${message}"
    sleep 0.1
done
```

## Bash Argument Parsing

- Command-line arguments must be parsed with the `while [[ $# -gt 0 ]]; do case ... esac done` pattern.
- Every option provides both a short and a long form, merged with `|`: `-m | --mode)`.
- Value-taking options use `shift 2`; boolean flag options use `shift`.
- Unrecognized options must fall into the `*)` branch, call `error`, and `return 1`.
- Optional positional parameters use the literal `"nll"` as the "not provided" sentinel, rather than the empty string, to distinguish "explicitly omitted" from "empty input".

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

## Bash Array Rules

- Arrays are declared with parentheses, each element double-quoted: `arr=( "a" "b" )`.
- Accessing all elements must use `"${arr[@]}"`; `${arr[*]}` and unquoted `${arr[@]}` are forbidden.
- Prefer `printf "%s\n" "${arr[@]}"` over a loop of `echo` when outputting an array.
- When multiple array segments are written to the same file, use a `{ ... } >file` block redirect to merge the writes and reduce IO.

```bash
# Valid array declaration
PUB_CONTENT=(
    "/**"
    " * Style Guide: RUAC-CCXX-STYLE-GUIDE.md"
    " * Author: ${CURRENT_AUTHOR}"
)

# Valid array traversal
for itme in "${sparray[@]}"; do
    ...
done

# Valid merged array write
{
    printf "%s\n" "${PUB_CONTENT[@]}"
    printf "%s\n" "${pub_cxx_paths[@]}"
    printf "%s\n" "${prv_hpp_content[@]}"
} >"${cxx_include}/${fhpp}"

# Invalid
for itme in ${sparray[@]}; do ... done          # unquoted
for itme in "${sparray[*]}"; do ... done        # wrong use of *
```

## Bash Output and Logging

- Logging must go through the unified functions provided by `.shared.sh`: `info`, `ok`, `warning`, `error`. Business scripts must not `echo` ordinary messages directly.
- Use `echo -e` when escape sequences (e.g. colors) must be interpreted; use `printf` for arrays or when format control is needed.
- The timestamp format is fixed as `YYYY-MM-DD-HH-MM-SS@3N` (milliseconds), produced by the `now()` function.
- Color constants are defined centrally in `.shared.sh`; business scripts must not define their own color escape sequences.
- `error` is used for failure scenarios and is usually followed by `return 1`; `warning` is for non-fatal, continuable notices; `ok` for success; `info` for progress information.

```bash
# Valid logging
error "Dirname is empty"
return 1

warning "Path is not specified, use default path:"
ok "Create directory ${include} and ${src} success"
info "mode: ${mode}, path: ${path}, file: ${file}"

# Invalid: direct echo for business messages
echo "create directory success"
```

## Bash Redirection Rules

- Discard all output with `&>/dev/null`; discard only stderr with `2>/dev/null`.
- File writes use `>"${file}"` (overwrite) or `>>"${file}"` (append); no space between the operator and the file name, and the file name must be quoted.
- When multiple commands write to the same file, use a `{ ... } >file` or `{ ... } >>file` block redirect.
- When coordinating a background process with `kill`/`wait`, stderr must be redirected to `/dev/null` to avoid polluting output on termination.

```bash
# Valid redirection
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

# Invalid
> "${file}"            # extra space after the operator
>${file}               # file name not quoted
```

## Bash Exit and Return

- An executable script must call its entry function at the end and then `exit`: `main "${@}"` followed by `exit 0`.
- Exit code semantics: `0` for business success; business failure is expressed via `return` inside `main`, and the outer layer always exits with `exit 0` (failure information has already been emitted via `error`).
- `exit` is forbidden inside functions; use `return` to leave a function so the whole script is not terminated early.
- When consuming a sub-call's exit code, capture it into a dedicated variable: `cmd; ret=${?}`; do not silently drop it with `local x=$(cmd)`.

```bash
# Valid script ending
main "${@}"
exit 0

# Valid exit-code capture
local ret
if [[ "${mode}" = "c" ]]; then
    init_c_file "${path}" "${file}"
    ret=${?}
else
    init_cxx_file "${path}" "${file}"
    ret=${?}
fi
return ${ret}

# Invalid: exit inside a function
function main() {
    if [[ -z "${1}" ]]; then
        exit 1
    fi
}
```

## Bash Shared Resources

- Common capabilities (logging, colors, timestamp, spinner) must be centralized in `.shared.sh` and imported by business scripts via `source`.
- The `source` path is relative to the current script: root-directory scripts use `source .shared.sh`; sub-directory scripts use `source ../.shared.sh`.
- The standard public interface of `.shared.sh`: `now`, `info`, `ok`, `warning`, `error`, `enable_spinner`, `cancel_spinner`, plus the color constants (`RESET`/`BLACK`..`WHITE`, etc.).
- Business scripts must not reimplement capabilities already in `.shared.sh`; new general capabilities should be consolidated into `.shared.sh`.
- The spinner is optional: call `enable_spinner "msg"` before use and must call `cancel_spinner` afterwards to restore the cursor.

```bash
# Valid import (root-directory script)
source .shared.sh

# Valid import (sub-directory script)
source ../.shared.sh

# Valid use of shared capabilities
info "Init cxx file !"
error "Path ${cxx_include} or ${cxx_src} not exist."
```
