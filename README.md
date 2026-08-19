# RUACDB (Runtime Unified Access Control Database)

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

## Development Environment & Toolchain Requirements

- **IDE Recommendations**
  - Code IDE (Visual Studio Code(/Insider)/Trae/...)
  - CLion (JetBrains)
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
