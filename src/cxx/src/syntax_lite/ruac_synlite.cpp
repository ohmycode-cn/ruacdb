/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synlite.hpp
 * src/syntax_lite/ruac_synlite.cpp
 */

#include "syntax_lite/ruac_synlite.hpp"
#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite {

    /**
     * @brief Construct the SynLite instance and initialise the internal Parser
     *
     * @details Creates a fresh Parser instance via std::make_unique and stores
     *          it in M_PARSER so that subsequent syntax_line_hook() calls have
     *          a working parser to delegate to.
     *
     */
    SynLite::SynLite(int uid) {
        M_PARSER = std::make_unique<ruac::syntax_lite::tree::Parser>(uid);
    }

    /**
     * @brief Submit a single RUAC command line for syntax analysis
     *
     * @param line_ - The raw input line containing the RUAC command to parse
     *
     * @details First guards against a null M_PARSER (e.g. if the object was
     *          moved-from); if the parser is missing, emits a thread-safe
     *          diagnostic to stdout and returns early. Otherwise forwards the
     *          line to Parser::get_query() which performs the tokenisation,
     *          AST construction and pre-execution pipeline.
     *
     */
    void SynLite::syntax_line_hook(const std::string &line_) {
        std::lock_guard<std::mutex> lock(M_SYN_LITE_MTX);
        if (nullptr == M_PARSER) {
            std::osyncstream(std::cout) << "Not initialized parser." << std::endl;
            return;
        }
        M_PARSER->get_query(line_);
    }

} // namespace ruac::syntax_lite
