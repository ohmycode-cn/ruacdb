/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/util/ruac_string_to_rtype.hpp
 * src/syntax_lite/tree/node/util/ruac_string_to_rtype.cpp
 */

#include "kernel/conversion/ruac_rtype_conversion.hpp"
#include "syntax_lite/tree/node/util/ruac_string_to_rtype.hpp"

#include <vector>

namespace ruac::syntax_lite::tree::node::util {

    auto string_to_rtype(const std::vector<std::string> &stypes_) -> std::vector<rtype> {
        std::vector<rtype> rtypes;
        for (const auto &st : stypes_) {
            rtypes.push_back(ruac::kernel::conversion::string_to_rtype(st));
        }
        return rtypes;
    }

    auto rtype_to_string(const std::vector<rtype> &rtypes_) -> std::vector<std::string> {
        std::vector<std::string> stypes;
        for (const auto &rt : rtypes_) {
            stypes.push_back(ruac::kernel::conversion::rtype_to_string(rt));
        }
        return stypes;
    }

} // namespace ruac::syntax_lite::tree::node::util
