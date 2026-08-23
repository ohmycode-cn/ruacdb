/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/ruac_controller_pipes.hpp
 * src/kernel/ruac_controller_pipes.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_CONTROLLER_PIPES_HPP
#define RUAC_CONTROLLER_PIPES_HPP

#include "kernel/object/ruac_object_abstract.hpp"
#include "kernel/state/ruac_state_abstract.hpp"
#include "kernel/track/ruac_track_abstract.hpp"

#include <unordered_map>
#include <mutex>

namespace ruac::kernel::controller {

    struct ControllerPipeArgs {
        int uid;
        ruac::kernel::object::ObjectAbstract *m_object;
        ruac::kernel::state::StateAbstract *m_state;
        ruac::kernel::track::TrackAbstract *m_track;
    };

    class ControllerPipes final {
      private:
        std::mutex M_CONTROLLER_PIPES_MTX;
        bool m_once_lock{false};

      private:
        std::unordered_map<int, ruac::kernel::object::ObjectAbstract *> m_object;
        std::unordered_map<int, ruac::kernel::state::StateAbstract *> m_state;
        std::unordered_map<int, ruac::kernel::track::TrackAbstract *> m_track;

      private:
        template <typename T>
        auto append_pipes(int uid_, std::unordered_map<int, T> &pipe_) -> bool;

      public:
        ControllerPipes() = default;
        ~ControllerPipes() = default;
        ControllerPipes(const ControllerPipes &) = delete;
        ControllerPipes &operator=(const ControllerPipes &) = delete;

      public:
        static auto get() -> ControllerPipes &;
        void init_pipe(ControllerPipeArgs &args_);
        auto object(const int uid_) -> ruac::kernel::object::ObjectAbstract &;
        auto state(const int uid_) -> ruac::kernel::state::StateAbstract &;
        auto track(const int uid_) -> ruac::kernel::track::TrackAbstract &;
    };

    template <typename T>
    inline auto ControllerPipes::append_pipes(int uid_, std::unordered_map<int, T> &pipe_) -> bool {
        auto itr = pipe_.find(uid_);
        if (itr != pipe_.end()) {
            return false; // uid and pipe:{m_object/m_state/m_track} already exists
        }
        return true; // uid and pipe:{m_object/m_state/m_track} not exists
    }

} // namespace ruac::kernel::controller

#endif // RUAC_CONTROLLER_PIPES_HPP
