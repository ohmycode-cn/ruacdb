/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_username.hpp
 * src/usersystem/ruac_username.cpp
 */

#include "usersystem/ruac_username.hpp"

namespace ruac::usersystem {

    auto UserName::instance() -> UserName & {
        static UserName instance_object;
        return instance_object;
    }

    void UserName::push_back(const std::string &name) {
        auto node = std::make_shared<UserNameNode>();
        node->name = name;
        if (!m_user_name_list.head) {
            m_user_name_list.head = node;
            m_user_name_list.tail = node;
        } else {
            node->prev = m_user_name_list.tail;
            m_user_name_list.tail->next = node;
            m_user_name_list.tail = node;
        }
        m_user_name_list.size++;
    }

    auto UserName::user_exists(const std::string &username_) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_NAME_MTX);
        auto cur = m_user_name_list.head;
        while (cur) {
            if (cur->name == username_) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    auto UserName::get_user_name(const std::string &username_) -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_NAME_MTX);
        auto cur = m_user_name_list.head;
        while (cur) {
            if (cur->name == username_) {
                return cur->name;
            }
            cur = cur->next;
        }
        return "";
    }

    auto UserName::add_user(const std::string &username_) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_NAME_MTX);
        auto cur = m_user_name_list.head;
        while (cur) {
            if (cur->name == username_) {
                return false;
            }
            cur = cur->next;
        }
        push_back(username_);
        return true;
    }

    void UserName::init() {
        std::lock_guard<std::mutex> lock(M_USER_NAME_MTX);
        if (m_init_once) {
            return;
        }
        m_init_once = true;
        std::string default_users[] = {"root", "live"};
        for (const auto &user : default_users) {
            push_back(user);
        }
    }

} // namespace ruac::usersystem
