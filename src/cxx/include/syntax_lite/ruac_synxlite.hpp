/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synxlite.hpp
 * src/syntax_lite/ruac_synxlite.cpp
 *
 * @brief Provides the SynxLite class for thread-safe RUAC syntax analysis.
 */

#pragma once
#ifndef RUAC_SYNLITE_HPP
#define RUAC_SYNLITE_HPP

#include "syntax_lite/tree/ruac_parser.hpp"

#include <mutex>
#include <string>

namespace ruac::syntax_lite::api {

    /**
     * @brief Lightweight syntax analyzer for RUAC commands.
     *
     * Provides a thread-safe interface for parsing single-line RUAC syntax commands,
     * with methods to submit a line for analysis and retrieve the resulting status
     * code.
     */
    class SynxLite {
      private:
        std::unique_ptr<ruac::syntax_lite::tree::Parser> M_PARSER;
        std::mutex M_SYN_LITE_MTX;

      public:
        explicit SynxLite(int uid_ = 1);
        ~SynxLite() = default;

      public:
        void process(const std::string &line_);
    };

} // namespace ruac::syntax_lite::api

#endif // RUAC_SYNLITE_HPP
