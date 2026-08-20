/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synxlite.hpp
 * src/syntax_lite/ruac_synxlite.cpp
 */

#include "syntax_lite/ruac_synxlite.hpp"

#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::api {

    /**
     * @brief Construct a SynxLite with a parser for the given user
     *
     * @param uid_ - User ID for the parsing context
     *
     */
    SynxLite::SynxLite(int uid_) {
        M_PARSER = std::make_unique<ruac::syntax_lite::tree::Parser>(uid_);
    }

    /**
     * @brief Parse a command line thread-safely
     *
     * @param line_ - The command line string to process
     *
     * @details Acquires M_SYN_LITE_MTX. Checks M_PARSER for null, printing a fatal
     *          error if missing. Delegates to Parser::process() for tokenization and parsing.
     *
     */
    void SynxLite::process(const std::string &line_) {
        std::lock_guard<std::mutex> lock(M_SYN_LITE_MTX);
        if (nullptr == M_PARSER) {
            std::osyncstream(std::cout) << "Fatal: Not initialized parser." << std::endl;
            return;
        }
        M_PARSER->process(line_);
    }

} // namespace ruac::syntax_lite::api
