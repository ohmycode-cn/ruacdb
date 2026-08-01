/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_interaction.hpp
 * src/ruac_interaction.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_INTERACTION_HPP
#define RUAC_INTERACTION_HPP

#include <string>

namespace ruac {

    struct InteractionParamList {
        bool m_enable_ce{true};
        bool m_enable_ht{false};
        bool m_enable_bf{false};
        bool m_enable_dp{false};
    };

    class Interaction {
      private:
        InteractionParamList m_param_list{};
        void show_base_info_guidance();

      private:
        std::string m_prompt{"ruacdb> "};

      private:
        void set_prompt(const bool enable_ht_ = false);
        void str_tolower(std::string &str_);

      public:
        Interaction() = default;
        ~Interaction() = default;

      public:
        void init(const InteractionParamList &param_list_ = {});
        auto run() -> bool;
    };

} // namespace ruac

#endif // RUAC_INTERACTION_HPP
