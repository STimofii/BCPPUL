rmdir /s /q lib
mkdir lib
mkdir lib\bcppul
mkdir lib\bcppul\include
mkdir lib\bcppul\lib
copy build_debug\lib\Debug\bcppul_static.lib lib\bcppul\lib\bcppul_static_debug.lib
copy build_debug\bin\Debug\bcppul_shared.dll lib\bcppul\lib\bcppul_shared_debug.dll
copy build_release\lib\Release\bcppul_static.lib lib\bcppul\lib\bcppul_static_release.lib
copy build_release\bin\Release\bcppul_shared.dll lib\bcppul\lib\bcppul_shared_release.dll
copy build_debug\lib\Debug\bcppul_shared.lib lib\bcppul\lib\bcppul_shared_debug.lib
copy build_release\lib\Release\bcppul_shared.lib lib\bcppul\lib\bcppul_shared_release.lib
xcopy build_release\bcppul\* lib\bcppul\include\bcppul\ /E
xcopy include\bcppul\* lib\bcppul\include\bcppul\ /E