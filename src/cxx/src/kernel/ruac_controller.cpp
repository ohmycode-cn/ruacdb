/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/ruac_controller.hpp
 * Source File : src/kernel/ruac_controller.cpp
 *
 * File Function Description:
 * Implementation file for ruac_controller.hpp.
 *
 */

#include "kernel/ruac_controller.hpp"

namespace ruac::kernel {

    namespace defname {
        // Null Implementation.
    } // namespace defname

    namespace controller {

        /**
         * Default constructor for Operation.
         */
        Operation::Operation() = default;

        /**
         * Default destructor for Operation.
         */
        Operation::~Operation() = default;

        /**
         * Sets the object strategy with a Single reference.
         *
         * Args:
         *   single_: Reference to the Single singleton.
         */
        void Operation::setObjectStrategy(defname::objs &single_) {
            m_object_strategy = &single_;
        }

        /**
         * Sets the object strategy with a Multis unique pointer.
         *
         * Args:
         *   multis_: Unique pointer to the Multis instance.
         */
        void Operation::setObjectStrategy(std::unique_ptr<defname::objm> multis_) {
            m_object_strategy = std::move(multis_);
        }

        /**
         * Gets the object strategy variant.
         *
         * Returns:
         *   Reference to the object strategy variant.
         */
        auto Operation::getObjectStrategy() -> std::variant<defname::objs *, std::unique_ptr<defname::objm>> & {
            return m_object_strategy;
        }

        /**
         * Sets the state strategy with a Single reference.
         *
         * Args:
         *   state_single_: Reference to the state Single singleton.
         */
        void Operation::setStateStrategy(defname::stas &state_single_) {
            m_state_strategy = &state_single_;
        }

        /**
         * Sets the state strategy with a Multis unique pointer.
         *
         * Args:
         *   state_multis_: Unique pointer to the state Multis instance.
         */
        void Operation::setStateStrategy(std::unique_ptr<defname::stam> state_multis_) {
            m_state_strategy = std::move(state_multis_);
        }

        /**
         * Gets the state strategy variant.
         *
         * Returns:
         *   Reference to the state strategy variant.
         */
        auto Operation::getStateStrategy() -> std::variant<defname::stas *, std::unique_ptr<defname::stam>> & {
            return m_state_strategy;
        }

        /**
         * Sets the track strategy with a Single reference.
         *
         * Args:
         *   track_single_: Reference to the track Single singleton.
         */
        void Operation::setTrackStrategy(defname::tras &track_single_) {
            m_track_strategy = &track_single_;
        }

        /**
         * Sets the track strategy with a Multis unique pointer.
         *
         * Args:
         *   track_multis_: Unique pointer to the track Multis instance.
         */
        void Operation::setTrackStrategy(std::unique_ptr<defname::tram> track_multis_) {
            m_track_strategy = std::move(track_multis_);
        }

        /**
         * Gets the track strategy variant.
         *
         * Returns:
         *   Reference to the track strategy variant.
         */
        auto Operation::getTrackStrategy() -> std::variant<defname::tras *, std::unique_ptr<defname::tram>> & {
            return m_track_strategy;
        }

    } // namespace controller

} // namespace ruac::kernel
