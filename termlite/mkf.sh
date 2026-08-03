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

source ../.shared.sh
PATH_INCLUDE="src"
PATH_SRC="src"
CURRENT_AUTHOR="$(grep -E "ISUSER=" ../.current_author.ini | cut -d'=' -f2)"

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
    local sub_namespace="${3}"
    local cxx_root_namespace="ruac::terminal_lite"
    local cxx_namespace

    if is_empty_param "${fpath}"; then
        warning "You not provide path parameter, use default path !"
        fpath=""
    else
        cxx_include="${PATH_INCLUDE}/${fpath}"
        cxx_src="${PATH_SRC}/${fpath}"
    fi

    if [[ -z "${sub_namespace}" ]]; then
        cxx_namespace="${cxx_root_namespace}"
    else
        cxx_namespace="${cxx_root_namespace}::${sub_namespace}"
    fi

    if ! is_exist_path "${cxx_include}" || ! is_exist_path "${cxx_src}"; then
        error "Path ${cxx_include} or ${cxx_src} not exist."
        return 1
    fi

    local fhpp="${cxx_prefix}${fname}.hpp"
    local fcpp="${cxx_prefix}${fname}.cpp"

    if is_exist_file "${cxx_include}/${fhpp}" || is_exist_file "${cxx_src}/${fcpp}"; then
        error "File ${cxx_include}/${fhpp} or ${cxx_src}/${fcpp} already exist."
        return 1
    fi

    if [[ -z "${fpath}" ]]; then
        pub_cxx_paths=(" * ${fhpp}" " * src/${fcpp}")
        local include_hpp="#include \"${fhpp}\""
    else
        pub_cxx_paths=(" * ${fpath}/${fhpp}" " * src/${fpath}/${fcpp}")
        local include_hpp="#include \"${fpath}/${fhpp}\""
    fi

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
        "${include_hpp}"
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

function main() {
    local namespace="nll"
    local path="nll"
    local file="nll"
    local nosrc=0

    while [[ $# -gt 0 ]]; do
        case "${1}" in
        -n | --namespace)
            namespace="${2}"
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
        --nosrc)
            nosrc=1
            shift
            ;;
        *)
            error "Unknown option: ${1}"
            return 1
            ;;
        esac
    done

    if [[ ${nosrc} -eq 1 ]]; then
        PATH_INCLUDE="."
    fi

    info "namespace: ${namespace}, path: ${path}, file: ${file}, nosrc: ${nosrc}"

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
    if [[ "${namespace}" = "nll" ]]; then
        init_cxx_file "${path}" "${file}"
    else
        init_cxx_file "${path}" "${file}" "${namespace}"
    fi
    ret=${?}

    return ${ret}
}
main "${@}"
exit 0
