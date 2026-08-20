/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/cmdlex/lib/ruac_funnel.hpp
 * src/rstd/cmdlex/lib/ruac_funnel.cpp
 */

#include "rstd/cmdlex/lib/ruac_funnel.hpp"
#include <algorithm>

namespace ruac::rstd::cmdlex::lib {

    /**
     * @brief Compress whitespace and split a string into semicolon-separated
     *        command lines
     *
     * @param lines_ - Input string to filter; modified in place
     * @param line_list_ - Output vector to receive the split lines
     *
     * @details Performs two passes:
     *          1. Uses std::unique with a predicate that collapses
     *             consecutive spaces into a single space, erasing the
     *             duplicates from lines_ in place.
     *          2. Iterates over the compressed string character by
     *             character, accumulating into a temporary string. On
     *             encountering ';' the accumulated string is pushed to
     *             line_list_ and the buffer is cleared. After the loop
     *             any remaining non-empty trailing content is also pushed.
     *          No locking is performed; callers must ensure thread safety
     *          (see funnel()).
     *
     */
    void Funnel::filter(std::string &lines_, std::vector<std::string> &line_list_) {

        // Replace multiple spaces with a single space. -> "space: n" -> "space: 1"
        lines_.erase(std::unique(
                         lines_.begin(),
                         lines_.end(),
                         [](char a, char b) { return a == ' ' && b == ' '; }),
                     lines_.end());

        std::string line;
        for (const char &c : lines_) {
            if (c == ';') {
                line_list_.push_back(line);
                line.clear();
            } else {
                line += c;
            }
        }

        if (!line.empty()) {
            line_list_.push_back(line);
            line.clear();
        }
    }

    /**
     * @brief Thread-safe wrapper around filter()
     *
     * @param lines_ - Input string to filter; modified in place
     * @param line_list_ - Output vector to receive the split lines
     *
     * @details Acquires M_FUNNEL_MTX, clears line_list_, then delegates
     *          to filter() to compress whitespace and split on ';'.
     *          This is the public entry point for concurrent callers;
     *          filter() itself is lock-free.
     *
     */
    void Funnel::funnel(std::string &lines_, std::vector<std::string> &line_list_) {

        std::lock_guard<std::mutex> lock(M_FUNNEL_MTX);

        line_list_.clear();

        filter(lines_, line_list_);
    }

} // namespace ruac::rstd::cmdlex::lib
