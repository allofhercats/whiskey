# CMake Options
#-----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(whiskey)

# Packages
#-----------------------------------------------------------------------

find_package(LLVM REQUIRED CONFIG)

# Subdirectories
#-----------------------------------------------------------------------

add_subdirectory(test/googletest)

# Include/link directories
#-----------------------------------------------------------------------

include_directories(include ${LLVM_INCLUDE_DIRS})

# Definitions
#-----------------------------------------------------------------------

add_definitions(${LLVM_DEFINITIONS})

# Flags
#-----------------------------------------------------------------------

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --std=c11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

# Fix for Ninja/Clang colored errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics -ferror-limit=5")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics -ferror-limit=5")
endif()

# File lists
#-----------------------------------------------------------------------

llvm_map_components_to_libnames(llvm_libs support core irreader mcjit native)

file(GLOB_RECURSE lib_whiskey_ast_files lib/whiskey/AST/*.cpp)
file(GLOB_RECURSE lib_whiskey_codegen_files lib/whiskey/CodeGen/*.cpp)
file(GLOB_RECURSE lib_whiskey_core_files lib/whiskey/Core/*.cpp)
file(GLOB_RECURSE lib_whiskey_fuzzing_files lib/whiskey/Fuzzing/*.cpp)
file(GLOB_RECURSE lib_whiskey_lexing_files lib/whiskey/Lexing/*.cpp)
file(GLOB_RECURSE lib_whiskey_messages_files lib/whiskey/Messages/*.cpp)
file(GLOB_RECURSE lib_whiskey_parsing_files lib/whiskey/Parsing/*.cpp)
file(GLOB_RECURSE lib_whiskey_passes_files lib/whiskey/Passes/*.cpp)
file(GLOB_RECURSE lib_whiskey_printing_files lib/whiskey/Printing/*.cpp)
file(GLOB_RECURSE lib_whiskey_source_files lib/whiskey/Source/*.cpp)
file(GLOB_RECURSE lib_whiskey_unicode_files lib/whiskey/Unicode/*.cpp)
file(GLOB_RECURSE test_unit_ast_files test/unit/AST/*.cpp)
file(GLOB_RECURSE test_unit_core_files test/unit/Core/*.cpp)
file(GLOB_RECURSE test_unit_lexing_files test/unit/Lexing/*.cpp)
file(GLOB_RECURSE test_unit_parsing_files test/unit/Parsing/*.cpp)
file(GLOB_RECURSE test_unit_passes_files test/unit/Passes/*.cpp)
file(GLOB_RECURSE test_unit_source_files test/unit/Source/*.cpp)
file(GLOB_RECURSE test_integration_files test/integration/*.cpp)
file(GLOB_RECURSE test_feature_files test/feature/*.cpp)

# Libraries
#-----------------------------------------------------------------------

add_library(lib_whiskey_ast ${lib_whiskey_ast_files})
set_target_properties(lib_whiskey_ast PROPERTIES OUTPUT_NAME WhiskeyAST)
target_link_libraries(lib_whiskey_ast lib_whiskey_core lib_whiskey_source bfd)

add_library(lib_whiskey_codegen ${lib_whiskey_codegen_files})
set_target_properties(lib_whiskey_codegen PROPERTIES OUTPUT_NAME WhiskeyCodeGen)

add_library(lib_whiskey_core ${lib_whiskey_core_files})
set_target_properties(lib_whiskey_core PROPERTIES OUTPUT_NAME WhiskeyCore)
target_link_libraries(lib_whiskey_core bfd)

add_library(lib_whiskey_fuzzing ${lib_whiskey_fuzzing_files})
set_target_properties(lib_whiskey_fuzzing PROPERTIES OUTPUT_NAME WhiskeyFuzzing)

add_library(lib_whiskey_lexing ${lib_whiskey_lexing_files})
set_target_properties(lib_whiskey_lexing PROPERTIES OUTPUT_NAME WhiskeyLexing)
target_link_libraries(lib_whiskey_lexing lib_whiskey_source)

add_library(lib_whiskey_messages ${lib_whiskey_messages_files})
set_target_properties(lib_whiskey_messages PROPERTIES OUTPUT_NAME WhiskeyMessages)
target_link_libraries(lib_whiskey_messages lib_whiskey_core lib_whiskey_source bfd)

add_library(lib_whiskey_parsing ${lib_whiskey_parsing_files})
set_target_properties(lib_whiskey_parsing PROPERTIES OUTPUT_NAME WhiskeyParsing)
target_link_libraries(lib_whiskey_parsing lib_whiskey_source)

add_library(lib_whiskey_passes ${lib_whiskey_passes_files})
set_target_properties(lib_whiskey_passes PROPERTIES OUTPUT_NAME WhiskeyPasses)
target_link_libraries(lib_whiskey_passes lib_whiskey_ast)

add_library(lib_whiskey_printing ${lib_whiskey_printing_files})
set_target_properties(lib_whiskey_printing PROPERTIES OUTPUT_NAME WhiskeyPrinting)
target_link_libraries(lib_whiskey_printing lib_whiskey_core lib_whiskey_source bfd)

add_library(lib_whiskey_source ${lib_whiskey_source_files})
set_target_properties(lib_whiskey_source PROPERTIES OUTPUT_NAME WhiskeySource)
target_link_libraries(lib_whiskey_source lib_whiskey_core lib_whiskey_messages bfd)

add_library(lib_whiskey_unicode ${lib_whiskey_unicode_files})
set_target_properties(lib_whiskey_unicode PROPERTIES OUTPUT_NAME WhiskeyUnicode)
# target_link_libraries(lib_whiskey_unicode )

# Unit tests
#-----------------------------------------------------------------------

# add_executable(test_unit_ast ${test_unit_ast_files})
# set_target_properties(test_unit_ast PROPERTIES OUTPUT_NAME whiskey-test-unit-ast)
# target_link_libraries(test_unit_ast lib_whiskey_ast gtest)

# add_executable(test_unit_core ${test_unit_core_files})
# set_target_properties(test_unit_core PROPERTIES OUTPUT_NAME whiskey-test-unit-core)
# target_link_libraries(test_unit_core lib_whiskey_core gtest)

# add_executable(test_unit_lexing ${test_unit_lexing_files})
# set_target_properties(test_unit_lexing PROPERTIES OUTPUT_NAME whiskey-test-unit-lexing)
# target_link_libraries(test_unit_lexing lib_whiskey_lexing gtest)

# add_executable(test_unit_parsing ${test_unit_parsing_files})
# set_target_properties(test_unit_parsing PROPERTIES OUTPUT_NAME whiskey-test-unit-parsing)
# target_link_libraries(test_unit_parsing lib_whiskey_ast lib_whiskey_parsing gtest)

# add_executable(test_unit_passes ${test_unit_passes_files})
# set_target_properties(test_unit_passes PROPERTIES OUTPUT_NAME whiskey-test-unit-passes)
# target_link_libraries(test_unit_passes lib_whiskey_passes gtest)

# add_executable(test_unit_source ${test_unit_source_files})
# set_target_properties(test_unit_source PROPERTIES OUTPUT_NAME whiskey-test-unit-source)
# target_link_libraries(test_unit_source lib_whiskey_source gtest)

# Integration tests
#-----------------------------------------------------------------------

# add_executable(test_integration ${test_integration_files})
# set_target_properties(test_integration PROPERTIES OUTPUT_NAME whiskey-test-integration)
# target_link_libraries(test_integration ${whiskey_libs})

# Feature tests
#-----------------------------------------------------------------------

# add_executable(test_feature ${test_feature_files})
# set_target_properties(test_feature PROPERTIES OUTPUT_NAME whiskey-test-feature)
# target_link_libraries(test_feature ${whiskey_libs})

# Fuzz tests
#-----------------------------------------------------------------------

# add_executable(test_fuzz_lexer_random test/fuzz/FuzzLexerRandom.cpp)
# set_target_properties(test_fuzz_lexer_random PROPERTIES OUTPUT_NAME whiskey-test-fuzz-lexer-random)
# target_link_libraries(test_fuzz_lexer_random lib_whiskey_core lib_whiskey_source lib_whiskey_messages lib_whiskey_lexing gtest)

# add_executable(test_fuzz_lexer_fuzzer_simple test/fuzz/FuzzLexerFuzzerSimple.cpp)
# set_target_properties(test_fuzz_lexer_fuzzer_simple PROPERTIES OUTPUT_NAME whiskey-test-fuzz-lexer-fuzzer-simple)
# target_link_libraries(test_fuzz_lexer_fuzzer_simple lib_whiskey_core lib_whiskey_source lib_whiskey_messages lib_whiskey_lexing lib_whiskey_fuzzing gtest)

# add_executable(test_fuzz_literals_reflexive_uint test/fuzz/FuzzLiteralsReflexiveUInt.cpp)
# set_target_properties(test_fuzz_literals_reflexive_uint PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-uint)
# target_link_libraries(test_fuzz_literals_reflexive_uint lib_whiskey_core lib_whiskey_source lib_whiskey_parsing bfd gtest)

# add_executable(test_fuzz_literals_reflexive_real test/fuzz/FuzzLiteralsReflexiveReal.cpp)
# set_target_properties(test_fuzz_literals_reflexive_real PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-real)
# target_link_libraries(test_fuzz_literals_reflexive_real lib_whiskey_core lib_whiskey_source lib_whiskey_parsing bfd gtest)

# add_executable(test_fuzz_literals_reflexive_char test/fuzz/FuzzLiteralsReflexiveChar.cpp)
# set_target_properties(test_fuzz_literals_reflexive_char PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-char)
# target_link_libraries(test_fuzz_literals_reflexive_char lib_whiskey_core lib_whiskey_source lib_whiskey_parsing bfd gtest)

# add_executable(test_fuzz_literals_reflexive_string test/fuzz/FuzzLiteralsReflexiveString.cpp)
# set_target_properties(test_fuzz_literals_reflexive_string PROPERTIES OUTPUT_NAME whiskey-test-fuzz-literals-reflexive-string)
# target_link_libraries(test_fuzz_literals_reflexive_string lib_whiskey_core lib_whiskey_source lib_whiskey_parsing bfd gtest)

# Demos
#-----------------------------------------------------------------------

# add_executable(demo_debug_printer test/demo/DemoDebugPrinter.cpp)
# set_target_properties(demo_debug_printer PROPERTIES OUTPUT_NAME whiskey-demo-debug-printer)
# target_link_libraries(demo_debug_printer lib_whiskey_core lib_whiskey_ast lib_whiskey_printing)

# CMake Tests
#-----------------------------------------------------------------------

enable_testing()

add_test(NAME ctest_unit_ast COMMAND ./whiskey-test-unit-ast)
add_test(NAME ctest_unit_core COMMAND ./whiskey-test-unit-core)
add_test(NAME ctest_unit_lexing COMMAND ./whiskey-test-unit-lexing)
add_test(NAME ctest_unit_parsing COMMAND ./whiskey-test-unit-parsing)
add_test(NAME ctest_unit_passes COMMAND ./whiskey-test-unit-passes)
add_test(NAME ctest_unit_source COMMAND ./whiskey-test-unit-source)
add_test(NAME ctest_integration COMMAND ./whiskey-test-integration)
add_test(NAME ctest_feature COMMAND ./whiskey-test-feature)
