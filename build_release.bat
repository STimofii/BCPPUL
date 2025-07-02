rmdir /s /q build
cmake -B build_release
cmake --build build_release --config Release
pause