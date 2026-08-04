/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/messages/ruac_stdmsg.hpp
 * src/rstd/messages/ruac_stdmsg.cpp
 *
 * @brief Provides thread-safe message output utilities for stdout and stderr.
 */

#pragma once
#ifndef RUAC_STDMSG_HPP
#define RUAC_STDMSG_HPP

#include <syncstream>
#include <iostream>
#include <mutex>

namespace ruac::rstd::messages {

    class StdMsg {
      private:
        StdMsg() = default;
        ~StdMsg() = default;
        StdMsg(const StdMsg &) = delete;
        StdMsg &operator=(const StdMsg &) = delete;

      private:
        std::mutex m_print_mtx;

      public:
        template <typename T>
        void print(const T &msg_, const bool &stdout_ = true);

      public:
        static auto instance() -> StdMsg &;
    };

    /**
     * @brief Print message to stdout or stderr
     *
     * @param msg_ Message to print
     * @param stdout_ Whether to print to stdout or stderr
     *
     * @return void
     */
    template <typename T>
    void StdMsg::print(const T &msg_, const bool &stdout_) {
        std::lock_guard<std::mutex> lock(m_print_mtx);
        (!stdout_) ? std::osyncstream(std::cerr) << msg_ << std::endl
                   : std::osyncstream(std::cout) << msg_ << std::endl;
    }

} // namespace ruac::rstd::messages

#endif // RUAC_STDMSG_HPP
