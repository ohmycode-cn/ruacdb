/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/shext/ruac_upermission.hpp
 * src/shext/ruac_upermission.cpp
 */

#include "shext/ruac_upermission.hpp"
#include "system/user/ruac_users_map.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>
#include <unordered_map>

namespace ruac::shext::upermission {

    namespace {

        struct Colors {
            std::string m_red_background{""};
            std::string m_yel{""};
            std::string m_end{""};
        };

        auto inner_fmt(const std::string &power_code_, Colors colors_) -> std::string {
            if ("NO" == power_code_) {
                return colors_.m_red_background + colors_.m_yel + power_code_ + colors_.m_end;
            }
            return power_code_;
        }

    } // namespace

    void print_view(std::string user_name_, bool color_) {
        if (user_name_.empty()) {
            std::osyncstream(std::cout) << "Error: Invalid user name: '" << user_name_ << "'" << std::endl;
            return;
        };

        ruac::system::user::UsersMap ump;
        auto pmap = ump.get_users_map(std::move(user_name_));

        if (pmap.empty()) {
            std::string msg{"Info  : Current user not add any group, so it has no any permission."};
            std::osyncstream(std::cout) << std::move(msg) << std::endl;
            return;
        }

        auto &u = ruac::system::user::perm_code_str;

        Colors colors;
        if (color_) {
            colors.m_red_background = "\033[41m";
            colors.m_yel = "\033[33m";
            colors.m_end = "\033[0m";
        }

        std::stringstream ss;
        for (const auto &[group_name, power_code] : pmap) {
            ss << "Group: " << group_name << ", ";
            ss << "Power: [";
            ss << "R: " << u(power_code.rp) << ", ";
            ss << "W: " << u(power_code.wp) << ", ";
            ss << "X: " << u(power_code.xp) << ", ";
            ss << "L: " << u(power_code.lp) << ", ";
            ss << "S: " << inner_fmt(u(power_code.os), colors) << "]";
        }
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

} // namespace ruac::shext::upermission
