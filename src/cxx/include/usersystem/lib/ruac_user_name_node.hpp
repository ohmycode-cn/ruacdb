/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/lib/ruac_user_name_node.hpp
 * src/usersystem/lib/ruac_user_name_node.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_USER_NAME_NODE_HPP
#define RUAC_USER_NAME_NODE_HPP

#include <memory>
#include <string>

namespace ruac::usersystem::lib {

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

} // namespace ruac::usersystem::lib

#endif // RUAC_USER_NAME_NODE_HPP
