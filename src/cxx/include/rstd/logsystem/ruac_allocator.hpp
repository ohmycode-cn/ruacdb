/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_allocator.hpp
 * src/rstd/logsystem/ruac_allocator.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_ALLOCATOR_HPP
#define RUAC_ALLOCATOR_HPP

#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_loader.hpp"

namespace ruac::rstd::logsystem {

    struct AllocatorParamList {
        logenum::Output m_term_output{logenum::Output::CONSOLE};
        logenum::Output m_file_output{logenum::Output::CONSOLE};
        logenum::Format m_term_format{logenum::Format::TEXT};
        logenum::Format m_file_format{logenum::Format::TEXT};
        logenum::Level m_term_level{logenum::Level::DEBUG};
        logenum::Level m_file_level{logenum::Level::DEBUG};
        logenum::Level m_mini_level{logenum::Level::DEBUG};
        bool m_enable_ht{false};
        bool m_enable_bf{false};
        bool m_enable_ce{true};
    };

    class Allocator {
      private:
        logtype::string m_wf_path{""};
        logtype::string m_wf_name{""};
        logtype::string m_limit_f{""};

      private:
        AllocatorParamList m_param_list{};
        logtype::strmap m_default_map{};
        logtype::strmap m_loader_map{};
        logtype::strmap m_std_map{};
        logtype::string m_loader_msg{""};
        bool m_once_lock_guard{false};

      private:
        void parser_config_bool_value(
            logtype::strmap &map_, const logtype::string key_,
            bool &val_);
        void parser_config_output(
            logtype::strmap &map_, const logtype::string key_,
            logenum::Output &val_, bool isf_);
        void parser_config_format(
            logtype::strmap &map_, const logtype::string key_,
            logenum::Format &val_, bool isf_);
        void parser_config_log_level(
            logtype::strmap &map_, const logtype::string key_,
            logenum::Level &val_);

      private:
        void init_default_map();
        void parser_verify_configure_map();

      public:
        Allocator(const LoaderParamList &loader_param_list = {});
        ~Allocator() = default;

      public:
        auto get_param_list() -> AllocatorParamList;
        void out_loader_msg();
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_ALLOCATOR_HPP
