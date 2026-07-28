/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/welcome/ruac_guidance.hpp
 * src/welcome/ruac_guidance.cpp
 */

#include "rstd/colors/ruac_background.hpp"
#include "welcome/ruac_guidance.hpp"
#include "rstd/ruac_donone.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace ruac::welcome {

    namespace {
        namespace crlib = rstd::colors;
    } // namespace

    namespace guidance {

        /**
         * @brief Display a colored background with two rows of color blocks
         *
         * @details Early-returns if m_enable_ht is false. Creates two
         *          Background instances (bd0 and bd1) to output 8 colored
         *          space blocks (dark, red, green, yellow, blue, magenta,
         *          cyan, white) in two rows via std::stringstream. Uses
         *          configuration flags m_enable_ce and m_enable_dp from
         *          m_param_list. Safely deletes both Background instances
         *          after use.
         *
         */
        void BaseInfo::show_color_background() {

            auto ht = m_param_list.m_enable_ht;
            if (!ht) {
                return;
            }
            auto ce = m_param_list.m_enable_ce;
            auto dp = m_param_list.m_enable_dp;

            constexpr const char *const SPACE{"    "};
            std::stringstream ss;

            auto *bd0 = new crlib::Background(ht, ce, dp);
            ss << bd0->d(SPACE);
            ss << bd0->r(SPACE);
            ss << bd0->g(SPACE);
            ss << bd0->y(SPACE);
            ss << bd0->b(SPACE);
            ss << bd0->m(SPACE);
            ss << bd0->c(SPACE);
            ss << bd0->w(SPACE);
            delete bd0;
            bd0 = nullptr;

            auto *bd1 = new crlib::Background(ht, ce, dp);
            ss << "\n";
            ss << bd1->d(SPACE);
            ss << bd1->r(SPACE);
            ss << bd1->g(SPACE);
            ss << bd1->y(SPACE);
            ss << bd1->b(SPACE);
            ss << bd1->m(SPACE);
            ss << bd1->c(SPACE);
            ss << bd1->w(SPACE);
            delete bd1;
            bd1 = nullptr;

            std::cout << ss.str() << std::endl;
        }

        /**
         * @brief Initialize the BaseInfo with color parameter list
         *
         * @param param_list_ - BaseInfo color parameter list containing config
         *
         * @details Stores the provided BaseInfoColorParamList into m_param_list
         *          for later use during display operations.
         *
         */
        void BaseInfo::init(const BaseInfoColorParamList &param_list_) {
            m_param_list = param_list_;
        }

        /**
         * @brief Display the base information
         *
         * @details Uses a ternary operator: calls show_color_background()
         *          when m_param_list.m_enable_ht is true, otherwise calls
         *          ruac::rstd::donone::notdo() as a no-op (does nothing).
         *
         */
        void BaseInfo::show() {
            (m_param_list.m_enable_ht) ? show_color_background() : ruac::rstd::donone::notdo();
        }

    } // namespace guidance

} // namespace ruac::welcome
