// #include "test/ruac_c_test_main.h"
#include "test/ruac_test_main.hpp"
#include "ruac_shell_interaction.hpp"

int main() {
    // test_c_main();
    ruac::test::test_main();

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
