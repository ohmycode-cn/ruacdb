#include "ruac_window.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QScrollArea>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QLabel>

namespace ruac::terminal_lite {

    static const char *kScrollBarStyle = R"(
        QScrollBar:vertical {
            background: transparent;
            width: 10px;
            margin: 4px 2px 4px 2px;
            border: none;
        }
        QScrollBar::handle:vertical {
            background: #4a4a4a;
            min-height: 36px;
            border-radius: 5px;
        }
        QScrollBar::handle:vertical:hover {
            background: #2a2a2a;
        }
        QScrollBar::handle:vertical:pressed {
            background: #1a1a1a;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
            height: 0;
            border: none;
        }

        QScrollBar:horizontal {
            background: transparent;
            height: 10px;
            margin: 2px 4px 2px 4px;
            border: none;
        }
        QScrollBar::handle:horizontal {
            background: #4a4a4a;
            min-width: 36px;
            border-radius: 5px;
        }
        QScrollBar::handle:horizontal:hover {
            background: #2a2a2a;
        }
        QScrollBar::handle:horizontal:pressed {
            background: #1a1a1a;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal,
        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal {
            background: none;
            width: 0;
            border: none;
        }
    )";

    void Window::run(int argc, char **argv) {
        QApplication app(argc, argv);
        QMainWindow mainWindow;
        mainWindow.setWindowTitle("Ruac Terminal Lite");
        mainWindow.resize(960, 640);

        auto *sidebar = new QWidget();
        sidebar->setStyleSheet(
            "background: rgba(246,246,246,0.92);"
            "border-right: 1px solid #d4d4d4;"
        );

        QStringList menuItems = {
            "Dashboard",   "Monitor",       "Settings",
            "Thread",      "Process",       "CPU",
            "GPU",         "NPU",           "Memory",
            "Disk",        "Network",       "Battery",
            "Thermal",     "Fan",           "Voltage",
            "Clock",       "Power",         "Display",
            "Audio",       "USB",           "Bluetooth",
            "WiFi",        "Ethernet",      "Storage",
            "RAID",        "Sensor",        "Kernel",
            "Module",      "Driver",        "Service",
            "Systemd",     "Journal",       "Logs",
            "Dmesg",       "Crash",         "Audit",
            "Firewall",    "Security",      "Container",
            "Virtual Machine", "PCIe",      "IOMMU",
            "DMA",         "Interrupt",     "Scheduler",
            "Cgroup",      "NUMA",          "Hugepages",
            "Swap",        "Zram",          "Benchmark",
            "Stress Test", "Topology",      "Affinity",
            "About"
        };

        auto *sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setContentsMargins(0, 8, 0, 8);
        sidebarLayout->setSpacing(2);
        sidebarLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        auto *mdiArea = new QMdiArea();
        mdiArea->setStyleSheet(
            "QMdiArea { background: #ffffff; }"
            "QMdiSubWindow { background: #ffffff; border: 1px solid #d4d4d4; }"
            "QMdiSubWindow::title-bar { background: rgba(246,246,246,0.95); height: 28px; }"
        );
        mdiArea->setViewMode(QMdiArea::TabbedView);
        for (const auto &item : menuItems) {
            auto *btn = new QPushButton(item);
            btn->setCursor(Qt::PointingHandCursor);
            btn->setStyleSheet(
                "QPushButton {"
                "    background: transparent;"
                "    border: none;"
                "    padding: 10px 20px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    color: #333333;"
                "    border-radius: 6px;"
                "    margin: 0 8px;"
                "}"
                "QPushButton:hover {"
                "    background: rgba(0,0,0,0.05);"
                "}"
                "QPushButton:pressed {"
                "    background: rgba(0,0,0,0.08);"
                "}"
            );
            sidebarLayout->addWidget(btn);

            QObject::connect(btn, &QPushButton::clicked, [mdiArea, item]() {
                for (auto *existing : mdiArea->subWindowList()) {
                    if (existing->windowTitle() == item) {
                        mdiArea->setActiveSubWindow(existing);
                        existing->showNormal();
                        existing->raise();
                        return;
                    }
                }
                auto *subWindow = new QMdiSubWindow();
                auto *contentWidget = new QWidget();
                auto *contentLayout = new QVBoxLayout(contentWidget);
                contentLayout->setContentsMargins(24, 24, 24, 24);

                auto *titleLabel = new QLabel(item);
                titleLabel->setStyleSheet(
                    "font-size: 22px; font-weight: bold; color: #1a1a1a;"
                );

                auto *bodyLabel = new QLabel("Content for " + item);
                bodyLabel->setStyleSheet("font-size: 14px; color: #666666;");

                contentLayout->addWidget(titleLabel);
                contentLayout->addWidget(bodyLabel);
                contentLayout->addStretch();

                subWindow->setWidget(contentWidget);
                subWindow->setWindowTitle(item);
                subWindow->setAttribute(Qt::WA_DeleteOnClose);
                subWindow->resize(480, 360);
                mdiArea->addSubWindow(subWindow);
                subWindow->show();
            });
        }

        sidebarLayout->addStretch();

        auto *sidebarScroll = new QScrollArea();
        sidebarScroll->setWidget(sidebar);
        sidebarScroll->setWidgetResizable(true);
        sidebarScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sidebarScroll->setStyleSheet(
            "border: none;" + QString(kScrollBarStyle)
            );

        auto *centralWidget = new QWidget();
        auto *mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);
        mainLayout->addWidget(sidebarScroll, 1);
        mainLayout->addWidget(mdiArea, 3);

        mainWindow.setCentralWidget(centralWidget);
        mainWindow.show();
        QApplication::exec();
    }

} // namespace ruac::terminal_lite