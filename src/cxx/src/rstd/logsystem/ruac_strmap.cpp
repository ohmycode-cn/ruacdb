/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_strmap.hpp
 * src/rstd/logsystem/ruac_strmap.cpp
 */

#include "rstd/logsystem/ruac_strmap.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace strmap {

        auto get_ansi_map() -> logtype::StringMap {
            logtype::StringMap map;
            return map;
        }

        auto get_text_map() -> logtype::StringMap {
            logtype::StringMap map;
            return map;
        }

    } // namespace strmap

} // namespace ruac::rstd::logsystem
