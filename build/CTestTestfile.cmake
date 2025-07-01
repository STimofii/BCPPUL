# CMake generated Testfile for 
# Source directory: C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL
# Build directory: C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(BCPPUL_Example_Run "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/build/Debug/bcppul_example.exe")
  set_tests_properties(BCPPUL_Example_Run PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;73;add_test;C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(BCPPUL_Example_Run "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/build/Release/bcppul_example.exe")
  set_tests_properties(BCPPUL_Example_Run PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;73;add_test;C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(BCPPUL_Example_Run "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/build/MinSizeRel/bcppul_example.exe")
  set_tests_properties(BCPPUL_Example_Run PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;73;add_test;C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(BCPPUL_Example_Run "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/build/RelWithDebInfo/bcppul_example.exe")
  set_tests_properties(BCPPUL_Example_Run PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;73;add_test;C:/Users/Bulka/Desktop/programming/cpp/libs/BCPPUL/CMakeLists.txt;0;")
else()
  add_test(BCPPUL_Example_Run NOT_AVAILABLE)
endif()
