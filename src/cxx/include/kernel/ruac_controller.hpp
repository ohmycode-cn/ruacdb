/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/ruac_controller.hpp
 * Source File : src/kernel/ruac_controller.cpp
 *
 * File Function Description:
 * Controller operation class that manages object, state, and track strategies.
 * Uses std::variant to hold different strategy types with proper ownership semantics.
 *
 */

#pragma once
#ifndef RUAC_CONTROLLER_HPP
#define RUAC_CONTROLLER_HPP

#include "kernel/state/ruac_state_multis.hpp"
#include "kernel/state/ruac_state_single.hpp"
#include "kernel/track/ruac_track_multis.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "kernel/object/ruac_object_multis.hpp"
#include "kernel/object/ruac_object_single.hpp"
#include <memory>
#include <variant>

namespace ruac::kernel::object {
    class Single;
    class Multis;
} // namespace ruac::kernel::object

namespace ruac::kernel::state {
    class Single;
    class Multis;
} // namespace ruac::kernel::state

namespace ruac::kernel::track {
    class Single;
    class Multis;
} // namespace ruac::kernel::track

namespace ruac::kernel {

    namespace defname {
        using objs = ruac::kernel::object::Single;
        using objm = ruac::kernel::object::Multis;
        using stas = ruac::kernel::state::Single;
        using stam = ruac::kernel::state::Multis;
        using tras = ruac::kernel::track::Single;
        using tram = ruac::kernel::track::Multis;
    } // namespace defname

    namespace controller {

        /**
         * @brief Controller operation managing object, state, and track strategies.
         */
        class Operation {
          private:
            std::variant<defname::objs *, std::unique_ptr<defname::objm>> m_object_strategy;
            std::variant<defname::stas *, std::unique_ptr<defname::stam>> m_state_strategy;
            std::variant<defname::tras *, std::unique_ptr<defname::tram>> m_track_strategy;

          public:
            Operation();
            ~Operation();

          public:
            void setObjectStrategy(defname::objs &single_);
            void setObjectStrategy(std::unique_ptr<defname::objm> multis_);
            auto getObjectStrategy() -> std::variant<defname::objs *, std::unique_ptr<defname::objm>> &;

            void setStateStrategy(defname::stas &state_single_);
            void setStateStrategy(std::unique_ptr<defname::stam> state_multis_);
            auto getStateStrategy() -> std::variant<defname::stas *, std::unique_ptr<defname::stam>> &;

            void setTrackStrategy(defname::tras &track_single_);
            void setTrackStrategy(std::unique_ptr<defname::tram> track_multis_);
            auto getTrackStrategy() -> std::variant<defname::tras *, std::unique_ptr<defname::tram>> &;
        }; // Operation
    } // namespace controller

} // namespace ruac::kernel

#endif // RUAC_CONTROLLER_HPP
