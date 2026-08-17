/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/share/ruac_userlist.hpp
 * src/share/ruac_userlist.cpp
 */

#include "share/ruac_userlist.hpp"
#include <mutex>

namespace ruac::share {

    /**
     * @brief Access the singleton UserList instance
     *
     * @return UserList & - Reference to the single shared instance
     *
     * @details Returns a function-local static UserList so that the
     *          instance is created on first use and destroyed at program
     *          exit.
     *
     */
    auto UserList::instance() -> UserList & {
        static UserList instance_object;
        return instance_object;
    }

    /**
     * @brief Return the sentinel string used for absent users
     *
     * @return std::string - The null-user sentinel value stored in M_NULL_USER
     *
     * @details Acquires M_USER_LIST_MTX and returns the constant M_NULL_USER
     *          so callers can compare lookup results against the same
     *          sentinel used internally by get_une().
     *
     */
    auto UserList::get_null_user() const -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_LIST_MTX);
        return M_NULL_USER;
    }

    /**
     * @brief Register a uid-to-username mapping
     *
     * @param uid_ - The user ID to register
     * @param uname_ - The username to associate with the uid
     *
     * @details Acquires M_USER_LIST_MTX and inserts the pair only if uid_
     *          is not already present in m_umap; existing entries are left
     *          untouched.
     *
     */
    void UserList::add_map(const int uid_, const std::string &uname_) {
        std::lock_guard<std::mutex> lock(M_USER_LIST_MTX);
        auto itr{m_umap.find(uid_)};
        if (itr == m_umap.end()) {
            m_umap[uid_] = uname_;
        }
    }

    /**
     * @brief Look up the uid associated with a username
     *
     * @param uname_ - The username to search for
     *
     * @return int - The matching uid, or -1 if the username is not found
     *
     * @details Acquires M_USER_LIST_MTX and linearly scans m_umap for an
     *          entry whose value equals uname_; returns the key on the
     *          first match.
     *
     */
    auto UserList::get_uid(const std::string &uname_) const -> int {
        std::lock_guard<std::mutex> lock(M_USER_LIST_MTX);
        for (const auto &item : m_umap) {
            if (item.second == uname_) {
                return item.first;
            }
        }
        return -1;
    }

    /**
     * @brief Look up the username associated with a uid
     *
     * @param uid_ - The user ID to search for
     *
     * @return std::string - The matching username, or "nouser" if the
     *         uid is not found
     *
     * @details Acquires M_USER_LIST_MTX and performs an O(log n) lookup
     *          on m_umap; returns the mapped value or "nouser" when the
     *          key is absent.
     *
     */
    auto UserList::get_une(const int uid_) const -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_LIST_MTX);
        auto itr{m_umap.find(uid_)};
        if (itr != m_umap.end()) {
            return itr->second;
        }
        return M_NULL_USER;
    }

} // namespace ruac::share
