# CMake generated Testfile for 
# Source directory: /home/hwlee4/ics46/Lab3/Calculator
# Build directory: /home/hwlee4/ics46/Lab3/Calculator/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CalculatorTests "/home/hwlee4/ics46/Lab3/Calculator/build/bin/CalculatorTests")
set_tests_properties(CalculatorTests PROPERTIES  _BACKTRACE_TRIPLES "/home/hwlee4/ics46/Lab3/Calculator/CMakeLists.txt;43;add_test;/home/hwlee4/ics46/Lab3/Calculator/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
