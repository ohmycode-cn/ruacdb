/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_output_file.hpp
 * src/rstd/logsystem/ruac_output_file.cpp
 *
 * @brief File output sink for writing log messages to disk
 */

#pragma once
#ifndef RUAC_OUTPUT_FILE_HPP
#define RUAC_OUTPUT_FILE_HPP

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_output.hpp"
#include <fstream>
#include <memory>

namespace ruac::rstd::logsystem {

    /**
     * @brief File-output sink that writes formatted log messages to disk.
     *        Supports shared static paths for single-file multi-instance
     *        logging or per-instance paths for thread-separation scenarios.
     */
    class OutputFile : public Output {
      private:
        std::unique_ptr<std::ofstream> m_ofs{nullptr};

        logtype::string m_fpath{nullproc::nostr()};
        logtype::string m_fname{nullproc::nostr()};

        static logtype::string m_static_fpath;
        static logtype::string m_static_fname;

        static bool m_is_lock_vals;

      private:
        bool m_is_check{false};
        bool m_is_openf{false};

      private:
        void init(const logtype::string &fpath_, const logtype::string &fname_, const bool thread_separation_mode);
        void over();

      public:
        OutputFile(const logtype::string &fpath_, const logtype::string &fname_,
                   const bool thread_separation_mode = true);
        ~OutputFile();

      public:
        void output(const logtype::string &message_);

    }; // class OutputFile

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_FILE_HPP
