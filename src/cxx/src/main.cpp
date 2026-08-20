/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * src/main.cpp
 */

// #include "test/ruac_c_test_main.h"
// #include "test/ruac_test_main.hpp"
#include "kernel/object/ruac_object_single.hpp"
#include "kernel/ruac_controller.hpp"
#include "kernel/ruac_controller_table.hpp"
#include "kernel/state/ruac_state_single.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "login/ruac_login_user.hpp"
#include "rshell/lib/ruac_args.hpp"
#include "rshell/ruac_rshell.hpp"

/**
 * @brief Program entry point
 *
 * @return int - Process exit status (implicit 0 on normal completion)
 *
 * @details Creates a heap-allocated Operation controller and configures its
 *          object, state, and track strategies to the Single singleton (via
 *          instance()). Creates a LoginUser, configures it with LoginMethod::OTHER,
 *          and calls init_login() to set up the default root user. Registers
 *          the controller into ControllerTable at the user's uid, then retrieves
 *          it and sets the kernel state's current user. Deletes the LoginUser
 *          once the uid and name are propagated. Finally constructs a
 *          rshell::api::RShell with the kernel state, sets runtime args
 *          (ce=true, ht=true, bf=false, dp=true), and calls run() to
 *          start the interactive shell.
 *
 */
int main() {
    // test_c_main();
    // ruac::test::test_main();

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

    {
        ruac::rshell::lib::args::ShellArgs ruac_shell_args{
            .m_enable_ce = true,
            .m_enable_ht = true,
            .m_enable_bf = false,
            .m_enable_dp = true,
        };
        ruac::rshell::api::RShell ruac_shell(state->get_kernel_state());
        ruac_shell.set_args(ruac_shell_args);
        ruac_shell.run(true);
    }
}
