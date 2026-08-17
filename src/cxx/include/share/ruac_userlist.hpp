/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/share/ruac_userlist.hpp
 * src/share/ruac_userlist.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_USERLIST_HPP
#define RUAC_USERLIST_HPP

#include <map>
#include <mutex>
#include <string>

namespace ruac::share {

    class UserList {
      private:
        const char *const M_NULL_USER{"nouser"};
        mutable std::mutex M_USER_LIST_MTX;
        std::map<int, std::string> m_umap;

      private:
        UserList() = default;
        ~UserList() = default;
        UserList(const UserList &) = delete;
        UserList &operator=(const UserList &) = delete;

      public:
        static auto instance() -> UserList &;
        auto get_null_user() const -> std::string;
        void add_map(const int uid_, const std::string &uname_);
        auto get_uid(const std::string &uname_) const -> int;
        auto get_une(const int uid_) const -> std::string;
    };

} // namespace ruac::share

#endif // RUAC_USERLIST_HPP
