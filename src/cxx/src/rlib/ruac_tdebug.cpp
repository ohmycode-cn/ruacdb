/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rlib/ruac_tdebug.hpp
 * src/rlib/ruac_tdebug.cpp
 */

#include "rlib/ruac_tdebug.hpp"

#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"

#include <sstream>

namespace ruac::rlib::tdebug {

    /**
     * @brief Format class, function, and optional message into a debug string
     *
     * @param class_  Class name (moved into, consumed)
     * @param func_   Function name (moved into, consumed)
     * @param msgs_   Optional message (moved into, consumed)
     * @return Formatted string owned by caller (move semantics)
     *
     * @note Use-and-drop: all internal state destroyed on return.
     */
    auto Info::innerfmt(std::string class_, std::string func_, std::string msgs_) -> std::string {
        std::stringstream ss;
        ss << "Class: " << class_ << "\n";
        ss << "  |_Func: " << func_ << "\n";
        if (!msgs_.empty()) {
            ss << "    |_Msgs: " << msgs_ << "\n";
        }
        return ss.str();
    };

    /**
     * @brief Get the singleton Info instance
     *
     * @return Info & - Reference to the static singleton instance
     *
     * @details Uses a function-local static to guarantee a single
     *          instance for the lifetime of the program.
     */
    auto Info::get() -> Info & {
        static Info instance;
        return instance;
    }

    /**
     * @brief Format a debug message (thread-safe)
     *
     * @param class_  Class name (moved into innerfmt, consumed)
     * @param func_   Function name (moved into innerfmt, consumed)
     * @param msgs_   Optional message (default "", moved into innerfmt, consumed)
     * @return Formatted string owned by caller (move semantics)
     *
     * @note Ownership is transferred via std::move to innerfmt.
     *       Recommended: pass std::string or string literals.
     *       The return value can be safely std::move'd into print().
     */
    auto Info::fmt(std::string class_, std::string func_, std::string msgs_) -> std::string {
        std::lock_guard<std::mutex> lock(M_MSG_MTX);
        auto fmt_string = innerfmt(
            std::move(class_),
            std::move(func_),
            std::move(msgs_));
        return fmt_string;
    }

    /**
     * @brief Print a formatted debug message
     *
     * @param msgs_  Message content (string_view, zero-heap-copy)
     * @param file_  Source file path (__FILE__, points to static storage)
     * @param line_  Source line number (__LINE__, stack value)
     *
     * @details Delegates to rstd::messages::StdDug::ostrs_view() to build
     *          a formatted debug string with file and line information,
     *          then outputs it via rstd::messages::StdMsg::print().
     *
     * @note Calling conventions:
     *   - msgs_ is a non-owning view; caller MUST ensure the underlying
     *     data outlives this call. Preferred sources:
     *     1. std::string (lvalue or rvalue) — safe, implicit zero-cost view
     *     2. String literal ("...") — safe, points to static storage
     *     3. std::string from fmt() return — safe, survives the call
     *   - Avoid passing temporary char[] or destroyed buffers.
     *   - file_ must point to persistent storage (use __FILE__).
     *   - Thread-safe output via std::osyncstream.
     */
    void Info::print(std::string_view msgs_, const char *file_, const int line_) {
        {
            auto &msg{ruac::rstd::messages::StdMsg::instance()};
            auto &dug{ruac::rstd::messages::StdDug::instance()};
            msg.print(dug.ostrs_view(msgs_, file_, line_), true);
        }
    }

} // namespace ruac::rlib::tdebug
