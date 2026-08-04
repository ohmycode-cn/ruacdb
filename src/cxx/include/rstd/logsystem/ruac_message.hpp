/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_message.hpp
 * src/rstd/logsystem/ruac_message.cpp
 *
 * @brief Singleton message output utility with colored error and warning output to stdout
 */

#pragma once
#ifndef RUAC_MESSAGE_HPP
#define RUAC_MESSAGE_HPP

#include "rstd/logsystem/ruac_logstruct.hpp"
#include "rstd/logsystem/ruac_colored.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <iostream>
#include <syncstream>
#include <mutex>

namespace ruac::rstd::logsystem {

    /**
     * @brief Singleton message output utility that formats and writes colored
     *        error/warning messages to stdout via osyncstream
     *
     */
    class Message {
      private:
        Colored *m_colored{nullptr};
        std::mutex m_out_mtx;

      private:
        logtype::string M_WARNING{"WARNING"};
        logtype::string M_ERROR{"ERROR:("};
        logtype::string m_reset{""};
        logtype::string m_red{""};
        logtype::string m_yellow{""};

      private:
        Message() = default;
        ~Message() = default;
        Message(const Message &) = delete;
        Message &operator=(const Message &) = delete;
        void delete_colored_ptr();

      public:
        static auto instance() -> Message &;

      public:
        template <typename E>
        void stdout_err(const E &message_, const logtype::string &msg_prefix_ = "");

        template <typename W>
        void stdout_war(const W &message_, const logtype::string &msg_prefix_ = "");

      public:
        void init(const logstruct::ColoredParamList &param_ = {});
    };

    template <typename E>
    void Message::stdout_err(const E &message_, const logtype::string &msg_prefix_) {
        std::lock_guard<std::mutex> lock(m_out_mtx);
        logtype::string msg_string{"[ " + m_red + msg_prefix_ + M_ERROR + m_reset + " ] " + message_};
        std::osyncstream(std::cout) << msg_string << std::endl;
    }

    template <typename W>
    void Message::stdout_war(const W &message_, const logtype::string &msg_prefix_) {
        std::lock_guard<std::mutex> lock(m_out_mtx);
        logtype::string msg_string{"[ " + m_yellow + msg_prefix_ + M_WARNING + m_reset + " ] " + message_};
        std::osyncstream(std::cout) << msg_string << std::endl;
    }

} // namespace ruac::rstd::logsystem

#endif // RUAC_MESSAGE_HPP
