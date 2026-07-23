/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_loader.hpp
 * src/rstd/logsystem/ruac_loader.cpp
 */

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include <filesystem>
#include <sstream>
#include <fstream>

namespace ruac::rstd::logsystem {

    Loader::Loader(const LoaderParamList &params) {
        m_params = params;
        load_file_content_to_buffer();
    }

    Loader::~Loader() {
        free_buffer();
    }

    void Loader::load_file_content_to_buffer() {
        if (m_once_lock) {
            return;
        }
        m_once_lock = true;

        auto fullpath = std::filesystem::path(m_params.m_fpath) / m_params.m_fname;
        auto fpath = m_params.m_fpath;
        auto fname = m_params.m_fname;

        if (!std::filesystem::exists(fullpath)) {
            std::stringstream ss;
            ss << "Loader: file not found: " << nullproc::nextline();
            ss << "      Path: " << fpath << nullproc::nextline();
            ss << "      Name: " << fname;
            Message::instance().stdout_err(ss.str(), "LOAD ");
            return;
        }

        auto f_size = std::filesystem::file_size(fullpath);
        auto b_size = static_cast<std::size_t>(f_size);

        m_buffer = new char[b_size];
        std::ifstream ifs(fullpath);
        ifs.read(m_buffer, b_size);
        ifs.close();
        m_load_done = true;
    }

    void Loader::free_buffer() {
        if (nullptr != m_buffer) {
            delete[] m_buffer;
            m_buffer = nullptr;
        }
    }

    auto Loader::parser_buffer_content() -> logtype::StringMap {
        logtype::StringMap map{};
        if (nullptr == m_buffer) {
            return map;
        }

        // TODO: parser buffer content to map map
        return map;
    }

    auto Loader::getmap(const LoaderParamList &params) -> logtype::StringMap {
        if (!m_once_lock) {
            load_file_content_to_buffer();
        }
        if (!m_load_done) {
            return {};
        }
        return parser_buffer_content();
    }
} // namespace ruac::rstd::logsystem
