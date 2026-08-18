/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synlite.hpp
 * src/syntax_lite/ruac_synlite.cpp
 *
 * @brief Provides the SynLite class for thread-safe RUAC syntax analysis.
 */

#pragma once
#ifndef RUAC_SYNLITE_HPP
#define RUAC_SYNLITE_HPP

#include "syntax_lite/tree/ruac_parser.hpp"
#include <mutex>
#include <string>

namespace ruac::syntax_lite {

    /**
     * @brief Lightweight syntax analyzer for RUAC commands.
     *
     * Provides a thread-safe interface for parsing single-line RUAC syntax commands,
     * with methods to submit a line for analysis and retrieve the resulting status
     * code.
     */
    class SynLite {
      private:
        std::unique_ptr<ruac::syntax_lite::tree::Parser> M_PARSER;
        std::mutex M_SYN_LITE_MTX;

      public:
        explicit SynLite(int uid_ = 1);
        ~SynLite() = default;

      public:
        void syntax_line_hook(const std::string &line_);
    };

} // namespace ruac::syntax_lite

#endif // RUAC_SYNLITE_HPP
