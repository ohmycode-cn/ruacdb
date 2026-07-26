/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_manager.hpp
 * src/rstd/logsystem/ruac_manager.cpp
 */

#include "rstd/logsystem/ruac_manager.hpp"
#include "rstd/logsystem/ruac_output_console.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"

namespace ruac::rstd::logsystem {

    Manager::~Manager() {
        over_sink_pipeline();
    }

    void Manager::create_sink_output(Output *&out_, const logenum::Output &enum_out_) {
        if (nullptr != out_) {
            return;
        }
        switch (enum_out_) {
        case logenum::Output::FILE:
            out_ = new OutputFile(m_wf_path, m_wf_name, true);
            break;
        case logenum::Output::CONSOLE:
            out_ = new OutputConsole();
            break;
        }
    }

    void Manager::create_sink_format(Format *&fmt_, const logenum::Format &enum_fmt_) {
        if (nullptr != fmt_) {
            return;
        }
        switch (enum_fmt_) {
        case logenum::Format::JSON:
            fmt_ = new FormatJson();
            break;
        case logenum::Format::TEXT:
            fmt_ = new FormatText();
            break;
        case logenum::Format::XML:
            fmt_ = new FormatXML();
            break;
        }
    }

    void Manager::delete_sink_output(Output *&out_) {
        if (nullptr == out_) {
            return;
        }
        delete out_;
        out_ = nullptr;
    }

    void Manager::delete_sink_format(Format *&fmt_) {
        if (nullptr == fmt_) {
            return;
        }
        delete fmt_;
        fmt_ = nullptr;
    }

    void Manager::init_sink_pipeline(const AllocatorParamList &params_) {
        m_wf_path = params_.m_wf_path;
        m_wf_name = params_.m_wf_name;
        create_sink_output(m_sink_pipeline.m_file_sink.m_output_, params_.m_file_output);
        create_sink_output(m_sink_pipeline.m_term_sink.m_output_, params_.m_term_output);
        create_sink_format(m_sink_pipeline.m_file_sink.m_format_, params_.m_file_format);
        create_sink_format(m_sink_pipeline.m_term_sink.m_format_, params_.m_term_format);
    }

    void Manager::over_sink_pipeline() {
        delete_sink_output(m_sink_pipeline.m_file_sink.m_output_);
        delete_sink_output(m_sink_pipeline.m_term_sink.m_output_);
        delete_sink_format(m_sink_pipeline.m_file_sink.m_format_);
        delete_sink_format(m_sink_pipeline.m_term_sink.m_format_);
    }

    void Manager::out_stream(Format *&format_, Output *&output_, const logtype::strmap &strmap_,
                             const logtype::string &level_, const logtype::seqnum &sequence_,
                             const logtype::string &message_, const logtype::string &file_, logtype::sd_int line_) {

        if (nullptr == format_ || nullptr == output_) {
            return;
        }
        auto time = logtime::get_time();
        auto strs = format_->format(strmap_, time, level_, sequence_, message_, file_, line_);
        output_->output(strs);
    }

    void Manager::init(const LoaderParamList &params_) {
        m_allocator = std::make_unique<Allocator>(params_);
        init_sink_pipeline(m_allocator->get_param_list());
    }

    void Manager::write(logenum::Level level_, const logtype::string &message_,
                        const logtype::string &file_, logtype::sd_int line_) {
    }

} // namespace ruac::rstd::logsystem
