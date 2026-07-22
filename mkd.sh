#!/bin/bash
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
# [*] File       : mkd.sh
# [*] Description: Directory creation script.

source .shared.sh

# Description:
#   This function creates include and src directories for a given module name.
# Args:
#   $1 - The directory/module name to create under src/cxx/include and src/cxx/src.
# Returns:
#   0 on success, 1 on validation or creation failure.
# Echo:
#   Success or error messages via ok/error functions.
function main() {
    local include="src/cxx/include"
    local src="src/cxx/src"
    local dirname="${1}"

    if [[ -z "${dirname}" ]]; then
        error "Dirname is empty"
        return 1
    else
        include="src/cxx/include/${dirname}"
        src="src/cxx/src/${dirname}"
    fi

    if [[ -d "${include}" ]]; then
        error "Include directory already exists: ${include}"
        return 1
    fi

    if ! mkdir -p "${include}"; then
        error "Create include directory failed: ${include}"
        return 1
    fi

    if [[ -d "${src}" ]]; then
        error "Src directory already exists: ${src}"
        return 1
    fi

    if ! mkdir -p "${src}"; then
        error "Create src directory failed: ${src}"
        return 1
    fi

    ok "Create directory ${include} and ${src} success"
    return 0
}

main "${1}"
exit 0
