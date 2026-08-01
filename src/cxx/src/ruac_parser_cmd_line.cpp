/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_parser_cmd_line.hpp
 * src/ruac_parser_cmd_line.cpp
 */

#include "ruac_parser_cmd_line.hpp"
#include <mutex>

namespace ruac {

    void ParserCmdLine::get_cmd_lines(std::string &lines_) {
        std::lock_guard<std::mutex> lock(M_PARSER_CMD_LINE_MTX);
        auto lines{lines_};
        lines = lines.substr(0, lines.find_last_not_of("\t\n ") + 1);
        lines = lines.substr(lines.find_first_not_of("\t\n "));
        std::string line;
        bool one_space{false};
        for (auto &c : lines) {
            if (c == M_SEMICOLON) {
                m_cmd_list.push_back(line);
                line.clear();
            } else if (c == ' ') {
                if (!one_space) {
                    line += ' ';
                    one_space = true;
                }
            } else {
                line += c;
                one_space = false;
            }
        }
        if (!line.empty()) {
            m_cmd_list.push_back(line);
        }
    }

    auto ParserCmdLine::ret_cmd_line() -> std::vector<std::string> {
        std::lock_guard<std::mutex> lock(M_PARSER_CMD_LINE_MTX);
        return m_cmd_list;
    }

    void ParserCmdLine::clr_cmd_list() {
        std::lock_guard<std::mutex> lock(M_PARSER_CMD_LINE_MTX);
        m_cmd_list.clear();
    }
} // namespace ruac
