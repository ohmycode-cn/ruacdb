/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_confmap.hpp
 * src/rstd/logsystem/ruac_confmap.cpp
 * @brief Provides get_default_config_map() for retrieving default log system configuration.
 */

#pragma once
#ifndef RUAC_CONFMAP_HPP
#define RUAC_CONFMAP_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace confmap {

        auto get_default_config_map() -> logtype::strmap;

    } // namespace confmap

} // namespace ruac::rstd::logsystem

#endif // RUAC_CONFMAP_HPP
