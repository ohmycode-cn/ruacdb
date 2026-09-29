/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/format/tbe26/ruac_tbe26.hpp
 * src/rstd/format/tbe26/ruac_tbe26.cpp
 */

#include "rstd/format/tbe26/ruac_tbe26.hpp"
#include <algorithm>
#include <iterator>
#include <print>
#include <sstream>
#include <string>

namespace {
    constexpr auto NT{'\n'};
    constexpr auto L1{'+'};
    constexpr auto L2{'+'};
    constexpr auto R1{'+'};
    constexpr auto R2{'+'};
    constexpr auto LE{'-'};
    constexpr auto CL{'|'};
    constexpr auto SP{' '};
} // namespace

namespace ruac::rstd::format::tbe26 {

    void TbeFmt::filter_ansi(const std::vector<std::string> &vecstr_) {
        {
            std::println("SORRY NULL ....");
        }
        auto vecstr{vecstr_};
    }

    void TbeFmt::retmax_col(const std::vector<std::string> &vecstr_) {
        for (const auto &item : vecstr_) {
            auto current_size = std::size(item);
            m_maxcol = std::max(m_maxcol, static_cast<unsigned int>(current_size));
        }
    }

    auto TbeFmt::retfmt_str(const std::vector<std::string> &vecstr_) -> std::string {
        std::stringstream ss;
        ss << L1 << SP << std::string(m_maxcol, LE) << SP << R1 << NT;
        for (const auto &item : vecstr_) {
            const auto pad{m_maxcol - static_cast<unsigned int>(std::size(item))};
            ss << CL << SP << item << std::string(pad, SP) << SP << CL << NT;
        }
        ss << L2 << SP << std::string(m_maxcol, LE) << SP << R2 << NT;
        m_maxcol = 0; // reset -> zero
        return ss.str();
    }

} // namespace ruac::rstd::format::tbe26
