rmdir /s /q build_release
cmake -B build_release
cmake --build build_release --config Release
pause