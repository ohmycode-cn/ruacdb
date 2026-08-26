/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_name.hpp
 * src/system/user/ruac_name.cpp
 *
 * @brief Defines the UserName singleton class with a doubly-linked list for thread-safe user name management.
 */

#pragma once
#ifndef RUAC_NAME_HPP
#define RUAC_NAME_HPP

#include "system/user/lib/ruac_name_node.hpp"

#include <memory>
#include <mutex>
#include <string>

namespace ruac::system::user {

    class UserName {
      private:
        std::unique_ptr<lib::UserNameList> m_user_name_list{std::make_unique<lib::UserNameList>()};
        std::mutex M_USER_NAME_MTX;
        bool m_init_lock{false};

      private:
        UserName();
        ~UserName() = default;
        UserName(const UserName &) = delete;
        UserName &operator=(const UserName &) = delete;

      private:
        void push_back(const std::string &name_);

      public:
        static auto instance() -> UserName &;
        auto add_user(const std::string &username_) -> bool;
    };

} // namespace ruac::system::user

#endif // RUAC_NAME_HPP
