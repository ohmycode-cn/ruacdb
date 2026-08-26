/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/conversion/ruac_rval_conversion.hpp
 * src/kernel/conversion/ruac_rval_conversion.cpp
 */

#include "kernel/conversion/ruac_rval_conversion.hpp"

#include <charconv>

namespace ruac::kernel::conversion {

    using ruac::kernel::core::type::rtype;
    using ruac::kernel::core::vals::rval;

    auto rval_to_string(const rval &rval_) -> std::string {
        return std::visit([](const auto &value_) -> std::string {
            using T = std::decay_t<decltype(value_)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return "";
            } else if constexpr (std::is_same_v<T, std::string>) {
                return value_;
            } else if constexpr (std::is_same_v<T, char>) {
                return std::to_string(static_cast<int>(value_));
            } else if constexpr (std::is_same_v<T, char8_t>) {
                return std::to_string(static_cast<unsigned int>(value_));
            } else if constexpr (std::is_same_v<T, char16_t>) {
                return std::to_string(static_cast<unsigned int>(value_));
            } else if constexpr (std::is_same_v<T, char32_t>) {
                return std::to_string(static_cast<unsigned long>(value_));
            } else {
                return std::to_string(value_);
            }
        },
                          rval_);
    }

    auto string_to_rval(const std::string &string_rval_, rtype rtype_) -> rval {
        const char *begin = string_rval_.data();
        const char *end = begin + string_rval_.size();

        switch (rtype_) {
        case rtype::NONE:
            return std::monostate{};
        case rtype::INT64U: {
            std::uint64_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return v;
            }
            return std::monostate{};
        }
        case rtype::INT32U: {
            std::uint32_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<std::uint64_t>(v);
            }
            return std::monostate{};
        }
        case rtype::INT16U: {
            std::uint16_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<std::uint64_t>(v);
            }
            return std::monostate{};
        }
        case rtype::INT8U: {
            std::uint8_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<std::uint64_t>(v);
            }
            return std::monostate{};
        }
        case rtype::INT64: {
            std::int64_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return v;
            }
            return std::monostate{};
        }
        case rtype::INT32: {
            std::int32_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<std::int64_t>(v);
            }
            return std::monostate{};
        }
        case rtype::INT16: {
            std::int16_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<std::int64_t>(v);
            }
            return std::monostate{};
        }
        case rtype::INT8: {
            std::int8_t v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<std::int64_t>(v);
            }
            return std::monostate{};
        }
        case rtype::DOUBLE: {
            double v = 0.0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return v;
            }
            return std::monostate{};
        }
        case rtype::FLOAT: {
            float v = 0.0f;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return v;
            }
            return std::monostate{};
        }
        case rtype::CHAR32: {
            unsigned long v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<char32_t>(v);
            }
            return std::monostate{};
        }
        case rtype::CHAR16: {
            unsigned int v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<char16_t>(v);
            }
            return std::monostate{};
        }
        case rtype::CHAR8: {
            unsigned int v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<char8_t>(v);
            }
            return std::monostate{};
        }
        case rtype::CHAR: {
            int v = 0;
            auto [ptr, ec] = std::from_chars(begin, end, v);
            if (ec == std::errc{} && ptr == end) {
                return static_cast<char>(v);
            }
            return std::monostate{};
        }
        case rtype::STRING:
            return string_rval_;
        default:
            return std::monostate{};
        }
    }

} // namespace ruac::kernel::conversion
