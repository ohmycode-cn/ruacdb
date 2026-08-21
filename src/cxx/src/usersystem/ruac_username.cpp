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
    void UserName::push_back(const std::string &name_) {
        auto node = std::make_shared<lib::UserNameNode>();
        node->name = name_;
        if (!m_user_name_list->head) {
            m_user_name_list->head = node;
            m_user_name_list->tail = node;
        } else {
            node->prev = m_user_name_list->tail;
            m_user_name_list->tail->next = node;
            m_user_name_list->tail = node;
        }
        m_user_name_list->size++;
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
        auto cur = m_user_name_list->head;
        while (cur) {
            if (cur->name == username_) {
                return false;
            }
            cur = cur->next;
        }
        push_back(username_);
        return true;
    }

} // namespace ruac::usersystem
