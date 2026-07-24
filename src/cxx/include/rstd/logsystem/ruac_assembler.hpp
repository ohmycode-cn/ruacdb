/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_assembler.hpp
 * src/rstd/logsystem/ruac_assembler.cpp
 * Description of header file function declaration
 * Log pipeline assembler that reads configuration via Allocator, creates and
 * owns terminal/file Output and Format pairs, and destroys them on teardown.
 *
 */

#pragma once
#ifndef RUAC_ASSEMBLER_HPP
#define RUAC_ASSEMBLER_HPP

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_output.hpp"
#include "rstd/logsystem/ruac_format.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * @brief Holds a paired Output and Format pointer for one sink channel
         *
         */
        struct SinkPair {
            Output *m_output{nullptr};
            Format *m_format{nullptr};
        };

    } // namespace

    /**
     * @brief Contains terminal and file sink pairs forming the complete log output pipeline
     *
     */
    struct SinkPipeline {
        SinkPair m_term_sink_pair{};
        SinkPair m_file_sink_pair{};
    };

    /**
     * @brief Assembles the log pipeline from configuration. Loads settings via
     *        Allocator, resolves enums, creates Output/Format objects for both
     *        terminal and file channels, and destroys them on teardown.
     *
     */
    class Assembler {
      private:
        logenum::Output m_output_mode{logenum::Output::CONSOLE};
        logenum::Format m_term_format{logenum::Format::TEXT};
        logenum::Format m_file_format{logenum::Format::TEXT};
        logenum::Level m_term_level{logenum::Level::DEBUG};
        logenum::Level m_file_level{logenum::Level::DEBUG};
        logenum::Level m_min_level{logenum::Level::DEBUG};

      private:
        Allocator m_allocator{Allocator()};
        SinkPipeline m_sink_pipeline{};
        logtype::StringMap m_map{};
        logtype::Bool m_once_lock{false};

      private:
        void inner_load_member_config();
        void inner_resolve_format_enum(logenum::Format &fmt_, logtype::StringMap &map_, const logtype::String &key_);
        void inner_resolve_log_level(logenum::Level &level_, logtype::StringMap &map_, const logtype::String &key_);
        void inner_create_output(Output *&ptr_output_, logenum::Output &enm_out_, logtype::Bool is_file_);
        void inner_create_format(Format *&ptr_fmt_, logenum::Format &enm_fmt_);
        void inner_destroy_output(Output *&ptr_out_);
        void inner_destroy_format(Format *&ptr_fmt_);

      private:
        void build();
        void endof();

      public:
        Assembler() = default;
        ~Assembler();

      public:
        auto get_allocator_obj() -> Allocator &;
        auto get_sink_pipeline() -> SinkPipeline &;
        auto get_map() -> logtype::StringMap;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_ASSEMBLER_HPP
