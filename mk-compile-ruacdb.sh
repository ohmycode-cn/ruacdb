#!/bin/bash

if [[ "${0}" != "${BASH_SOURCE[0]}" ]]; then
    echo -e "[EXEC ERROR] The standard safe practice is 'bash ${0}'"
    return 1 &>/dev/null
fi

# [*] File   Rule: The code should wrap around 100 columns and force wrap around 120 columns
# [*] Style Guide: RUAC-BASH-STYLE-GUIDE.md
# [*] Author     : ohmycode-cn(https://github.com/ohmycode-cn)
# [*]            : ohmycode-cn(ohcode@163.com)
# [*] Bash Std   : Version 5.0 +
# [*] License    : MIT
# [*] File       : mk-compile-ruacdb.sh
# [*] Description: Build script for ruacdb project.

source .shared.sh

# Description:
#   This function builds the ruacdb project via CMake.
#   By default, unit tests are enabled (UNIT_TEST=ON).
#   Pass --off-unit-test to build a production binary.
#   Pass --clear-build to delete build/* before building.
# Args:
#   $@ - Command line arguments.
# Returns:
#   0 on success, 1 on build failure.
# Echo:
#   Build progress and result messages.
function main() {
    local unit_test="ON"    # default: unit test enabled
    local clear_build="OFF" # default: do not clear build directory

    while [[ $# -gt 0 ]]; do
        case "${1}" in
        --off-unit-test)
            unit_test="OFF"
            shift
            ;;
        --clear-build)
            clear_build="ON"
            shift
            ;;
        *)
            error "Unknown option: ${1}"
            return 1
            ;;
        esac
    done

    local build_dir="build"

    if [[ "${clear_build}" == "ON" ]]; then
        info "Build mode: Clearing build directory: ${build_dir}/*"
        rm -rf "${build_dir:?}"/*
    fi

    if [[ "${unit_test}" == "ON" ]]; then
        info "Build mode: Debug (UNIT_TEST=ON)"
    else
        info "Build mode: Release (UNIT_TEST=OFF)"
    fi

    if [[ ! -f "CMakeLists.txt" ]]; then
        error "CMakeLists.txt not found. Please check the project directory: 'ruacdb/CMakeLists.txt'"
        return 1
    fi

    info "Configuring CMake ..."
    enable_spinner "cmake configuring"

    if ! cmake -B "${build_dir}" -DUNIT_TEST="${unit_test}" 2>&1; then
        cancel_spinner
        error "CMake configure failed."
        return 1
    fi

    cancel_spinner
    ok "CMake configure done."
    info "Compiling ..."
    enable_spinner "compiling"

    local nproc
    if command -v nproc &>/dev/null; then
        nproc=$(nproc)
    elif command -v sysctl &>/dev/null; then
        nproc=$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
    else
        nproc=4
    fi

    if ! cmake --build "${build_dir}" -j "${nproc}" 2>&1; then
        cancel_spinner
        error "Build failed."
        return 1
    fi

    cancel_spinner
    ok "Build success: out/ruacdb"
    return 0
}

main "${@}"
exit ${?}
