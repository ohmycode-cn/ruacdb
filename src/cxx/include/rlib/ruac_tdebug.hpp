/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rlib/ruac_tdebug.hpp
 * src/rlib/ruac_tdebug.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_TDEBUG_HPP
#define RUAC_TDEBUG_HPP

#include <mutex>
#include <string>

namespace ruac::rlib::tdebug {

    class Info {
      private:
        std::mutex M_MSG_MTX;

      private:
        Info() = default;
        ~Info() = default;
        Info(const Info &) = delete;
        Info &operator=(const Info &) = delete;

      public:
        static auto get() -> Info &;
        void print(const std::string &msgs_, const std::string &file_, const int line_);
    };

} // namespace ruac::rlib::tdebug

#endif // RUAC_TDEBUG_HPP
