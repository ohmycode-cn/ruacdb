/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/cmdlex/ruac_cmdlex.hpp
 * src/rstd/cmdlex/ruac_cmdlex.cpp
 */

#include "rstd/cmdlex/ruac_cmdlex.hpp"

#include <memory>
#include <mutex>

namespace ruac::rstd::cmdlex::api {

    /**
     * @brief Construct a CmdLex owning a Funnel instance
     *
     * @details Allocates a new Funnel via std::make_unique and stores it
     *          in m_funnel. The Funnel provides the actual whitespace
     *          compression and semicolon-splitting logic.
     *
     */
    CmdLex::CmdLex() : m_funnel(std::make_unique<ruac::rstd::cmdlex::lib::Funnel>()) {}

    /**
     * @brief Lex a raw input string into command lines
     *
     * @param lines_ - Input string to process; modified in place by the
     *                underlying Funnel
     * @param line_list_ - Output vector to receive the split lines; its
     *                    existing contents are cleared inside
     *                    Funnel::funnel() before the split is performed
     *
     * @return bool - true if at least one command line was produced;
     *               false if the Funnel is null, the input is empty, or
     *               no lines resulted from lexing
     *
     * @details Acquires M_INTERFACE_MTX for thread-safe access. Returns
     *          false early when m_funnel is null or lines_ is empty.
     *          Otherwise delegates to Funnel::funnel() to compress
     *          whitespace and split on ';'. A final check returns false
     *          if the output vector is still empty after lexing.
     *
     */
    auto CmdLex::lex(std::string &lines_, std::vector<std::string> &line_list_) -> bool {

        std::lock_guard<std::mutex> lock(M_INTERFACE_MTX);

        if (nullptr == m_funnel || lines_.empty()) {
            return false;
        }

        m_funnel.get()->funnel(lines_, line_list_);

        if (line_list_.empty()) {
            return false;
        }

        return true;
    }

} // namespace ruac::rstd::cmdlex::api
