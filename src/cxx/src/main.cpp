/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * src/main.cpp
 */

// #include "test/ruac_c_test_main.h"
#include "test/ruac_test_main.hpp"
#include "kernel/object/ruac_object_single.hpp"
#include "kernel/ruac_controller.hpp"
#include "kernel/ruac_controller_table.hpp"
#include "kernel/state/ruac_state_single.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "ruac_shell_interaction.hpp"
#include "login/ruac_login_user.hpp"

/**
 * @brief Program entry point
 *
 * @return int - Process exit status (implicit 0 on normal completion)
 *
 * @details Creates a heap-allocated Operation controller and configures its
 *          object, state, and track strategies to the Single singleton (via
 *          instance()), then registers it into ControllerTable at index 0.
 *          Next constructs a ShellInteraction, initializes it with the
 *          runtime config flags (ce=true, ht=true, bf=false, dp=true), and
 *          invokes run() to start the interactive shell. When run() returns
 *          true the ShellInteraction is deleted and its pointer nullified;
 *          the controller remains registered in ControllerTable. Relies on
 *          main's implicit return 0 when run() completes.
 *
 */
int main() {
    // test_c_main();
    ruac::test::test_main();

    auto controller = new ruac::kernel::controller::Operation();
    controller->set_object_strategy(ruac::kernel::object::Single::instance());
    controller->set_state_strategy(ruac::kernel::state::Single::instance());
    controller->set_track_strategy(ruac::kernel::track::Single::instance());
    ruac::login::LoginUser *lu = new ruac::login::LoginUser();
    lu->conf_login(ruac::login::LoginMethod::OTHER);
    lu->init_login();
    ruac::kernel::controller::ControllerTable::instance().set_controller(lu->get_uid(), *controller);
    auto &ctr = ruac::kernel::controller::ControllerTable::instance().get_controller(lu->get_uid());
    auto *state = std::get<ruac::kernel::state::Single *>(ctr.get_state_strategy());
    state->get_kernel_state().set_current_user(lu->get_uname(), lu->get_uid());
    if (nullptr != lu) {
        delete lu;
        lu = nullptr;
    }

    auto shell_interaction = new ruac::ShellInteraction(state->get_kernel_state());
    shell_interaction->init({
        .m_enable_ce = true,
        .m_enable_ht = true,
        .m_enable_bf = false,
        .m_enable_dp = true,
    });

    if (const auto end = shell_interaction->run(); end && nullptr != shell_interaction) {
        delete shell_interaction;
        shell_interaction = nullptr;
    }
}
