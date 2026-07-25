/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_output_file.hpp
 * src/rstd/logsystem/ruac_output_file.cpp
 */

#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include <filesystem>
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {

        /**
         * @brief Validates the target directory and file for write access.
         *
         * If the directory does not exist, attempts to create it.  If the
         * file already exists, verifies it is a regular file.  A missing
         * file is not an error — the caller will create it on open.
         *
         * @param fpath_  The directory path where the log file should reside.
         * @param fname_  The log file name to validate.
         *
         * @return true when the directory is writable (and, if the file
         *         exists, it is a regular file); false on hard errors.
         */
        auto checkfile(const logtype::string &fpath_, const logtype::string &fname_) -> bool {

            const char *const pfmt{"                 Path: "};
            const char *const ffmt{"                 File: "};
            const char *const PREFIX_PATH{"PATH "};
            const char *const PREFIX_FILE{"FILE "};
            const char *const NEXT_LINE{"\n"};

            namespace fs = std::filesystem;
            auto fpath = fs::path(fpath_);
            auto full = fpath / fname_;

            if (!fs::exists(fpath)) {
                std::stringstream ss;
                ss << "Directory not exist, you must manually create it: " << NEXT_LINE << pfmt << fpath;

                ss << DebugT::instance().ostrs("", __FILE__, __LINE__);

                Message::instance().stdout_err(ss.str(), PREFIX_PATH);

                return false;
            }

            auto perms = fs::status(fpath).permissions();
            if ((perms & fs::perms::owner_write) == fs::perms::none) {
                std::stringstream ss;
                ss << "Directory is not writable: " << NEXT_LINE << pfmt << fpath;

                ss << DebugT::instance().ostrs("", __FILE__, __LINE__);

                Message::instance().stdout_err(ss.str(), PREFIX_PATH);
                return false;
            }

            if (fs::exists(full)) {
                if (!fs::is_regular_file(full)) {
                    std::stringstream ss;
                    ss << "Target is not a regular file: " << NEXT_LINE << pfmt << fpath << NEXT_LINE << ffmt << fname_;

                    ss << DebugT::instance().ostrs("", __FILE__, __LINE__);

                    Message::instance().stdout_err(ss.str(), PREFIX_FILE);
                    return false;
                }
            }

            return true;
        }

    } // namespace

    /// Shared directory path for non-thread-separation mode, locked after first assignment.
    logtype::string OutputFile::m_static_fpath{nullproc::nostr()};
    /// Shared file name for non-thread-separation mode, locked after first assignment.
    logtype::string OutputFile::m_static_fname{nullproc::nostr()};
    /// Flag indicating whether the shared static paths have been locked.
    bool OutputFile::m_is_lock_vals{false};

    /**
     * @brief Constructs an OutputFile and initializes the file stream.
     *
     * @param fpath_  The directory path for the log file.
     * @param fname_  The log file name.
     * @param thread_separation_mode  If true, each instance uses its own path;
     *                                if false, all instances share static paths.
     */
    OutputFile::OutputFile(const logtype::string &fpath_, const logtype::string &fname_,
                           const bool thread_separation_mode) {
        init(fpath_, fname_, thread_separation_mode);
    }

    /**
     * Destroys the OutputFile and closes the file stream.
     */
    OutputFile::~OutputFile() {
        over();
    }

    /**
     * @brief Initializes the file stream with path validation and mode selection.
     *
     * In shared mode (thread_separation_mode=false), the first call locks the
     * static paths; subsequent calls reuse them. In separation mode, each
     * instance maintains its own path. Opens the file in binary append mode.
     *
     * @param fpath_  The directory path for the log file.
     * @param fname_  The log file name.
     * @param thread_separation_mode  If true, uses instance-specific paths;
     *                                if false, uses shared static paths.
     */
    void OutputFile::init(const logtype::string &fpath_, const logtype::string &fname_,
                          const bool thread_separation_mode) {

        if (!thread_separation_mode && !m_is_lock_vals) {
            m_static_fpath = fpath_;
            m_static_fname = fname_;
            m_is_lock_vals = true;
        } else {
            m_fpath = fpath_;
            m_fname = fname_;
        }

        auto bin = std::ios::binary;
        auto out = std::ios::out;
        auto app = std::ios::app;

        logtype::string file_path = (thread_separation_mode) ? m_fpath : m_static_fpath;
        logtype::string file_name = (thread_separation_mode) ? m_fname : m_static_fname;

        m_is_check = (checkfile(file_path, file_name));
        if (!m_is_check) {
            return;
        }

        m_ofs = std::make_unique<std::ofstream>(file_path + "/" + file_name, out | app | bin);
        if (m_ofs->is_open()) {
            m_is_openf = true;
        }
    }

    /**
     * Closes the output file stream if it is open.
     */
    void OutputFile::over() {
        if (m_ofs && m_ofs->is_open()) {
            m_ofs->close();
        }
    }

    /**
     * @brief Writes a log message to the output file.
     *
     * @param message_  The formatted log message string to write.
     *
     * @note Silently returns if the file is not open or validation failed.
     */
    void OutputFile::output(const logtype::string &message_) {
        if (!m_is_openf || !m_is_check) {
            return;
        }
        (*m_ofs) << message_ << std::endl;
    }

} // namespace ruac::rstd::logsystem
