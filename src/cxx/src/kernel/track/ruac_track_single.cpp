/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_single.hpp
 * Source File : src/kernel/track/ruac_track_single.cpp
 *
 * File Function Description:
 * Implementation file for ruac_track_single.hpp.
 *
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
    auto Single::obitan() -> Single & {
        static Single instance;
        return instance;
    }

    /**
     * @brief Gets the Kernel instance.
     * @return Reference to the Kernel object.
     */
    auto Single::getKernel() -> Kernel & {
        return *m_kernel;
    }

} // namespace ruac::kernel::track
