/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logstruct.hpp
 * src/rstd/logsystem/ruac_logstruct.cpp
 * Description of header file function declaration
 *
 * Defines common data structures used in the log system
 *
 */

#pragma once
#ifndef RUAC_LOGSTRUCT_HPP
#define RUAC_LOGSTRUCT_HPP

namespace ruac::rstd::logsystem {

    namespace logstruct {

        struct ColoredParamList {
            bool m_enable_ce{true};
            bool m_enable_ht{false};
            bool m_enable_bf{false};
        };

    } // namespace logstruct

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGSTRUCT_HPP
