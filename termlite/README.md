# Ruacdb Terminal Lite

## Introduction

Terminal Lite (termlite) is a reserved GUI interaction module for RUACDB. RUACDB itself is a lightweight database that operates primarily in command-line mode, following the Linux philosophy of "small and focused." To ensure long-term extensibility, termlite provides a pre-built graphical interface scaffold — it does not replace the CLI, but serves as a future entry point for users who prefer visual interaction.

Strictly speaking, termlite is an extension project. It is designed as an optional component: the core database functions independently without it, while termlite can be built and loaded when a graphical environment is needed.

## Design Principles

- **Decoupled from core**: termlite depends only on well-defined interfaces from the RUACDB core. It has no knowledge of internal implementations.
- **Optional component**: RUACDB remains fully functional in CLI mode. termlite is built separately and never required.
- **Minimal surface**: the GUI is intentionally kept lightweight, aligned with RUACDB's "small and focused" philosophy.

## Tech Stack

| Component      | Detail                  |
|----------------|-------------------------|
| Language       | C++26                   |
| Build System   | CMake 4.3+              |
| GUI Framework  | Qt6 (Widgets)           |
| Standard       | `CMAKE_CXX_STANDARD 26` |

## Current State

termlite is in an early scaffolding stage. The existing implementation provides:

- A `QMainWindow` (960x640) with a horizontal `QSplitter` layout
- A sidebar panel (ratio 1) with light gray styling
- A content panel (ratio 3) with white background
- A 1px splitter handle between panels

The layout structure is in place, but the sidebar and content areas have no functional widgets yet. Several Qt headers (`QHBoxLayout`, `QVBoxLayout`, `QLabel`, `QPainterPath`) are included but commented out, indicating planned expansion.

## Building

```bash
mkdir -p cmake-build-debug && cd cmake-build-debug
cmake ..
make
```

Requires Qt6 Widgets to be installed and discoverable by CMake.

## Project Structure

```
termlite/
├── CMakeLists.txt          # Build configuration
├── termlite.cpp            # Entry point
├── src/
│   ├── ruac_window.hpp     # Window class declaration
│   └── ruac_window.cpp     # Window implementation
├── mkf.sh                 # Build helper script
├── out/                   # Build output directory
└── README.md
```

## Future Direction

termlite will gradually incorporate functional UI components to support database operations through a graphical interface. Planned areas include database object browsing, query execution views, and result visualization — all while maintaining the lightweight nature of the module.
