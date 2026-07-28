/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/welcome/ruac_guidance.hpp
 * src/welcome/ruac_guidance.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_GUIDANCE_HPP
#define RUAC_GUIDANCE_HPP

namespace ruac::welcome {

    namespace guidance {

        struct BaseInfoColorParamList {
            bool m_enable_ce{true};
            bool m_enable_ht{false};
            bool m_enable_bf{false};
            bool m_enable_dp{false};
        };

        class BaseInfo {
          private:
            BaseInfoColorParamList m_param_list{};

          private:
            void show_guide_message();
            void show_color_background();

          public:
            BaseInfo() = default;
            ~BaseInfo() = default;

          public:
            void init(const BaseInfoColorParamList &param_list_ = {});
            void show();
        };

    } // namespace guidance

} // namespace ruac::welcome

#endif // RUAC_GUIDANCE_HPP
