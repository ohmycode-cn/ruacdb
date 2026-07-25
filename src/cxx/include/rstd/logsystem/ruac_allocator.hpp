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
#include "rstd/logsystem/ruac_logtype.hpp"
#ifndef RUAC_ALLOCATOR_HPP
#define RUAC_ALLOCATOR_HPP

#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_output.hpp"
#include "rstd/logsystem/ruac_format.hpp"
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

    namespace {
        struct SinkPair {
            Output *m_output_{nullptr};
            Format *m_format_{nullptr};
        };
    } // namespace

    struct AllocatorSinkPipeline {
        SinkPair m_term_sink;
        SinkPair m_file_sink;
    };

    class Allocator {
      private:
        AllocatorSinkPipeline m_sink_pipeline{};
        AllocatorParamList m_param_list{};
        logtype::strmap m_default_map{};
        logtype::strmap m_loader_map{};
        logtype::string m_loader_msg{""};

      private:
        void init_default_map();

      public:
        Allocator(const LoaderParamList &loader_param_list = {});
        ~Allocator() = default;

      public:
        auto get_sink_pipeline() -> AllocatorSinkPipeline &;
        auto get_param_list() -> AllocatorParamList;
        void out_loader_msg();
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_ALLOCATOR_HPP
