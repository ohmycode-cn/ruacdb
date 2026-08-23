/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/track/ruac_track_abstract.hpp
 * src/kernel/track/ruac_track_abstract.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_TRACK_ABSTRACT_HPP
#define RUAC_TRACK_ABSTRACT_HPP

#include "kernel/track/ruac_track_kernel.hpp"

namespace ruac::kernel::track {

    class TrackAbstract {
      public:
        virtual ~TrackAbstract() = default;

      public:
        virtual auto get_kernel() -> Kernel & = 0;
    };

} // namespace ruac::kernel::track

#endif // RUAC_TRACK_ABSTRACT_HPP
