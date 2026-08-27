# RUACDB (Runtime Unified Access Control Database)

> [!IMPORTANT]
> ## Kernel Stage Note (0.0.1-beta)
>
> The current kernel (`kernel`) is in the **0.0.1-beta** stage. It serves only as a minimal viable prototype (MVP) for validating that the overall architecture can run end-to-end, and has not yet reached the maturity required for production or large-scale multi-user scenarios.
>
> ### Known Defects
>
> - **Flattened data ownership with full copies**: data is copied between `object::Kernel` and `object::Single` / `object::Multis` via `getdbs()` returning a copy, and `Single` / `Multis` each perform a full deep copy at construction. Starting N users can therefore produce N times the amount of data copied, suffering from severe data bloat and synchronization problems.
> - **One-shot multi-user registration**: `ControllerPipes::init_pipe` relies on the `m_once_lock` flag, so only the first user can be registered and subsequent users are silently ignored, preventing the multi-user scenario from initializing correctly.
> - **Data write path is not yet closed**: `object::Kernel` currently only exposes read-only copy access (`getdbs()` returns by value) and lacks a write entry point to synchronize modifications back to the authoritative data source; the data semantics (shared vs. isolated) have not been finalized.
> - **Dangling references (raw-pointer ownership)**: `ControllerTable::m_controller_table` stores each user's controller as a raw pointer `Operation *`, whose lifetime is owned by the caller (the `new` in `main()`) yet is never `delete`d — this is both a memory leak and leaves no guarantee that the referenced object remains alive while being held. If `Operation` is released early or switched to a stack object / smart pointer, the raw pointer kept in the table will immediately dangle; `ControllerPipes` holds `object / state / track` as raw pointers with the same hazard.
>
> ### Stage Positioning
>
> The goal of this stage is to **get the system running first** and validate a minimal closed loop (login → controller assembly → state initialization → interactive shell → SQL statement execution), rather than pursuing correctness of the data model, concurrency, and persistence. The defects above are all known and will be progressively resolved in later commits by refactoring the kernel (shared data references, closed write paths, multi-user registration, and so on).

## Introduction

RUACDB is a mini database for runtime unified access control, implemented in C/C++/Rust, with most functionality written in C++. The project is dedicated to exploring a more radical database system architecture, and therefore may undergo major refactoring at certain milestones or specific version stages. RUACDB has been verified to compile and run on Windows 11 / Linux platforms.

**Core Philosophy: Absolute Modularity** — Each module only needs to provide well-defined interfaces without knowing the internal implementation of other modules, ensuring long-term maintainability and extensibility.

## Vision

RUACDB is inspired by the Linux philosophy, adhering to the principles of "small and focused," "large and comprehensive," "modular," and "extensible."

### Multi-Language Architecture

RUACDB employs a multi-language implementation strategy:
- **C++**: Most functionality implementation
- **Rust**: Memory-safety-critical parts
- **C**: Performance-critical parts

This design leverages the strengths of each language to achieve optimal performance while ensuring development efficiency and safety.

### Language Standard Strategy

RUACDB will completely abandon outdated programming paradigms and language standards:
- **C++**: Minimum standard C++17, actual usage C++26
  - ISO Standard: https://isocpp.org
- **C**: Directly adopt C23 standard
  - Working Draft: https://www.open-std.org/jtc1/sc22/wg14/
  - ISO Standard: https://www.iso.org/standard/82075.html
- **Rust**: Use the latest long-term support version from the official Rust standard library

| Resource | URL |
|----------|-----|
| Official Website | https://www.rust-lang.org/ |
| Chinese Website | https://www.rust-lang.org/zh-CN/ |
| RFC Repository | https://github.com/rust-lang/rfcs |
| Standard Library Docs | https://doc.rust-lang.org/std/ |
| Source Repository | https://github.com/rust-lang/rust |

RUACDB adopts Rust's "use and discard" philosophy in C/C++ code, which may seem unconventional by industry standards. However, this makes RUACDB's code safer and more maintainable.

### Standard Library & System Architecture

RUACDB, like an operating system, has its own standard library `rstd`:
- `rstd` is a strictly isolated library module with dependencies between submodules explicitly prohibited
- Each submodule is only responsible for its own functionality and provides clear interfaces
- In the future, third-party libraries will gradually be replaced by the project's standard library

RUACDB has a complete system architecture:
- Database model
- Kernel layer
- User layer (similar to the Linux user system, with user space; the default root user has full permissions)
- Network layer

A user + group permission model will be introduced in the future.

## Participation Guidelines

RUACDB is a complex project and can be very challenging!

**Note**: I am not a professional software engineer (maybe someday I will be), just a free software enthusiast. If you are interested in RUACDB, you are welcome to participate in development and discussions.

**Important**: All participants must strictly adhere to RUACDB's code standards and development workflow. If you cannot accept these standards and workflow, your submissions will be rejected.

### Code Standards

- RUACDB C/C++ Style Guide: `RUAC-CCXX-STYLE-GUIDE.md`
  - [English](RUAC-CCXX-STYLE-GUIDE.md)
  - [Chinese](document/md/zh_cn/RUAC-CCXX-STYLE-GUIDE.md)

- RUACDB Rust Style Guide: `RUAC-RUST-STYLE-GUIDE.md`
  - [English](RUAC-RUST-STYLE-GUIDE.md)
  - [Chinese](document/md/zh_cn/RUAC-RUST-STYLE-GUIDE.md)

- RUACDB BASH Style Guide: `RUAC-BASH-STYLE-GUIDE.md`
  - [English](RUAC-BASH-STYLE-GUIDE.md)
  - [Chinese](document/md/zh_cn/RUAC-BASH-STYLE-GUIDE.md)

### Project Rules

- Project rules and contribution restrictions announcement: `RULES.md`
  - [English](RULES.md)
  - [Chinese](RULES.md)
  - These are rules added or updated after the initial project setup.

## Development Environment & Toolchain Requirements

- **IDE Recommendations**
  - Code IDE (Visual Studio Code(/Insider)/Trae/...)
  - CLion (JetBrains)
- **Line Break Limits**
  - For Code-based IDEs, add the following settings to `settings.json` to display column rulers and enable word wrap:
    ```jsonc
    "editor.rulers": [
        {
            "column": 100,
            "color": "#2E7D3250"
        },
        {
            "column": 120,
            "color": "#e6394660"
        }
    ],
    "editor.tabSize": 4,
    "editor.wordWrap": "wordWrapColumn",
    "editor.wordWrapColumn": 120,
    "editor.wrappingIndent": "same"
    ```
- **WINDOWS**
  - Compile env: clang-cl.exe/clang++.exe
  - Qt env: Qt6(>=6.11.0), recommended: msvc2022
- **LINUX**
  - Compile env: clang++
  - Qt env: Your Linux latest Qt version (but >= 6.11.0)
- **MACOS**
  - Unsupported platform
- **UNIX**
  - Unsupported platform
- **OTHER**
  - Unsupported platform

### CMakeLists.txt Configuration

If building RUACDB on Windows platform, you need to create a `local.cmake` file and modify the Qt6 path:

```cmake
# local.cmake
if (WIN32)
    set(Qt6_ROOT "your/Qt6/installation/path")
    set(CMAKE_PREFIX_PATH "${Qt6_ROOT}" CACHE PATH "Qt6 install root")
endif()
```

`local.cmake` has been added to `.gitignore` and will not be committed to version control.

### Build & Compile

RUACDB provides the build script `mk-compile-ruacdb.sh` to simplify the CMake workflow.

**Prerequisites**:
- CMake >= 4.3.1
- Clang (clang++ on Linux, clang-cl on Windows)
- Qt6 Widgets >= 6.11.0
- Bash >= 5.0

**Build Modes**:

| Mode | Command | Description |
|------|---------|-------------|
| Debug (default) | `bash mk-compile-ruacdb.sh` | Enables unit tests (`UNIT_TEST=ON`), links Google Test |
| Production (Release) | `bash mk-compile-ruacdb.sh --off-unit-test` | Disables unit tests (`UNIT_TEST=OFF`), excludes all test sources and Google Test |

**Build Workflow** (production binary):

```bash
# 1. (Windows only) Create local.cmake and set your Qt6 path (see above)

# 2. Build production binary
bash mk-compile-ruacdb.sh --off-unit-test

# 3. Run
./out/ruacdb
```

**Build Workflow** (development with tests):

```bash
# 1. Build with unit tests enabled
bash mk-compile-ruacdb.sh

# 2. Run
./out/ruacdb
```

The script automatically:
- Detects the number of CPU cores (`nproc` / `sysctl`) for parallel compilation
- Configures CMake in the `build/` directory
- Outputs the binary to `out/ruacdb`

### Module API Documentation

Each module has clear API interfaces. Documentation can be found in the `document/api/` directory.

**Note**: API documentation may not be updated in a timely manner. Please be aware of version differences when using it.

## Git Commit Guidelines

- No limit on the number of commits
- Before modifying code files (add/delete/update), always pull the latest code first to avoid conflicts with others' changes
- Commit messages must be written in English and describe the changes in detail, including:
  - Files modified
  - Location of changes
  - Reason for changes

## License

RUACDB is licensed under the **GNU General Public License v3.0 or later (GPL-3.0-or-later)**, with additional attribution terms applied pursuant to Section 7 of the GPL-3.0. See [LICENSE](LICENSE) for the full text.
