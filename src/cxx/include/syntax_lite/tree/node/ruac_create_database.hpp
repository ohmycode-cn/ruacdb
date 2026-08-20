/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_database.hpp
 * src/syntax_lite/tree/node/ruac_create_database.cpp
 *
 * @brief Defines the CreateDatabase class for creating databases with existence checking and thread-safe access.
 */

#pragma once
#ifndef RUAC_CREATE_DATABASE_HPP
#define RUAC_CREATE_DATABASE_HPP

#include <mutex>
#include <string>

namespace ruac::syntax_lite::tree::node {

    class CreateDatabase {
      private:
        std::mutex M_CREATE_DATABASE_MTX;
        [[maybe_unused]] int m_uid{1};

      private:
        auto exist_database(const std::string &name_) -> bool;
        void create_database(const std::string &name_, bool in_advance_check_ = false);

      public:
        explicit CreateDatabase(int uid_ = 1);
        ~CreateDatabase() = default;

      public:
        void execute(const std::string &name_, bool in_advance_check_ = false);
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_CREATE_DATABASE_HPP
