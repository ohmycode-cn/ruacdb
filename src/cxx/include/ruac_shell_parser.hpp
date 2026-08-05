/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_parser.hpp
 * src/ruac_shell_parser.cpp
 * Description of header file function declaration
 *
 * @brief Thread-safe command-line parser that splits semicolon-delimited input into individual commands.
 */

#pragma once
#ifndef RUAC_SHELL_PARSER_HPP
#define RUAC_SHELL_PARSER_HPP

#include <string>
#include <vector>
#include <mutex>

namespace ruac {

    class ShellParser {
      private:
        std::vector<std::string> m_command_line_list;
        std::mutex M_SHELL_PARSER_MTX;
        const char M_SEMICOLON{';'};
        const char M_SPACE{' '};

      public:
        ShellParser() = default;
        ~ShellParser() = default;

      public:
        void get_lines(std::string &lines_);
        auto ret_lines() -> std::vector<std::string>;
        void clr_lines();
    };

} // namespace ruac

#endif // RUAC_SHELL_PARSER_HPP
