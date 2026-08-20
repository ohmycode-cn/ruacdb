/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/state/ruac_state_multis.hpp
 * src/kernel/state/ruac_state_multis.cpp
 */

#include "kernel/state/ruac_state_multis.hpp"

namespace ruac::kernel::state {

    /**
     * @brief Initializes the Multis object.
     */
    void Multis::init() {
        if (nullptr == m_kernel) {
            m_kernel = new Kernel();
        }
    }

    /**
     * @brief Cleans up the Kernel object.
     */
    void Multis::over() {
        if (nullptr != m_kernel) {
            delete m_kernel;
            m_kernel = nullptr;
        }
    }

    /**
     * @brief Constructs a Multis object and initializes resources.
     */
    Multis::Multis() {
        init();
    }

    /**
     * @brief Destroys the Multis object and cleans up resources.
     */
    Multis::~Multis() {
        over();
    }

    /**
     * @brief Gets the Kernel instance.
     * @return Reference to the Kernel object.
     */
    auto Multis::get_kernel_state() -> Kernel & {
        return *m_kernel;
    }

} // namespace ruac::kernel::state
