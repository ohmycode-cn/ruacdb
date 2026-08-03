/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/miniterm/gui/ruac_winterm.hpp
 * src/miniterm/gui/ruac_winterm.cpp
 */

#include "miniterm/gui/ruac_winterm.hpp"
#include <QApplication>
#include <QWidget>

namespace ruac::miniterm::gui {

    void WinTerm::w_master(int argc, char **argv) {
        QApplication app(argc, argv);
        QWidget window;
        window.setWindowTitle("ruac terminal lite");
        window.resize(900, 700);
        window.show();
        app.exec();
    }

} // namespace ruac::miniterm::gui
