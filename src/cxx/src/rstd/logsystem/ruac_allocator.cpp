/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_allocator.hpp
 * src/rstd/logsystem/ruac_allocator.cpp
 */

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_confmap.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Construct an Allocator and initialize from loader parameters
     *
     * @param loader_param_list - List of loader parameters for configuration
     *
     * @details Creates a Loader instance within a scoped block to populate
     *          m_loader_map and m_loader_msg, then calls init_default_map()
     *          to initialize default configuration. The scoped block ensures
     *          the Loader is destroyed after initialization completes.
     *
     */
    Allocator::Allocator(const LoaderParamList &loader_param_list) {
        {
            Loader loader(loader_param_list);
            m_loader_map = loader.getmap();
            m_loader_msg = loader.outmap_string(m_loader_map);
            init_default_map();
        }
    }

    /**
     * @brief Initialize the default configuration map
     *
     * @details Populates m_default_map with default configuration values
     *          retrieved from confmap::get_default_config_map().
     *
     */
    void Allocator::init_default_map() {
        m_default_map = confmap::get_default_config_map();
    }

    /**
     * @brief Get the sink pipeline reference
     *
     * @return AllocatorSinkPipeline& - Reference to the internal sink pipeline
     *
     * @details Returns a reference to m_sink_pipeline for external access
     *          to the allocator's sink pipeline instance.
     *
     */
    auto Allocator::get_sink_pipeline() -> AllocatorSinkPipeline & {
        return m_sink_pipeline;
    }

    /**
     * @brief Get the parameter list
     *
     * @return AllocatorParamList - Copy of the internal parameter list
     *
     * @details Returns a copy of m_param_list containing the allocator's
     *          configuration parameters.
     *
     */
    auto Allocator::get_param_list() -> AllocatorParamList {
        return m_param_list;
    }

    /**
     * @brief Output the loader message to standard output
     *
     * @details Writes m_loader_msg to stdout using std::osyncstream for
     *          thread-safe concurrent output. The message includes loader
     *          configuration information captured during initialization.
     *
     */
    void Allocator::out_loader_msg() {
        std::osyncstream(std::cout) << m_loader_msg << std::endl;
    }

} // namespace ruac::rstd::logsystem
