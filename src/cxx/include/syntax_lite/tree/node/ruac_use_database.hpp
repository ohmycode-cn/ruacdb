/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_use_database.hpp
 * src/syntax_lite/tree/node/ruac_use_database.cpp
 *
 * @brief Defines the UseDatabase class as a stub for database selection node processing.
 */

#pragma once
#ifndef RUAC_USE_DATABASE_HPP
#define RUAC_USE_DATABASE_HPP

namespace ruac::syntax_lite::tree::node {

    class UseDatabase {
      private:
        int m_uid{1};

      public:
        explicit UseDatabase(int uid = 1);
        ~UseDatabase() = default;
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_USE_DATABASE_HPP
