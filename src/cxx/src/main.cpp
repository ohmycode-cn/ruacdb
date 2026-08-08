// #include "test/ruac_c_test_main.h"
// #include "test/ruac_test_main.hpp"
#include "kernel/object/ruac_object_single.hpp"
#include "kernel/ruac_controller_table.hpp"
#include "kernel/ruac_controller.hpp"
#include "kernel/state/ruac_state_single.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "ruac_shell_interaction.hpp"

int main() {
    // test_c_main();
    // ruac::test::test_main();

    auto controller = new ruac::kernel::controller::Operation();
    controller->setObjectStrategy(ruac::kernel::object::Single::obitan());
    controller->setStateStrategy(ruac::kernel::state::Single::obitan());
    controller->setTrackStrategy(ruac::kernel::track::Single::obitan());
    ruac::kernel::ControllerTable::instance().set_controller(0, *controller);

    auto shell_interaction = new ruac::ShellInteraction();
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
