/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/util/ruac_exists_table.hpp
 * src/syntax_lite/tree/node/util/ruac_exists_table.cpp
 */

#include "kernel/ruac_controller_pipes.hpp"
#include "syntax_lite/tree/node/util/ruac_exists_table.hpp"

namespace ruac::syntax_lite::tree::node::util {

    auto exist_table(const std::string &dbname_, const std::string &tbname_, const int uid_) -> bool {
        auto &track = ruac::kernel::controller::ControllerPipes::get().track(uid_);
        return track.get_kernel().exist_table(dbname_, tbname_);
    }

} // namespace ruac::syntax_lite::tree::node::util
