#include "ruac_window.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
// #include <QHBoxLayout>
// #include <QVBoxLayout>
// #include <QLabel>
#include <QListWidget>
#include <QSplitter>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
// #include <QPainterPath>

namespace ruac::terminal_lite {

    void Window::run(int argc, char **argv) {
        QApplication app(argc, argv);
        QMainWindow mainWindow;
        mainWindow.setWindowTitle("Ruac Terminal Lite");
        mainWindow.resize(960, 640);
        auto *sidebar = new QWidget();
        auto *content = new QWidget();
        sidebar->setStyleSheet("background: rgba(246,246,246,0.92); border-right: 1px solid #d4d4d4;");
        content->setStyleSheet("background: #ffffff;");
        auto *splitter = new QSplitter(Qt::Horizontal);
        splitter->addWidget(sidebar);
        splitter->addWidget(content);
        splitter->setStretchFactor(0, 1);
        splitter->setStretchFactor(1, 3);
        splitter->setHandleWidth(1);
        mainWindow.setCentralWidget(splitter);
        mainWindow.show();
        QApplication::exec();
    }

} // namespace ruac::terminal_lite
