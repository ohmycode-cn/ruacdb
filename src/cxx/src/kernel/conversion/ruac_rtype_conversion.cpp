/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/conversion/ruac_rtype_conversion.hpp
 * src/kernel/conversion/ruac_rtype_conversion.cpp
 */

#include "kernel/conversion/ruac_rtype_conversion.hpp"

namespace ruac::kernel::conversion {
    using ruac::kernel::core::type::rtype;

    auto rtype_to_string(const rtype &rtype_) -> std::string {
        switch (rtype_) {
        case rtype::NONE:
            return "none";
        case rtype::INT64U:
            return "int64u";
        case rtype::INT32U:
            return "int32u";
        case rtype::INT16U:
            return "int16u";
        case rtype::INT8U:
            return "int8u";
        case rtype::INT64:
            return "int64";
        case rtype::INT32:
            return "int32";
        case rtype::INT16:
            return "int16";
        case rtype::INT8:
            return "int8";
        case rtype::DOUBLE:
            return "double";
        case rtype::FLOAT:
            return "float";
        case rtype::CHAR32:
            return "char32";
        case rtype::CHAR16:
            return "char16";
        case rtype::CHAR8:
            return "char8";
        case rtype::CHAR:
            return "char";
        case rtype::STRING:
            return "string";
        default:
            return "error_type";
        }
    }

    auto string_to_rtype(const std::string &string_type_) -> rtype {
        if (string_type_ == "none") {
            return rtype::NONE;
        }
        if (string_type_ == "int64u") {
            return rtype::INT64U;
        }
        if (string_type_ == "int32u") {
            return rtype::INT32U;
        }
        if (string_type_ == "int16u") {
            return rtype::INT16U;
        }
        if (string_type_ == "int8u") {
            return rtype::INT8U;
        }
        if (string_type_ == "int64") {
            return rtype::INT64;
        }
        if (string_type_ == "int32") {
            return rtype::INT32;
        }
        if (string_type_ == "int16") {
            return rtype::INT16;
        }
        if (string_type_ == "int8") {
            return rtype::INT8;
        }
        if (string_type_ == "double") {
            return rtype::DOUBLE;
        }
        if (string_type_ == "float") {
            return rtype::FLOAT;
        }
        if (string_type_ == "char32") {
            return rtype::CHAR32;
        }
        if (string_type_ == "char16") {
            return rtype::CHAR16;
        }
        if (string_type_ == "char8") {
            return rtype::CHAR8;
        }
        if (string_type_ == "char") {
            return rtype::CHAR;
        }
        if (string_type_ == "string") {
            return rtype::STRING;
        }
        return rtype::ERROR_TYPE;
    }

} // namespace ruac::kernel::conversion
