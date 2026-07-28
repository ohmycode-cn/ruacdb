// #include "test/ruac_c_test_main.h"
// #include "test/ruac_test_main.hpp"
#include "ruac_interaction.hpp"

int main(void) {
    // test_c_main();
    // ruac::test::test_main();

    auto interaction = new ruac::Interaction();
    interaction->init({
        .m_enable_ce = true,
        .m_enable_ht = true,
        .m_enable_bf = false,
        .m_enable_dp = true,
    });
    auto end = interaction->run();
    if (end && nullptr != interaction) {
        delete interaction;
        interaction = nullptr;
    }
}
