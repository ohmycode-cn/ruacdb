# RULES

> Effective date: 2026-08-22 12:49

## Google Test Framework

- Only repository administrators are authorized to pull / update the vendored Google Test framework (`src/cxx/include/google_test/api/googletest/`).
- Contributors must not modify, re-vendor, or re-pull the Google Test source tree without admin approval.

> Effective date: 2026-08-23 14:28

## mk-compile-ruacdb.sh

- The Windows platform does not currently support compiling production binaries via the script `mk-compile-ruacdb.sh`. Compilation must be performed manually.

```shell
cmake -B build -DUNIT_TEST=OFF
cmake --build build/ -j<N>
```

 - `-j<N>`: Replace `<N>` with the number of parallel jobs appropriate for your device (e.g. `-j9` for a machine with 9+ cores). Do not omit the value entirely — `-j` without a number lets the build system use unlimited parallelism, which may exhaust memory on low-core machines.
