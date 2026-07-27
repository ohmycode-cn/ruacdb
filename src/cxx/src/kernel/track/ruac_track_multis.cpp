/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_multis.hpp
 * Source File : src/kernel/track/ruac_track_multis.cpp
 *
 * File Function Description:
 * Implementation file for ruac_track_multis.hpp.
 *
 */

#include "kernel/track/ruac_track_multis.hpp"

namespace ruac::kernel::track {

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
    auto Multis::getKernel() -> Kernel & {
        return *m_kernel;
    }

} // namespace ruac::kernel::track
