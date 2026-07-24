/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_assembler.hpp
 * src/rstd/logsystem/ruac_assembler.cpp
 * Assembler implementation with config-driven enum resolution, polymorphic
 * Output/Format creation, and safe destruction with null-reset.
 */

#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_output_console.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_assembler.hpp"
#include "rstd/logsystem/ruac_assembler.hpp"
#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Destroys the Assembler, releasing all owned Output and Format objects
     *
     */
    Assembler::~Assembler() {
        endof();
    }

    /**
     * @brief Resolve a Format enum value from a config map entry
     *
     * @param fmt_  Output parameter, set to the resolved Format enum
     * @param map_  Configuration key-value map to read from
     * @param key_  The config key whose value determines the Format
     *
     */
    void Assembler::inner_resolve_format_enum(logenum::Format &fmt_, logtype::StringMap &map_,
                                             const logtype::String &key_) {
        if (logkeys::word::G_JSON == map_.at(key_)) {
            fmt_ = logenum::Format::JSON;
        } else if (logkeys::word::G_XML == map_.at(key_)) {
            fmt_ = logenum::Format::XML;
        } else {
            fmt_ = logenum::Format::TEXT;
        }
    }

    /**
     * @brief Resolve a Level enum value from a config map entry
     *
     * @param level_  Output parameter, set to the resolved Level enum
     * @param map_    Configuration key-value map to read from
     * @param key_    The config key whose value determines the Level
     *
     */
    void Assembler::inner_resolve_log_level(logenum::Level &level_, logtype::StringMap &map_,
                                          const logtype::String &key_) {
        if (logkeys::word::G_LOG_LEVEL_INFO == map_.at(key_)) {
            level_ = logenum::Level::INFO;
        } else if (logkeys::word::G_LOG_LEVEL_WARNING == map_.at(key_)) {
            level_ = logenum::Level::WARNING;
        } else if (logkeys::word::G_LOG_LEVEL_ERROR == map_.at(key_)) {
            level_ = logenum::Level::ERROR;
        } else if (logkeys::word::G_LOG_LEVEL_FATAL == map_.at(key_)) {
            level_ = logenum::Level::FATAL;
        } else {
            level_ = logenum::Level::DEBUG;
        }
    }

    /**
     * @brief Create an Output instance based on the output mode enum.
     * @details Skips if ptr_output_ is already set. Uses a once-lock to ensure
     *          FILE-type Output is created at most once across multiple calls.
     *
     * @param ptr_output_  Reference to output pointer; receives the new object
     * @param enm_out_     Output mode enum (CONSOLE, FILE, or BOTH)
     * @param is_file_     Whether this call targets a file sink channel
     *
     */
    void Assembler::inner_create_output(Output *&ptr_output_, logenum::Output &enm_out_,
                                              logtype::Bool is_file_) {
        if (nullptr != ptr_output_) {
            return;
        }

        auto wf_path = m_allocator.getconfmap().at(logkeys::word::G_LOG_WRITE_PATH);
        auto wf_name = m_allocator.getconfmap().at(logkeys::word::G_LOG_WRITE_FILE);

        switch (enm_out_) {

        case logenum::Output::CONSOLE:
            ptr_output_ = new OutputConsole();
            break;

        case logenum::Output::FILE:
            if (!m_once_lock && is_file_) {
                ptr_output_ = new OutputFile(wf_path, wf_name);
                m_once_lock = true;
            }
            break;

        case logenum::Output::BOTH:
            ptr_output_ = new OutputConsole();
            if (!m_once_lock && is_file_) {
                ptr_output_ = new OutputFile(wf_path, wf_name);
                m_once_lock = true;
            }
            break;
        }
    }

    /**
     * @brief Create a Format instance based on the format enum.
     * @details Skips if ptr_fmt_ is already set.
     *
     * @param ptr_fmt_  Reference to format pointer; receives the new object
     * @param enm_fmt_  Format enum (JSON, XML, or TEXT)
     *
     */
    void Assembler::inner_create_format(Format *&ptr_fmt_, logenum::Format &enm_fmt_) {

        if (nullptr != ptr_fmt_) {
            return;
        }

        switch (enm_fmt_) {
        case logenum::Format::JSON:
            ptr_fmt_ = new FormatJson();
            break;
        case logenum::Format::XML:
            ptr_fmt_ = new FormatXML();
            break;
        case logenum::Format::TEXT:
            ptr_fmt_ = new FormatText();
            break;
        }
    }

    /**
     * @brief Load all member configuration from the Allocator config map.
     * @details Resolves output mode, terminal/file format styles, and three
     *          log level filters into their corresponding enum members.
     *
     */
    void Assembler::inner_load_member_config() {
        auto map = m_allocator.getconfmap();
        if (logkeys::word::G_FILE == map.at(logkeys::word::G_LOG_OUTPUT_MODE)) {
            m_output_mode = logenum::Output::FILE;
        } else if (logkeys::word::G_BOTH == map.at(logkeys::word::G_LOG_OUTPUT_MODE)) {
            m_output_mode = logenum::Output::BOTH;
        } else {
            m_output_mode = logenum::Output::CONSOLE;
        }
        inner_resolve_format_enum(m_term_format, map, logkeys::word::G_LOG_TERM_FORMAT_STYLE);
        inner_resolve_format_enum(m_file_format, map, logkeys::word::G_LOG_FILE_FORMAT_STYLE);
        inner_resolve_log_level(m_term_level, map, logkeys::word::G_TERM_LOG_LEVEL_FILTER);
        inner_resolve_log_level(m_file_level, map, logkeys::word::G_FILE_LOG_LEVEL_FILTER);
        inner_resolve_log_level(m_min_level, map, logkeys::word::G_MINIMUM_LOG_LEVEL);
    }

    /**
     * @brief Destroy an Output object and reset its pointer to nullptr
     *
     * @param ptr_out_  Reference to the output pointer to delete
     *
     */
    void Assembler::inner_destroy_output(Output *&ptr_out_) {
        if (nullptr != ptr_out_) {
            delete ptr_out_;
            ptr_out_ = nullptr;
        }
    }

    /**
     * @brief Destroy a Format object and reset its pointer to nullptr
     *
     * @param ptr_fmt_  Reference to the format pointer to delete
     *
     */
    void Assembler::inner_destroy_format(Format *&ptr_fmt_) {
        if (nullptr != ptr_fmt_) {
            delete ptr_fmt_;
            ptr_fmt_ = nullptr;
        }
    }

    /**
     * @brief Build the complete log pipeline: load config, create terminal and
     *        file Output/Format pairs
     *
     */
    void Assembler::build() {
        inner_load_member_config();
        inner_create_output(m_sink_pipeline.m_term_sink_pair.m_output, m_output_mode,
                                  false);
        inner_create_format(m_sink_pipeline.m_term_sink_pair.m_format, m_term_format);
        inner_create_output(m_sink_pipeline.m_file_sink_pair.m_output, m_output_mode,
                                  true);
        inner_create_format(m_sink_pipeline.m_file_sink_pair.m_format, m_file_format);
    }

    /**
     * @brief Tear down the pipeline: destroy all Output and Format objects
     *
     */
    void Assembler::endof() {

        inner_destroy_output(m_sink_pipeline.m_term_sink_pair.m_output);
        inner_destroy_format(m_sink_pipeline.m_term_sink_pair.m_format);

        inner_destroy_output(m_sink_pipeline.m_file_sink_pair.m_output);
        inner_destroy_format(m_sink_pipeline.m_file_sink_pair.m_format);
    }

    /**
     * @brief Return a reference to the internal Allocator
     *
     * @return Allocator reference
     */
    auto Assembler::get_allocator_obj() -> Allocator & {
        return m_allocator;
    };

    /**
     * @brief Return a reference to the assembled SinkPipeline
     *
     * @return SinkPipeline reference
     */
    auto Assembler::get_sink_pipeline() -> SinkPipeline & {
        return m_sink_pipeline;
    }

    /**
     * @brief Return a copy of the internal config map
     *
     * @return StringMap copy
     */
    auto Assembler::get_map() -> logtype::StringMap {
        return m_map;
    }

} // namespace ruac::rstd::logsystem
