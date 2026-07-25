/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_allocator.hpp
 * src/rstd/logsystem/ruac_allocator.cpp
 */

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::rstd::logsystem {

    Allocator::Allocator(const LoaderParamList &loader_param_list) {
        {
            Loader loader(loader_param_list);
            m_loader_map = loader.getmap();
            m_loader_msg = loader.outmap_string(m_loader_map);
        }
    }

    auto Allocator::get_sink_pipeline() -> AllocatorSinkPipeline & {
        return m_sink_pipeline;
    }

    auto Allocator::get_param_list() -> AllocatorParamList {
        return m_param_list;
    }

    void Allocator::out_loader_msg() {
        std::osyncstream(std::cout) << m_loader_msg << std::endl;
    }

} // namespace ruac::rstd::logsystem
