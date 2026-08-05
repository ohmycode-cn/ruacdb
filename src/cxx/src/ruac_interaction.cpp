/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_interaction.hpp
 * src/ruac_interaction.cpp
 */

#include "rstd/colors/ruac_color26.hpp"
#include "welcome/ruac_guidance.hpp"
#include "ruac_interaction.hpp"
#include "ruac_shell_exec.hpp"
#include "ruac_shell_pipe.hpp"
#include <syncstream>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

namespace ruac {

    /**
     * @brief Display the base information guidance
     *
     * @details Creates a heap-allocated BaseInfo object, initializes it with
     *          color and display flags from m_config (enable_ce, enable_ht,
     *          enable_bf, enable_dp), displays the base info, then safely
     *          deletes the object and nullifies the pointer.
     *
     */
    void Interaction::show_base_info_guidance() {
        auto base_info = new ruac::welcome::guidance::BaseInfo();
        base_info->init({
            .m_enable_ce = m_config.m_enable_ce,
            .m_enable_ht = m_config.m_enable_ht,
            .m_enable_bf = m_config.m_enable_bf,
            .m_enable_dp = m_config.m_enable_dp,
        });
        base_info->show();
        if (nullptr != base_info) {
            delete base_info;
            base_info = nullptr;
        }
    }

    /**
     * @brief Set the interactive command prompt
     *
     * @param enable_ht_ - Enable ANSI color output; false disables all colors
     *
     * @details Early-returns if enable_ht_ is false. Creates a temporary
     *          Color26 instance, builds a colored prompt string with 'ruacdb'
     *          in red and '>' in cyan, stores it in m_prompt, then safely
     *          deletes the temporary object.
     *
     */
    void Interaction::set_prompt(const bool enable_ht_) {
        if (!enable_ht_) {
            return;
        }
        auto *tmp = new ruac::rstd::colors::Color26(
            m_config.m_enable_ce,
            m_config.m_enable_ht,
            m_config.m_enable_bf);
        m_prompt = tmp->r("ruacdb") + tmp->c(">") + " ";
        if (nullptr != tmp) {
            delete tmp;
            tmp = nullptr;
        }
    }

    /**
     * @brief Convert the input string to lower case
     *
     * @param str_ - The input string to convert
     *
     * @details Uses std::transform to apply std::tolower to each character in the
     *          input string, converting it to lower case.
     *
     */
    void Interaction::str_tolower(std::string &str_) {
        std::transform(str_.begin(), str_.end(), str_.begin(), [](unsigned char c) { return std::tolower(c); });
    }

    /**
     * @brief Initialize the Interaction with parameter list
     *
     * @param config_ - Interaction configuration
     *
     * @details Stores the provided configuration into m_config for later
     *          use during the interactive session.
     *
     */
    void Interaction::init(const InteractionConfig &config_) {
        m_config = config_;
    }

    /**
     * @brief Run the interactive REPL loop
     *
     * @return bool - True when the loop terminates normally
     *
     * @details Entry point for the interactive command-line interface. First
     *          displays base info guidance via show_base_info_guidance(), then
     *          enters an infinite loop that: prints the prompt via thread-safe
     *          std::osyncstream, reads a line from stdin, skips empty lines and
     *          comment lines (starting with '#' or '//'), and returns true when
     *          end_whiled() detects a quit/exit command.
     *
     */
    auto Interaction::run() -> bool {
        show_base_info_guidance();

        ShellExec sexec;
        std::vector<std::string> cmd_history_records;
        auto cmd_history_records_ptr = &cmd_history_records;
        ShellPipeList pipe;
        pipe.m_cmd_history_records_ptr = cmd_history_records_ptr; // copy the pointer
        ShellPipe::instance().set_shell_pipe_list(pipe);

        while (true) {
            std::osyncstream(std::cout) << m_prompt;
            std::string lines;
            std::getline(std::cin, lines);
            str_tolower(lines);
            if (lines.empty()) {
                continue;
            }
            int code = sexec.exec(lines);
            if (1 == code) {
                return false;
            }
            if (0 == code) {
                return true;
            }
        }
        return true;
    }

} // namespace ruac
