/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_manager.hpp
 * src/rstd/logsystem/ruac_manager.cpp
 * Description of header file function declaration
 *
 * Defines the Manager class that orchestrates log system initialization, configuration, and message routing
 *
 */

#pragma once

#ifndef RUAC_MANAGER_HPP
#define RUAC_MANAGER_HPP

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logmaps.hpp"
#include "rstd/logsystem/ruac_format.hpp"
#include "rstd/logsystem/ruac_output.hpp"
#include <memory>

namespace ruac::rstd::logsystem {

    struct SinkPair {
        Output *m_output_{nullptr};
        Format *m_format_{nullptr};
    };

    struct SinkPipeline {
        SinkPair m_term_sink;
        SinkPair m_file_sink;
    };

    class Manager {
      private:
        logtype::strmap m_text_level_map{logmaps::get_text_level_map()};
        logtype::strmap m_ansi_level_map{logmaps::get_ansi_level_map()};
        logtype::strmap m_text_token_map{logmaps::get_text_map()};
        logtype::strmap m_ansi_token_map;

      private:
        // bool m_guard_marker{false};
        std::unique_ptr<Allocator> m_allocator{nullptr};
        AllocatorParamList m_allocator_list{};
        SinkPipeline m_sink_pipeline{};
        logtype::string m_wf_path;
        logtype::string m_wf_name;

      private:
        logenum::Level m_term_level;
        logenum::Level m_file_level;
        logenum::Level m_mini_level;
        bool m_enable_ht{};
        bool m_enable_bf{};
        bool m_enable_ce{};

      private:
        void increment(logtype::seqnum &sequence_);
        logtype::seqnum m_seq_debug{0};
        logtype::seqnum m_seq_info{0};
        logtype::seqnum m_seq_warning{0};
        logtype::seqnum m_seq_error{0};
        logtype::seqnum m_seq_fatal{0};

      private:
        void create_sink_output(Output *&out_, const logenum::Output &enum_out_);
        void create_sink_format(Format *&fmt_, const logenum::Format &enum_fmt_);
        void delete_sink_output(Output *&out_);
        void delete_sink_format(Format *&fmt_);

      private:
        void init_sink_pipeline(const AllocatorParamList &params_);
        void over_sink_pipeline();

        void out_stream(Format *&format_, Output *&output_, const logtype::strmap &strmap_,
                        const logtype::string &level_, const logtype::seqnum &sequence_,
                        const logtype::string &message_, const logtype::string &file_, logtype::sd_int line_);

      public:
        Manager() = default;
        ~Manager();

      public:
        void init(const LoaderParamList &params_ = {});
        void write(logenum::Level level_, const logtype::string &message_, const logtype::string &file_,
                   logtype::sd_int line_);
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_MANAGER_HPP
