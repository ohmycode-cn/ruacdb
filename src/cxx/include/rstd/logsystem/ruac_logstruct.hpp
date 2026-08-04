/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logstruct.hpp
 * src/rstd/logsystem/ruac_logstruct.cpp
 * @brief Defines common data structures for the log system.
 */

#pragma once
#ifndef RUAC_LOGSTRUCT_HPP
#define RUAC_LOGSTRUCT_HPP

namespace ruac::rstd::logsystem {

    namespace logstruct {

        /**
         * @brief Configuration parameters for the colorizer in log output.
         *
         * Controls color enable, highlight mode, and bold font settings for colored log output.
         */
        struct ColoredParamList {
            bool m_enable_ce{true};
            bool m_enable_ht{false};
            bool m_enable_bf{false};
        };

    } // namespace logstruct

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGSTRUCT_HPP
