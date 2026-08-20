/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/ruac_controller.hpp
 * src/kernel/ruac_controller.cpp
 */

#include "kernel/ruac_controller.hpp"

namespace ruac::kernel {

    namespace defname {
        // Null Implementation.
    } // namespace defname

    namespace controller {

        /**
         * @brief Default constructor for Operation.
         *
         */
        Operation::Operation() = default;

        /**
         * @brief Default destructor for Operation.
         *
         */
        Operation::~Operation() = default;

        /**
         * @brief Sets the object strategy with a Single reference.
         *
         * @param single_ - Reference to the Single singleton.
         *
         */
        void Operation::set_object_strategy(defname::objs &single_) {
            m_object_strategy = &single_;
        }

        /**
         * @brief Sets the object strategy with a Multis unique pointer.
         *
         * @param multis_ - Unique pointer to the Multis instance.
         *
         */
        void Operation::set_object_strategy(std::unique_ptr<defname::objm> multis_) {
            m_object_strategy = std::move(multis_);
        }

        /**
         * @brief Gets the object strategy variant.
         *
         * @return std::variant<defname::objs *, std::unique_ptr<defname::objm>> & - Reference to the object strategy variant.
         *
         */
        auto Operation::get_object_strategy() -> std::variant<defname::objs *, std::unique_ptr<defname::objm>> & {
            return m_object_strategy;
        }

        /**
         * @brief Sets the state strategy with a Single reference.
         *
         * @param state_single_ - Reference to the state Single singleton.
         *
         */
        void Operation::set_state_strategy(defname::stas &state_single_) {
            m_state_strategy = &state_single_;
        }

        /**
         * @brief Sets the state strategy with a Multis unique pointer.
         *
         * @param state_multis_ - Unique pointer to the state Multis instance.
         *
         */
        void Operation::set_state_strategy(std::unique_ptr<defname::stam> state_multis_) {
            m_state_strategy = std::move(state_multis_);
        }

        /**
         * @brief Gets the state strategy variant.
         *
         * @return std::variant<defname::stas *, std::unique_ptr<defname::stam>> & - Reference to the state strategy variant.
         *
         */
        auto Operation::get_state_strategy() -> std::variant<defname::stas *, std::unique_ptr<defname::stam>> & {
            return m_state_strategy;
        }

        /**
         * @brief Sets the track strategy with a Single reference.
         *
         * @param track_single_ - Reference to the track Single singleton.
         *
         */
        void Operation::set_track_strategy(defname::tras &track_single_) {
            m_track_strategy = &track_single_;
        }

        /**
         * @brief Sets the track strategy with a Multis unique pointer.
         *
         * @param track_multis_ - Unique pointer to the track Multis instance.
         *
         */
        void Operation::set_track_strategy(std::unique_ptr<defname::tram> track_multis_) {
            m_track_strategy = std::move(track_multis_);
        }

        /**
         * @brief Gets the track strategy variant.
         *
         * @return std::variant<defname::tras *, std::unique_ptr<defname::tram>> & - Reference to the track strategy variant.
         *
         */
        auto Operation::get_track_strategy() -> std::variant<defname::tras *, std::unique_ptr<defname::tram>> & {
            return m_track_strategy;
        }

    } // namespace controller

} // namespace ruac::kernel
