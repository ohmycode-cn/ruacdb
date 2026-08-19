/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_username.hpp
 * src/usersystem/ruac_username.cpp
 *
 * @brief Defines the UserName singleton class with a doubly-linked list for thread-safe user name management.
 */

#pragma once
#ifndef RUAC_USERNAME_HPP
#define RUAC_USERNAME_HPP

#include <memory>
#include <mutex>
#include <string>

namespace ruac::usersystem {

    struct UserNameNode {
        std::string name;
        std::shared_ptr<UserNameNode> prev;
        std::shared_ptr<UserNameNode> next;
    };

    struct UserNameList {
        int size{0};
        std::shared_ptr<UserNameNode> head;
        std::shared_ptr<UserNameNode> tail;
    };

    class UserName {
      private:
        UserNameList m_user_name_list;
        std::mutex M_USER_NAME_MTX;

      private:
        UserName() = default;
        ~UserName() = default;
        UserName(const UserName &) = delete;
        UserName &operator=(const UserName &) = delete;

      private:
        void push_back(const std::string &name_);

      public:
        static auto instance() -> UserName &;
        auto add_user(const std::string &username_) -> bool;
    };

} // namespace ruac::usersystem

#endif // RUAC_USERNAME_HPP
