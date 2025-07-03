rmdir /s /q build_debug
cmake -B build_debug
cmake --build build_debug
rmdir /s /q build_release
cmake -B build_release
cmake --build build_release --config Release