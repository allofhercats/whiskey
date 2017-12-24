cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(whiskey)

find_package(ICU)

add_subdirectory(test/googletest)

include_directories(include ${ICU_INCLUDE_DIRS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --std=c11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -fno-rtti")

set(whiskey_libs lib_whiskey gtest m ${ICU_LIBRARIES})

# Fix for Ninja/Clang colored errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
endif()

file(GLOB_RECURSE lib_whiskey_files lib/whiskey/*.cpp)
file(GLOB_RECURSE test_unit_files test/unit/*.cpp)

add_library(lib_whiskey ${lib_whiskey_files})
set_target_properties(lib_whiskey PROPERTIES OUTPUT_NAME whiskey)

add_executable(test_unit ${test_unit_files})
set_target_properties(test_unit PROPERTIES OUTPUT_NAME whiskey-test-unit)
target_link_libraries(test_unit ${whiskey_libs})

add_executable(fuzz_lexer_random test/fuzz/FuzzLexerRandom.cpp)
set_target_properties(fuzz_lexer_random PROPERTIES OUTPUT_NAME whiskey-fuzz-lexer-random)
target_link_libraries(fuzz_lexer_random ${whiskey_libs})

add_executable(fuzz_lexer_fuzzer_simple test/fuzz/FuzzLexerFuzzerSimple.cpp)
set_target_properties(fuzz_lexer_fuzzer_simple PROPERTIES OUTPUT_NAME whiskey-fuzz-lexer-fuzzer-simple)
target_link_libraries(fuzz_lexer_fuzzer_simple ${whiskey_libs})

add_executable(fuzz_literals_reflexive_uint64 test/fuzz/FuzzLiteralsReflexiveUInt64.cpp)
set_target_properties(fuzz_literals_reflexive_uint64 PROPERTIES OUTPUT_NAME whiskey-fuzz-literals-reflexive-uint64)
target_link_libraries(fuzz_literals_reflexive_uint64 ${whiskey_libs})

add_executable(fuzz_literals_reflexive_real test/fuzz/FuzzLiteralsReflexiveReal.cpp)
set_target_properties(fuzz_literals_reflexive_real PROPERTIES OUTPUT_NAME whiskey-fuzz-literals-reflexive-real)
target_link_libraries(fuzz_literals_reflexive_real ${whiskey_libs})

add_executable(fuzz_literals_reflexive_char test/fuzz/FuzzLiteralsReflexiveChar.cpp)
set_target_properties(fuzz_literals_reflexive_char PROPERTIES OUTPUT_NAME whiskey-fuzz-literals-reflexive-char)
target_link_libraries(fuzz_literals_reflexive_char ${whiskey_libs})

add_executable(fuzz_literals_reflexive_string test/fuzz/FuzzLiteralsReflexiveString.cpp)
set_target_properties(fuzz_literals_reflexive_string PROPERTIES OUTPUT_NAME whiskey-fuzz-literals-reflexive-string)
target_link_libraries(fuzz_literals_reflexive_string ${whiskey_libs})

add_executable(demo_debug_printer test/demo/DemoDebugPrinter.cpp)
set_target_properties(demo_debug_printer PROPERTIES OUTPUT_NAME whiskey-demo-debug-printer)
target_link_libraries(demo_debug_printer ${whiskey_libs})
