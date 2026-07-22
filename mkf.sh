#!/bin/bash
# shellcheck disable=SC2034

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "[EXEC ERROR] The standard safe practice is 'bash ${0} [dirname]'"
    return 1 &>/dev/null
fi

# [*] File   Rule: The code should wrap around 100 columns and force wrap around 120 columns
# [*] Style Guide: RUAC-BASH-STYLE-GUIDE.md
# [*] Author     : ohmycode-cn(https://github.com/ohmycode-cn)
# [*]            : ohmycode-cn(ohcode@163.com)
# [*] Bash Std   : Version 5.0 +
# [*] License    : MIT
# [*] File       : mkf.sh
# [*] Description: File creation script.

source .shared.sh
PATH_INCLUDE="src/cxx/include"
PATH_SRC="src/cxx/src"
CURRENT_AUTHOR="$(cat .current_author.ini)"

function is_empty_param() {
    if [[ "${1}" == "nll" ]]; then
        return 0
    fi
    return 1
}

function is_exist_path() {
    if [[ -d "${1}" ]]; then
        return 0
    fi
    return 1
}

function is_exist_file() {
    if [[ -f "${1}" ]]; then
        return 0
    fi
    return 1
}

PUB_CONTENT=(
    "/**"
    " * Style Guide: RUAC-CCXX-STYLE-GUIDE.md"
    " * File Rule: The code should wrap around 100 columns and force wrap around 120 columns"
    " * Author: ${CURRENT_AUTHOR}"
)

PUB_HEADER_DESCRIPTION=(
    " * Description of header file function declaration"
    " * "
    " */"
)

function init_cxx_file() {
    local cxx_prefix="ruac_"
    local cxx_include="${PATH_INCLUDE}"
    local cxx_src="${PATH_SRC}"
    local fpath="${1}"
    local fname="${2}"
    local cxx_root_namespace="ruac"
    local cxx_namespace

    if is_empty_param "${fpath}"; then
        warning "You not provide path parameter, use default path !"
        cxx_namespace="${cxx_root_namespace}"
    else
        cxx_include="${PATH_INCLUDE}/${fpath}"
        cxx_src="${PATH_SRC}/${fpath}"
        # change xxx/xxx to xxx::xxx
        cxx_namespace="${cxx_root_namespace}::${fpath//\//::}"
    fi

    if ! is_exist_path "${cxx_include}" || ! is_exist_path "${cxx_src}"; then
        error "Path ${cxx_include} or ${cxx_src} not exist."
        return 1
    fi

    local fhpp="${cxx_prefix}${fname}.hpp"
    local fcpp="${cxx_prefix}${fname}.cpp"

    if is_exist_file "${fhpp}" || is_exist_file "${fcpp}"; then
        error "File ${fhpp} or ${fcpp} already exist."
        return 1
    fi

    pub_cxx_paths=(" * include/${fpath}/${fhpp}" " * src/${fpath}/${fcpp}")
    prv_hpp_content=(
        ""
        "#pragma once"
        "#ifndef ${cxx_prefix^^}${fname^^}_HPP"
        "#define ${cxx_prefix^^}${fname^^}_HPP"
        ""
        "namespace ${cxx_namespace}"
        "{"
        ""
        "class REPLACE_ME {public: REPLACE_ME()=default; ~REPLACE_ME()=default;};"
        ""
        "} // namespace ${cxx_namespace}"
        ""
        "#endif  // ${cxx_prefix^^}${fname^^}_HPP"
    )

    prv_cpp_content=(
        "*/"
        ""
        "#include \"${fpath}/${fhpp}\""
        ""
        "namespace ${cxx_namespace}"
        "{"
        "} // namespace ${cxx_namespace}"
    )

    {
        printf "%s\n" "${PUB_CONTENT[@]}"
        printf "%s\n" "${pub_cxx_paths[@]}"
        printf "%s\n" "${PUB_HEADER_DESCRIPTION[@]}"
        printf "%s\n" "${prv_hpp_content[@]}"
    } >"${cxx_include}/${fhpp}"

    {
        printf "%s\n" "${PUB_CONTENT[@]}"
        printf "%s\n" "${pub_cxx_paths[@]}"
        printf "%s\n" "${prv_cpp_content[@]}"
    } >"${cxx_src}/${fcpp}"

    info "Init cxx file !"
}

# Description:
#   This function creates C header (.h) and source (.c) files with header guards.
# Args:
#   $1 - The subdirectory path under include/src (optional).
#   $2 - The file name (without prefix and extension).
# Returns:
#   0 on success, 1 on validation or creation failure.
# Echo:
#   Success or error messages via ok/error functions.
function init_c_file() {
    local c_prefix="ruac_c_"
    local c_include="${PATH_INCLUDE}"
    local c_src="${PATH_SRC}"
    local fpath="${1}"
    local fname="${2}"

    if is_empty_param "${fpath}"; then
        warning "You not provide path parameter, use default path !"
    else
        c_include="${PATH_INCLUDE}/${fpath}"
        c_src="${PATH_SRC}/${fpath}"
    fi

    if ! is_exist_path "${c_include}" || ! is_exist_path "${c_src}"; then
        error "Path ${c_include} or ${c_src} not exist."
        return 1
    fi

    local fh="${c_prefix}${fname}.h"
    local fc="${c_prefix}${fname}.c"

    if is_exist_file "${fh}" || is_exist_file "${fc}"; then
        error "File ${fh} or ${fc} already exist."
        return 1
    fi

    pub_cxx_paths=(" * include/${fpath}/${fh}" " * src/${fpath}/${fc}")
    prv_h_content=(
        ""
        "#ifndef ${c_prefix^^}${fname^^}_H"
        "#define ${c_prefix^^}${fname^^}_H"
        ""
        "#ifdef __cplusplus"
        "extern \"C\" {"
        "#endif"
        ""
        ""
        "#ifdef __cplusplus"
        "}"
        "#endif"
        ""
        "#endif  // ${c_prefix^^}${fname^^}_H"
    )

    prv_c_content=(
        "*/"
        ""
        "#include \"${fpath}/${fh}\""
    )

    printf "%s\n" "${PUB_CONTENT[@]}" >"${c_include}/${fh}"
    {
        printf "%s\n" "${pub_cxx_paths[@]}"
        printf "%s\n" "${PUB_HEADER_DESCRIPTION[@]}"
        printf "%s\n" "${prv_h_content[@]}"
    } >>"${c_include}/${fh}"

    printf "%s\n" "${PUB_CONTENT[@]}" >"${c_src}/${fc}"
    {
        printf "%s\n" "${pub_cxx_paths[@]}"
        printf "%s\n" "${prv_c_content[@]}"
    } >>"${c_src}/${fc}"

    info "Init c file !"
}

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

    info "mode: ${mode}, path: ${path}, file: ${file}"

    if [[ "${path}" == "nll" ]]; then
        warning "Path is not specified, use default path:"
        warning "Source: ${PATH_SRC}"
        warning "Include: ${PATH_INCLUDE}"
    fi

    if [[ "${file}" == "nll" ]]; then
        error "You must provide a file name."
        return 1
    fi

    local ret
    if [[ "${mode}" = "c" ]]; then
        init_c_file "${path}" "${file}"
        ret=${?}
    else
        init_cxx_file "${path}" "${file}"
        ret=${?}
    fi

    return ${ret}
}
main "${@}"
exit 0
