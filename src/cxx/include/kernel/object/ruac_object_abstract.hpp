/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/object/ruac_object_abstract.hpp
 * src/kernel/object/ruac_object_abstract.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_OBJECT_ABSTRACT_HPP
#define RUAC_OBJECT_ABSTRACT_HPP

#include "kernel/core/ruac_data.hpp"

namespace ruac::kernel::object {

    class ObjectAbstract {
      public:
        virtual ~ObjectAbstract() = default;

      public:
        virtual auto getdbs() -> std::vector<ruac::kernel::core::data::Database> & = 0;
    };

} // namespace ruac::kernel::object

#endif // RUAC_OBJECT_ABSTRACT_HPP
