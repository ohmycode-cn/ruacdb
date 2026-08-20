/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/track/ruac_track_single.hpp
 * src/kernel/track/ruac_track_single.cpp
 */

#include "kernel/track/ruac_track_single.hpp"

namespace ruac::kernel::track {

    /**
     * @brief Constructs a Single object and initializes resources.
     */
    Single::Single() {
        init();
    }

    /**
     * @brief Destroys the Single object and cleans up resources.
     */
    Single::~Single() {
        over();
    }

    /**
     * @brief Initializes the Single object.
     */
    void Single::init() {
        if (nullptr == m_kernel) {
            m_kernel = new Kernel();
        }
    }

    /**
     * @brief Cleans up the Kernel object.
     */
    void Single::over() {
        if (nullptr != m_kernel) {
            delete m_kernel;
            m_kernel = nullptr;
        }
    }

    /**
     * @brief Gets the singleton instance of Single.
     * @return Reference to the single Single instance.
     */
    auto Single::instance() -> Single & {
        static Single instance;
        return instance;
    }

    /**
     * @brief Gets the Kernel instance.
     * @return Reference to the Kernel object.
     */
    auto Single::get_kernel() -> Kernel & {
        return *m_kernel;
    }

} // namespace ruac::kernel::track
