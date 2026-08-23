/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/kit/ruac_safemsg.hpp
 * src/google_test/kit/ruac_safemsg.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_SAFEMSG_HPP
#define RUAC_SAFEMSG_HPP

#include <mutex>
#include <string>

namespace ruac::google_test::kit {

    class SafeMsg final {
      private:
        std::mutex M_SAFE_MSG_MTX;
        bool m_stdout{true};

      public:
        SafeMsg() = default;
        ~SafeMsg() = default;
        SafeMsg(const SafeMsg &) = delete;
        SafeMsg &operator=(const SafeMsg &) = delete;

      public:
        void set_output_mode(const bool stdout_ = true);
        void println(const std::string &msg_header_, const std::string &msg_body_);
        void print(const std::string &msg_header_, const std::string &msg_body_);
        static auto get() -> SafeMsg &;
    };

} // namespace ruac::google_test::kit

#endif // RUAC_SAFEMSG_HPP
