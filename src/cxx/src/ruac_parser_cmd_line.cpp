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

    /**
     * @brief Parse a semicolon-delimited command string into individual entries
     *
     * @param lines_ - Input command string to parse (read-only, not modified)
     *
     * @details Acquires M_PARSER_CMD_LINE_MTX via std::lock_guard for thread
     *          safety against sibling methods. Trims trailing then leading
     *          whitespace, then iterates character-by-character: splits on
     *          M_SEMICOLON to push segments into m_cmd_list (semicolon itself
     *          is discarded), collapses consecutive spaces into one, and pushes
     *          a final non-empty trailing segment. Results accumulate across
     *          calls (list is not cleared); call clr_cmd_list() first for a
     *          fresh parse. Consecutive semicolons produce empty-string entries.
     *
     */
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

    /**
     * @brief Return a snapshot copy of the internal command list
     *
     * @return std::vector<std::string> - Copy by value of m_cmd_list
     *
     * @details Acquires M_PARSER_CMD_LINE_MTX via std::lock_guard during the
     *          copy construction. Returns an empty vector if no commands have
     *          been parsed or if clr_cmd_list() was the last mutating call.
     *          Because the return is by value, the caller's vector is
     *          independent and requires no lock to read.
     *
     */
    auto ParserCmdLine::ret_cmd_line() -> std::vector<std::string> {
        std::lock_guard<std::mutex> lock(M_PARSER_CMD_LINE_MTX);
        return m_cmd_list;
    }

    /**
     * @brief Clear the internal command list, removing all parsed entries
     *
     * @details Acquires M_PARSER_CMD_LINE_MTX via std::lock_guard. Clears
     *          m_cmd_list so that a subsequent ret_cmd_line() returns an empty
     *          vector. Intended as the reset mechanism paired with
     *          get_cmd_lines()'s append semantics for a non-accumulating parse.
     *
     */
    void ParserCmdLine::clr_cmd_list() {
        std::lock_guard<std::mutex> lock(M_PARSER_CMD_LINE_MTX);
        m_cmd_list.clear();
    }
} // namespace ruac
