/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/state/ruac_state_abstract.hpp
 * src/kernel/state/ruac_state_abstract.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_STATE_ABSTRACT_HPP
#define RUAC_STATE_ABSTRACT_HPP

#include "kernel/state/ruac_state_kernel.hpp"

namespace ruac::kernel::state {

    class StateAbstract {
      public:
        virtual ~StateAbstract() = default;

      public:
        virtual auto get_kernel_state() -> Kernel & = 0;
    };

} // namespace ruac::kernel::state

#endif // RUAC_STATE_ABSTRACT_HPP
