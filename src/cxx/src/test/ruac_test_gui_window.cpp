/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_gui_window.hpp
 * src/test/ruac_test_gui_window.cpp
 */

#include "test/ruac_test_gui_window.hpp"
#include <QApplication>
#include <QWidget>

namespace ruac::test {

    void TestGuiWindow::show_window(int argc, char **argv) {
        QApplication app(argc, argv);
        QWidget window;
        window.setWindowTitle("ruac terminal lite");
        window.resize(900, 700);
        window.show();
        app.exec();
    }

} // namespace ruac::test
