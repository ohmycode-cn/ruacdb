/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/format/tbe26/ruac_tbe26.hpp
 * src/rstd/format/tbe26/ruac_tbe26.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_TBE26_HPP
#define RUAC_TBE26_HPP

#include <vector>
#include <string>
#include <mutex>

namespace ruac::rstd::format::tbe26 {

    class TbeFmt {
      private:
        std::mutex M_TBE_FMT_MTX;
        unsigned int m_maxcol{0};

      public:
        TbeFmt() = default;
        ~TbeFmt() = default;

      public:
        void filter_ansi(const std::vector<std::string> &vecstr_);
        void retmax_col(const std::vector<std::string> &vecstr_);
        auto retfmt_str(const std::vector<std::string> &vecstr_) -> std::string;
    };

} // namespace ruac::rstd::format::tbe26

#endif // RUAC_TBE26_HPP
