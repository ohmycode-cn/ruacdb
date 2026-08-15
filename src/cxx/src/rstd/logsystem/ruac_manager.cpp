/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_manager.hpp
 * src/rstd/logsystem/ruac_manager.cpp
 */

#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_manager.hpp"
#include "rstd/logsystem/ruac_output_console.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"

namespace ruac::rstd::logsystem {

    namespace {

        namespace k = logkeys::token_k;

    }; // namespace

    /**
     * @brief Increment the sequence number
     *
     * @param sequence_ - Reference to the sequence number to increment
     *
     * @details Increments the provided sequence number by one. Used to track
     *          log message sequence for different log levels.
     *
     */
    void Manager::increment(logtype::seqnum &sequence_) {
        sequence_++;
    }

    /**
     * @brief Create a sink output object based on output type
     *
     * @param out_ - Reference to unique_ptr where the output object will be stored
     * @param enum_out_ - Output type enum specifying FILE or CONSOLE (const ref)
     *
     * @details Creates a new OutputFile or OutputConsole instance based on
     *          enum_out_. Does nothing if out_ is already not null. Uses
     *          m_wf_path and m_wf_name for file output configuration.
     *
     */
    void Manager::create_sink_output(std::unique_ptr<Output> &out_, const logenum::Output &enum_out_) {
        if (nullptr != out_) {
            return;
        }
        switch (enum_out_) {
        case logenum::Output::FILE:
            out_ = std::make_unique<OutputFile>(m_wf_path, m_wf_name, true);
            break;
        case logenum::Output::CONSOLE:
            out_ = std::make_unique<OutputConsole>();
            break;
        }
    }

    /**
     * @brief Create a sink format object based on format type
     *
     * @param fmt_ - Reference to unique_ptr where the format object will be stored
     * @param enum_fmt_ - Format type enum specifying JSON, TEXT, or XML (const ref)
     *
     * @details Creates a new FormatJson, FormatText, or FormatXML instance based
     *          on enum_fmt_. Does nothing if fmt_ is already not null.
     *
     */
    void Manager::create_sink_format(std::unique_ptr<Format> &fmt_, const logenum::Format &enum_fmt_) {
        if (nullptr != fmt_) {
            return;
        }
        switch (enum_fmt_) {
        case logenum::Format::JSON:
            fmt_ = std::make_unique<FormatJson>();
            break;
        case logenum::Format::TEXT:
            fmt_ = std::make_unique<FormatText>();
            break;
        case logenum::Format::XML:
            fmt_ = std::make_unique<FormatXML>();
            break;
        }
    }

    /**
     * @brief Initialize the sink pipeline with output and format objects
     *
     * @param params_ - Allocator parameter list containing configuration
     *
     * @details Sets m_wf_path and m_wf_name from params_, then creates output
     *          and format objects for both file and terminal sinks by calling
     *          create_sink_output and create_sink_format with the parameter values.
     *
     */
    void Manager::init_sink_pipeline(const AllocatorParamList &params_) {
        m_wf_path = params_.m_wf_path;
        m_wf_name = params_.m_wf_name;
        create_sink_output(m_sink_pipeline.m_file_sink.m_output_, params_.m_file_output);
        create_sink_output(m_sink_pipeline.m_term_sink.m_output_, params_.m_term_output);
        create_sink_format(m_sink_pipeline.m_file_sink.m_format_, params_.m_file_format);
        create_sink_format(m_sink_pipeline.m_term_sink.m_format_, params_.m_term_format);
    }

    /**
     * @brief Output a formatted log message to the specified output sink
     *
     * @param format_ - Reference to unique_ptr of Format object for message formatting
     * @param output_ - Reference to unique_ptr of Output object for message output
     * @param strmap_ - Token map containing format tokens and their values
     * @param level_ - Log level string (plain-text or ANSI-colored)
     * @param sequence_ - Sequence number for this log message
     * @param message_ - The log message content
     * @param file_ - Source file name where the log was generated
     * @param line_ - Source line number where the log was generated
     *
     * @details Gets the current timestamp via logtime::get_time(), formats the
     *          message using format_->format() with the provided parameters,
     *          then writes it via output_->output(). Does nothing if format_
     *          or output_ is null.
     *
     */
    void Manager::out_stream(std::unique_ptr<Format> &format_,
                             std::unique_ptr<Output> &output_,
                             const logtype::strmap &strmap_,
                             const logtype::string &level_,
                             const logtype::seqnum &sequence_,
                             const logtype::string &message_,
                             const logtype::string &file_,
                             logtype::sd_int line_) {

        if (nullptr == format_ || nullptr == output_) {
            return;
        }
        auto time = logtime::get_time();
        auto strs = format_->format(strmap_, time, level_, sequence_, message_, file_, line_);
        output_->output(strs);
    }

    /**
     * @brief Initialize the Manager with loader parameters
     *
     * @param params_ - Loader parameter list for initial configuration
     *
     * @details Creates an Allocator instance from loader parameters, extracts
     *          configuration values (log levels, color flags), initializes the
     *          sink pipeline via init_sink_pipeline(), and builds the ANSI token
     *          map for colored terminal output.
     *
     */
    void Manager::init(const LoaderParamList &params_) {
        m_allocator = std::make_unique<Allocator>(params_);
        m_allocator_list = m_allocator->get_param_list();
        m_mini_level = m_allocator_list.m_mini_level;
        m_term_level = m_allocator_list.m_term_level;
        m_file_level = m_allocator_list.m_file_level;
        m_enable_ht = m_allocator_list.m_enable_ht;
        m_enable_bf = m_allocator_list.m_enable_bf;
        m_enable_ce = m_allocator_list.m_enable_ce;
        init_sink_pipeline(m_allocator_list);
        m_ansi_token_map = logmaps::get_ansi_map(m_enable_ce, m_enable_ht,
                                                 m_enable_bf);
    }

    /**
     * @brief Write a log message with specified level
     *
     * @param level_ - Log level enum (DEBUG, INFO, WARNING, ERROR, FATAL)
     * @param message_ - The log message content
     * @param file_ - Source file name where the log was generated
     * @param line_ - Source line number where the log was generated
     *
     * @details Core logging function that filters and routes log messages.
     *          First checks if level is below m_mini_level and returns early
     *          if so. Uses a switch statement to select ANSI-colored level
     *          strings for terminal output and plain-text level strings for
     *          file output, along with per-level sequence counters. Increments
     *          the appropriate sequence counter. Outputs to terminal if level
     *          >= m_term_level using the ANSI token map, and to file if level
     *          >= m_file_level using the plain-text token map.
     *
     */
    void Manager::write(logenum::Level level_,
                        const logtype::string &message_,
                        const logtype::string &file_,
                        logtype::sd_int line_) {

        if (level_ < m_mini_level) {
            return;
        }

        auto &term_output = m_sink_pipeline.m_term_sink.m_output_;
        auto &file_output = m_sink_pipeline.m_file_sink.m_output_;
        auto &term_format = m_sink_pipeline.m_term_sink.m_format_;
        auto &file_format = m_sink_pipeline.m_file_sink.m_format_;
        auto &tmap = m_text_token_map;
        auto &amap = m_ansi_token_map;
        logtype::string term_level_str;
        logtype::string file_level_str;
        logtype::seqnum sequence;

        switch (level_) {
        case logenum::Level::INFO:
            term_level_str = m_ansi_level_map.at(k::G_INFO);
            file_level_str = m_text_level_map.at(k::G_INFO);
            sequence = m_seq_info;
            increment(m_seq_info);
            break;
        case logenum::Level::WARNING:
            term_level_str = m_ansi_level_map.at(k::G_WARNING);
            file_level_str = m_text_level_map.at(k::G_WARNING);
            sequence = m_seq_warning;
            increment(m_seq_warning);
            break;
        case logenum::Level::ERROR:
            term_level_str = m_ansi_level_map.at(k::G_ERROR);
            file_level_str = m_text_level_map.at(k::G_ERROR);
            sequence = m_seq_error;
            increment(m_seq_error);
            break;
        case logenum::Level::FATAL:
            term_level_str = m_ansi_level_map.at(k::G_FATAL);
            file_level_str = m_text_level_map.at(k::G_FATAL);
            sequence = m_seq_fatal;
            increment(m_seq_fatal);
            break;
        default: // logenum::Level::DEBUG:
            term_level_str = m_ansi_level_map.at(k::G_DEBUG);
            file_level_str = m_text_level_map.at(k::G_DEBUG);
            sequence = m_seq_debug;
            increment(m_seq_debug);
            break;
        }

        if (level_ >= m_term_level) {
            out_stream(term_format, term_output, amap, term_level_str, sequence, message_, file_, line_);
        }

        if (level_ >= m_file_level) {
            out_stream(file_format, file_output, tmap, file_level_str, sequence, message_, file_, line_);
        }
    }

} // namespace ruac::rstd::logsystem
