/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_gui_window.hpp
 * src/test/ruac_test_gui_window.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_TEST_GUI_WINDOW_HPP
#define RUAC_TEST_GUI_WINDOW_HPP

namespace ruac::test {

    class TestGuiWindow {
      public:
        TestGuiWindow() = default;
        ~TestGuiWindow() = default;

      public:
        void show_window(int argc, char **argv);
    };

} // namespace ruac::test

#endif // RUAC_TEST_GUI_WINDOW_HPP
