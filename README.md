# ruacdb (Runtime Unified Access Controller Database)

## Introduction

RUACDB is a mini database for runtime unified access control, implemented in C/C++/Rust. Most of the functionality is written in C++. I'm not sure what RUACDB will become in the future, but I hope to explore a more radical database system. This means RUACDB may undergo major refactoring at certain milestones or specific version stages. The core philosophy of RUACDB is absolute modularity. Each module only needs to provide well-defined interfaces without knowing the internal implementation of other modules, ensuring long-term maintainability and extensibility. I am not a professional software engineer (maybe someday), just a free software enthusiast. If you are interested in RUACDB, you are welcome to participate in development and discussions.

## Vision

RUACDB is inspired by the Linux philosophy, adhering to the principles of "small and focused," "large and comprehensive," "modular," and "extensible."
RUACDB employs a multi-language implementation: most functionality is implemented in C++, memory-safety-critical parts use Rust, and performance-critical parts use C. This design leverages the strengths of each language to achieve optimal performance while ensuring development efficiency and safety.
RUACDB adopts Rust's "use and discard" philosophy in C/C++ code, which may seem unconventional by industry standards. However, this makes RUACDB's code safer and more maintainable. In terms of language standards, RUACDB will completely abandon outdated programming paradigms and language standards. RUACDB's minimum C++ standard is C++17, but the actual project uses C++26, and the compiler standard is also set to C++26. For C components, RUACDB will directly adopt the C23 standard. Rust components will use the latest long-term support version of the official Rust standard library. RUACDB is a complex project and can be very challenging! In summary, RUACDB is a project that pursues new language standards, even though C++26 has not yet been officially released by the ISO C++ Standards Committee.
RUACDB is like an operating system — it has its own standard library, which means third-party libraries will gradually be replaced by its own standard library. In the future, RUACDB will have its own project standard library, which may require reinventing some wheels — this is both a challenge and a learning opportunity.
RUACDB has its own database model, kernel layer, user layer, and network layer. Similar to the Linux user system, RUACDB's user layer has its own user space, and the default root user has full permissions and controls the RUACDB system. In the future, RUACDB will also introduce a user + group permission model.

## ruacdb Project Standard Library

RUACDB's standard library, rstd, is a strictly isolated library module. Any dependencies between submodules of rstd are explicitly prohibited. Each submodule is only responsible for its own functionality and provides clear interfaces.
