#!/bin/bash

# [*] File   Rule: The code should wrap around 100 columns and force wrap around 120 columns
# [*] Style Guide: RUAC-BASH-STYLE-GUIDE.md
# [*] Author     : ohmycode-cn(https://github.com/ohmycode-cn)
# [*]            : ohmycode-cn(ohcode@163.com)
# [*] Bash Std   : Version 5.0 +
# [*] License    : MIT
# [*] File       : .shared.sh
# [*] Description: Shared resource script.

# Highlight: reset
readonly RESET='\033[0m'

# Highlight: black ~ white

readonly BLACK='\033[30m'   # Black
readonly RED='\033[31m'     # Red
readonly GREEN='\033[32m'   # Green
readonly YELLOW='\033[33m'  # Yellow
readonly BLUE='\033[34m'    # Blue
readonly MAGENTA='\033[35m' # Magenta
readonly CYAN='\033[36m'    # Cyan
readonly WHITE='\033[37m'   # White
ONCE_TIME=$(date '+%Y-%m-%d-%H-%M-%S')
# shellcheck disable=SC2034
readonly ONCE_TIME
COLON=${WHITE}":"${RESET}
readonly COLON

# Description:
#   This function echo the current timestamp in YYYY-MM-DD-HH-MM-SS-3N format.
# Args:
#   None
# Returns:
#   None
# Echo:
#   Timestamp in YYYY-MM-DD-HH-MM-SS-3N format.
function now() {
    echo -e "${BLUE}[${BLACK}$(date '+%Y-%m-%d-%H-%M-%S@%3N')${BLUE}]${RESET}"
}

# Description:
#   This function prints an informational message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted INFO log line with timestamp and cyan label.
function info() {
    echo -e "$(now) [${CYAN}INFO ${RESET}] ${COLON}${GREEN}${1}${RESET}"
}

# Description:
#   This function prints a success message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted OK log line with timestamp and green label.
function ok() {
    echo -e "$(now) [${GREEN}OK${RESET}] ${COLON}${GREEN}${1}${RESET}"
}

# Description:
#   This function prints a warning message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted WARNING log line with timestamp and yellow label.
function warning() {
    echo -e "$(now) [${YELLOW}WARNING${RESET}] ${COLON}${YELLOW}${1}${RESET}"
}

# Description:
#   This function prints an error message with a timestamp.
# Args:
#   $1 - The message to display.
# Returns:
#   None
# Echo:
#   Formatted ERROR log line with timestamp and magenta label.
function error() {
    echo -e "$(now) [${RED}ERROR${RESET}] ${COLON}${MAGENTA}${1}${RESET}"
}

SPINNER_LOCK=0 # 0: unlocked, 1: locked
SPINNER_PID=0  # Spinner process ID, 0: not running

# Description:
#   This function draws a spinning clock animation with an optional message.
# Args:
#   $1 - Optional message to display alongside the spinner.
# Returns:
#   None
# Echo:
#   Animated clock spinner with optional message text.
function spinner_draw() {
    local spinner_array=('🕛' '🕐' '🕑' '🕒' '🕓' '🕔' '🕕' '🕖' '🕗' '🕘' '🕙' '🕚')
    local message=""
    local param="${1}"

    if [[ -n "${param}" ]]; then
        message="${param}"
    fi

    while true; do
        for itme in "${spinner_array[@]}"; do
            printf "\r%s %s" "${itme}" "${message}"
            sleep 0.1
        done
        printf "\r                                                                             "
    done
    printf "\r                                                                             "
}

# Description:
#   This function starts a background spinner animation. Ignored if already running.
# Args:
#   $1 - Optional message to display alongside the spinner.
# Returns:
#   None
# Echo:
#   None (spawns background process).
function enable_spinner() {
    if [[ ${SPINNER_LOCK} -eq 1 ]]; then
        return
    fi
    SPINNER_LOCK=1
    tput civis
    spinner_draw "${1}" &
    SPINNER_PID=$!
}

# Description:
#   This function stops the running spinner and restores the cursor.
# Args:
#   None
# Returns:
#   None
# Echo:
#   None (kills background spinner process).
function cancel_spinner() {
    if [[ ${SPINNER_LOCK} -eq 0 ]]; then
        return
    fi
    kill ${SPINNER_PID} 2>/dev/null
    wait ${SPINNER_PID} 2>/dev/null
    info "done spinner"
    tput cnorm
    SPINNER_LOCK=0
}
