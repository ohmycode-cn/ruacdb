/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/lib/ruac_name_node.hpp
 * src/system/user/lib/ruac_name_node.cpp
 *
 * @brief Doubly-linked list node and list structures for UserName management.
 */

#pragma once
#ifndef RUAC_NAME_NODE_HPP
#define RUAC_NAME_NODE_HPP

#include <memory>
#include <string>

namespace ruac::system::user::lib {

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

} // namespace ruac::system::user::lib

#endif // RUAC_NAME_NODE_HPP
