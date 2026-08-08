/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_username.hpp
 * src/usersystem/ruac_username.cpp
 */

#include "usersystem/ruac_username.hpp"

namespace ruac::usersystem {

    /**
     * @brief Access the singleton instance of UserName.
     *
     * @return UserName & - Reference to the static UserName instance.
     *
     * @details A function-local static object is constructed on first invocation and
     *          its reference is returned on every subsequent call, providing a
     *          thread-safe singleton accessor.
     *
     */
    auto UserName::instance() -> UserName & {
        static UserName instance_object;
        return instance_object;
    }

    /**
     * @brief Append a user name node to the tail of the user name list.
     *
     * @param name_ - User name to store in the new node.
     *
     * @details A new UserNameNode is allocated and linked at the tail of the
     *          doubly linked list. When the list is empty the node becomes both
     *          the head and the tail; otherwise the existing tail is linked to
     *          the new node before the tail pointer is advanced. The list size is
     *          incremented after insertion. This helper does not take the lock
     *          itself, callers are expected to guard concurrent access.
     *
     */
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

    /**
     * @brief Check whether a user name already exists in the list.
     *
     * @param username_ - User name to search for.
     *
     * @return bool - true if the user name is found; false otherwise.
     *
     * @details The mutex is locked before traversal and the linked list is
     *          walked from head to tail comparing each node name against the
     *          requested value.
     *
     */
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

    /**
     * @brief Retrieve the stored name for a given user name.
     *
     * @param username_ - User name to search for.
     *
     * @return std::string - The matched user name, or an empty string when the
     *         user is not found.
     *
     * @details The mutex is locked and the list is traversed node by node. When
     *          a matching name is located the stored name is returned; if the
     *          end of the list is reached an empty string is returned.
     *
     */
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

    /**
     * @brief Add a new user name if it is not already present.
     *
     * @param username_ - User name to add.
     *
     * @return bool - true if the user was added; false if the name already
     *                exists.
     *
     * @details The mutex is locked before traversing the list for duplicate
     *          detection. When a duplicate is found the call returns false
     *          without modifying the list; otherwise push_back is invoked to
     *          append the name and true is returned.
     *
     */
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

    /**
     * @brief Initialize the user name list with default users.
     *
     * @details The mutex is locked and the m_init_once guard is checked so the
     *          initialization runs only once across the lifetime of the
     *          singleton. On first invocation the guard is flipped and the
     *          default users "root" and "live" are appended via push_back.
     *
     */
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
