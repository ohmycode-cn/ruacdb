/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_parser_cmd_line.hpp
 * src/ruac_parser_cmd_line.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_PARSER_CMD_LINE_HPP
#define RUAC_PARSER_CMD_LINE_HPP

#include <string>
#include <vector>
#include <mutex>

namespace ruac {

    class ParserCmdLine {
      private:
        static constexpr const char M_SEMICOLON{';'};
        static constexpr const char M_SPACE{' '};
        std::mutex M_PARSER_CMD_LINE_MTX;
        std::vector<std::string> m_cmd_list;

      private:
      public:
        ParserCmdLine() = default;
        ~ParserCmdLine() = default;

      public:
        void get_cmd_lines(std::string &lines_);
        auto ret_cmd_line() -> std::vector<std::string>;
        void clr_cmd_list();
    };

} // namespace ruac

#endif // RUAC_PARSER_CMD_LINE_HPP
