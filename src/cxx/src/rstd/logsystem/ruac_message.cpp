/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_message.hpp
 * src/rstd/logsystem/ruac_message.cpp
 */

#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_colored.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Return the global singleton Message instance
     *
     * @return Reference to the static Message object
     *
     */
    auto Message::instance() -> Message & {
        static Message instance_object;
        return instance_object;
    }

    /**
     * @brief Initialize the Message with colored output sequences
     *
     * @param param_ Configuration for ANSI color behavior
     *
     */
    void Message::init(const logstruct::ColoredParamList &param_) {
        Colored colored(param_.m_enable_ce, param_.m_enable_ht, param_.m_enable_bf);
        m_reset = colored.get_var(ColoredName::RESET);
        m_red = colored.get_var(ColoredName::RED);
        m_yellow = colored.get_var(ColoredName::YELLOW);
    }

} // namespace ruac::rstd::logsystem
