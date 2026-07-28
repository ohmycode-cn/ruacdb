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
#include <syncstream>
#include <iostream>
#include <string>

namespace ruac {

    /**
     * @brief Display the base information guidance
     *
     * @details Creates a heap-allocated BaseInfo object, initializes it with
     *          color and display flags from m_param_list (enable_ce, enable_ht,
     *          enable_bf, enable_dp), displays the base info, then safely
     *          deletes the object and nullifies the pointer.
     *
     */
    void Interaction::show_base_info_guidance() {
        auto base_info = new ruac::welcome::guidance::BaseInfo();
        base_info->init({
            .m_enable_ce = m_param_list.m_enable_ce,
            .m_enable_ht = m_param_list.m_enable_ht,
            .m_enable_bf = m_param_list.m_enable_bf,
            .m_enable_dp = m_param_list.m_enable_dp,
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
            m_param_list.m_enable_ce,
            m_param_list.m_enable_ht,
            m_param_list.m_enable_bf);
        m_prompt = tmp->r("ruacdb") + tmp->c(">") + " ";
        if (nullptr != tmp) {
            delete tmp;
            tmp = nullptr;
        }
    }

    /**
     * @brief Check if the input line matches a quit/exit command
     *
     * @param line_ - User input line to check
     *
     * @return bool - True if the line matches a quit/exit command, false otherwise
     *
     * @details Returns true if the input line matches one of four variations:
     *          "quit", "exit", "quit;", or "exit;". Used to determine when
     *          the interactive REPL loop should terminate.
     *
     */
    auto Interaction::end_whiled(const std::string &line_) -> bool {
        return "quit" == line_ || "exit" == line_ || "quit;" == line_ || "exit;" == line_;
    }

    /**
     * @brief Initialize the Interaction with parameter list
     *
     * @param param_list_ - Interaction parameter list containing configuration
     *
     * @details Stores the provided parameter list into m_param_list for later
     *          use during the interactive session.
     *
     */
    void Interaction::init(const InteractionParamList &param_list_) {
        m_param_list = param_list_;
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
        while (true) {
            std::osyncstream(std::cout) << m_prompt;
            std::string line;
            std::getline(std::cin, line);
            if (line.empty()) {
                continue;
            }
            if ("#" == line.substr(0, 1) || "//" == line.substr(0, 2)) {
                continue;
            }
            if (end_whiled(line)) {
                return true;
            }
        }
        return true;
    }

} // namespace ruac
