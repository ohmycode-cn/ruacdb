/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_exec.hpp
 * src/ruac_shell_exec.cpp
 */

#include "ruac_parser_cmd_line.hpp"
#include "ruac_shell_pipe.hpp"
#include "ruac_shell_exec.hpp"
#include <iostream>
#include <syncstream>
#include <sstream>

namespace ruac {

    auto ShellExec::end_whiled(const std::string &line_) -> bool {
        return "quit" == line_ || "exit" == line_ || "quit;" == line_ || "exit;" == line_;
    }

    void ShellExec::cat_cmd_history() {
        auto pipe = ShellPipe::instance().get_shell_pipe_list();
        auto cmdh = pipe.m_cmd_history_records_ptr;
        if (nullptr == cmdh) {
            return;
        }
        if (cmdh->empty()) {
            std::osyncstream(std::cout) << "No history records." << std::endl;
            return;
        }
        std::stringstream ss;
        ss << M_B_GREEN << M_F_YELLOW << "From Backup history records:" << M_RESET << "\n";
        for (const auto &cmd : *cmdh) {
            ss << cmd << "\n";
        }
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

    void ShellExec::cat_cmd_history_bak() {
        // if (m_cmd_history_records_bak.empty()) {
        //     return;
        // }
        std::stringstream ss;
        ss << M_B_RED << M_F_YELLOW << "From Backup history records:" << M_RESET << "\n";
        for (const auto &cmd : m_cmd_history_records_bak) {
            ss << cmd << "\n";
        }
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

    auto ShellExec::inner_exec(const std::string &line_) -> int {
        if (end_whiled(line_)) {
            return 0;
        }
        if ("cat history" == line_) {
            cat_cmd_history();
            cat_cmd_history_bak();
        }
        return 2;
    }

    auto ShellExec::exec(const std::string &lines_) -> int {
        std::lock_guard<std::mutex> lock(M_SHELL_EXEC_MTX);
        auto pipe = ShellPipe::instance().get_shell_pipe_list();
        auto cmdh = pipe.m_cmd_history_records_ptr;
        auto vect = &m_cmd_history_records_bak;
        if (nullptr != cmdh) {
            vect = &(*cmdh);
        }
        ParserCmdLine pcl;
        std::string tmp = lines_;
        pcl.get_cmd_lines(tmp);
        auto cmd_lines = pcl.ret_cmd_line();
        pcl.clr_cmd_list();
        if (cmd_lines.empty()) {
            return 2;
        }
        for (int i{0}; i < cmd_lines.size(); i++) {
            vect->push_back(cmd_lines.at(i));
            int code = inner_exec(cmd_lines.at(i));
            if (0 == code || 1 == code) {
                return code;
            }
        }
        return 2;
    }

} // namespace ruac
