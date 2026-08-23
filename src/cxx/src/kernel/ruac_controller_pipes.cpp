/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/ruac_controller_pipes.hpp
 * src/kernel/ruac_controller_pipes.cpp
 */

#include "kernel/ruac_controller_pipes.hpp"
#include <mutex>

namespace ruac::kernel::controller {

    auto ControllerPipes::get() -> ControllerPipes & {
        static ControllerPipes instance;
        return instance;
    }

    void ControllerPipes::init_pipe(ControllerPipeArgs &args_) {
        std::lock_guard<std::mutex> lock(M_CONTROLLER_PIPES_MTX);

        if (m_once_lock) {
            return;
        }

        auto uid = args_.uid;

        if (!append_pipes(uid, m_object)) {
            m_object[uid] = args_.m_object;
        }
        if (!append_pipes(uid, m_state)) {
            m_state[uid] = args_.m_state;
        }
        if (!append_pipes(uid, m_track)) {
            m_track[uid] = args_.m_track;
        }

        m_once_lock = true;
    }

    auto ControllerPipes::object(const int uid_) -> ruac::kernel::object::ObjectAbstract & {
        return *m_object[uid_];
    }

    auto ControllerPipes::state(const int uid_) -> ruac::kernel::state::StateAbstract & {
        return *m_state[uid_];
    }

    auto ControllerPipes::track(const int uid_) -> ruac::kernel::track::TrackAbstract & {
        return *m_track[uid_];
    }

} // namespace ruac::kernel::controller
