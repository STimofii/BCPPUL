rmdir /s /q build
cmake -B build_debug
cmake --build build_debug
rmdir /s /q build
cmake -B build_release
cmake --build build_release --config Release