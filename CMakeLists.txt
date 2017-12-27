# CMake Options
#-----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(whiskey)

# Packages
#-----------------------------------------------------------------------

find_package(ICU)

# Subdirectories
#-----------------------------------------------------------------------

add_subdirectory(test/googletest)

# Include/link directories
#-----------------------------------------------------------------------

include_directories(include ${ICU_INCLUDE_DIRS})

# Flags
#-----------------------------------------------------------------------

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --std=c11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -fno-rtti")

# Fix for Ninja/Clang colored errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics -ferror-limit=5")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics -ferror-limit=5")
endif()

# File lists
#-----------------------------------------------------------------------

set(whiskey_libs lib_whiskey gtest m ${ICU_LIBRARIES})

file(GLOB_RECURSE lib_whiskey_files lib/whiskey/*.cpp)
file(GLOB_RECURSE test_unit_files test/unit/*.cpp)
file(GLOB_RECURSE test_integration_files test/integration/*.cpp)
file(GLOB_RECURSE test_feature_files test/feature/*.cpp)

# Libraries
#-----------------------------------------------------------------------

add_library(lib_whiskey ${lib_whiskey_files})
set_target_properties(lib_whiskey PROPERTIES OUTPUT_NAME whiskey)

# Unit tests
#-----------------------------------------------------------------------

add_executable(test_unit ${test_unit_files})
set_target_properties(test_unit PROPERTIES OUTPUT_NAME whiskey-test-unit)
target_link_libraries(test_unit ${whiskey_libs})

# Integration tests
#-----------------------------------------------------------------------

add_executable(test_integration ${test_integration_files})
set_target_properties(test_integration PROPERTIES OUTPUT_NAME whiskey-test-integration)
target_link_libraries(test_integration ${whiskey_libs})

# Feature tests
#-----------------------------------------------------------------------

add_executable(test_feature ${test_feature_files})
set_target_properties(test_feature PROPERTIES OUTPUT_NAME whiskey-test-feature)
target_link_libraries(test_feature ${whiskey_libs})

# Fuzz tests
#-----------------------------------------------------------------------

add_executable(test_fuzz_lexer_random test/fuzz/FuzzLexerRandom.cpp)
set_target_properties(test_fuzz_lexer_random PROPERTIES OUTPUT_NAME whiskey-test-fuzz-lexer-random)
target_link_libraries(test_fuzz_lexer_random ${whiskey_libs})

add_executable(test_fuzz_lexer_fuzzer_simple test/fuzz/FuzzLexerFuzzerSimple.cpp)
set_target_properties(test_fuzz_lexer_fuzzer_simple PROPERTIES OUTPUT_NAME whiskey-test-fuzz-lexer-fuzzer-simple)
target_link_libraries(test_fuzz_lexer_fuzzer_simple ${whiskey_libs})

add_executable(test_fuzz_literals_reflexive_uint test/fuzz/FuzzLiteralsReflexiveUInt.cpp)
set_target_properties(test_fuzz_literals_reflexive_uint PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-uint)
target_link_libraries(test_fuzz_literals_reflexive_uint ${whiskey_libs})

add_executable(test_fuzz_literals_reflexive_real test/fuzz/FuzzLiteralsReflexiveReal.cpp)
set_target_properties(test_fuzz_literals_reflexive_real PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-real)
target_link_libraries(test_fuzz_literals_reflexive_real ${whiskey_libs})

add_executable(test_fuzz_literals_reflexive_char test/fuzz/FuzzLiteralsReflexiveChar.cpp)
set_target_properties(test_fuzz_literals_reflexive_char PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-char)
target_link_libraries(test_fuzz_literals_reflexive_char ${whiskey_libs})

add_executable(test_fuzz_literals_reflexive_string test/fuzz/FuzzLiteralsReflexiveString.cpp)
set_target_properties(test_fuzz_literals_reflexive_string PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-string)
target_link_libraries(test_fuzz_literals_reflexive_string ${whiskey_libs})

# Demos
#-----------------------------------------------------------------------

add_executable(demo_debug_printer test/demo/DemoDebugPrinter.cpp)
set_target_properties(demo_debug_printer PROPERTIES OUTPUT_NAME whiskey-demo-debug-printer)
target_link_libraries(demo_debug_printer ${whiskey_libs})

# CMake Tests
#-----------------------------------------------------------------------

enable_testing()

add_test(NAME ctest_unit COMMAND ./whiskey-test-unit)
add_test(NAME ctest_integration COMMAND ./whiskey-test-integration)
add_test(NAME ctest_feature COMMAND ./whiskey-test-feature)
