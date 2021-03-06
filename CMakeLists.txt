# CMake Configuration
#-----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(whiskey)

message(STATUS "CMake version: ${CMAKE_VERSION}")

# Options
#-----------------------------------------------------------------------
option(enable_verbose "enable_verbose" ON)

# Packages
#-----------------------------------------------------------------------

find_package(LLVM REQUIRED CONFIG 6.0)
message(STATUS "LLVM version: ${LLVM_VERSION}")

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++14 -fno-rtti -Wall -Wabsolute-value -Warray-bounds-pointer-arithmetic -Wassign-enum -Wbad-function-cast -Wbitfield-enum-conversion -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomma -Wcomment -Wconditional-uninitialized -Wcovered-switch-default -Wdeprecated -Wdisabled-macro-expansion -Wdouble-promotion -Wduplicate-enum -Wduplicate-method-arg -Wduplicate-method-match -Wembedded-directive -Wempty-translation-unit -Wfloat-conversion -Wheader-hygiene -Widiomatic-parentheses -Winfinite-recursion -Wmissing-prototypes -Wold-style-cast -Wover-aligned -Woverloaded-virtual -Wpedantic -Wrange-loop-analysis -Wreorder -Wshift-sign-overflow -Wshorten-64-to-32 -Wsign-compare -Wsign-conversion -Wswitch-enum -Wunused-variable")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

# Fix for Ninja/Clang colored errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics -ferror-limit=5")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics -ferror-limit=5")
endif()

# Handling the EnableVerbose option
if (${enable_verbose})
	message(STATUS "Enabling W_VERBOSE")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DW_ENABLE_VERBOSE")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DW_ENABLE_VERBOSE")
endif()

# File lists
#-----------------------------------------------------------------------

llvm_map_components_to_libnames(llvm_libs support core irreader mcjit native)

file(GLOB_RECURSE lib_whiskey_ast_files lib/whiskey/AST/*.cpp)
file(GLOB_RECURSE lib_whiskey_codegen_files lib/whiskey/CodeGen/*.cpp)
file(GLOB_RECURSE lib_whiskey_core_files lib/whiskey/Core/*.cpp)
file(GLOB_RECURSE lib_whiskey_lexing_files lib/whiskey/Lexing/*.cpp)
file(GLOB_RECURSE lib_whiskey_messages_files lib/whiskey/Messages/*.cpp)
file(GLOB_RECURSE lib_whiskey_parsing_files lib/whiskey/Parsing/*.cpp)
file(GLOB_RECURSE lib_whiskey_passes_files lib/whiskey/Passes/*.cpp)
file(GLOB_RECURSE lib_whiskey_printing_files lib/whiskey/Printing/*.cpp)
file(GLOB_RECURSE lib_whiskey_source_files lib/whiskey/Source/*.cpp)
file(GLOB_RECURSE lib_whiskey_testing_files lib/whiskey-testing/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_ast_files test/unit/AST/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_codegen_files test/unit/CodeGen/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_core_files test/unit/Core/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_lexing_files test/unit/Lexing/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_messages_files test/unit/Messages/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_parsing_files test/unit/Parsing/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_passes_files test/unit/Passes/*.cpp)
file(GLOB_RECURSE test_unit_whiskey_source_files test/unit/Source/*.cpp)
file(GLOB_RECURSE test_integration_whiskey_files test/integration/*.cpp)
file(GLOB_RECURSE test_feature_whiskey_files test/feature/*.cpp)

# Libraries
#-----------------------------------------------------------------------

add_library(lib_whiskey_ast ${lib_whiskey_ast_files})
set_target_properties(lib_whiskey_ast PROPERTIES OUTPUT_NAME WhiskeyAST)
target_link_libraries(lib_whiskey_ast lib_whiskey_core lib_whiskey_source)

add_library(lib_whiskey_codegen ${lib_whiskey_codegen_files})
set_target_properties(lib_whiskey_codegen PROPERTIES OUTPUT_NAME WhiskeyCodeGen)
target_link_libraries(lib_whiskey_codegen lib_whiskey_ast ${llvm_libs})

add_library(lib_whiskey_core ${lib_whiskey_core_files})
set_target_properties(lib_whiskey_core PROPERTIES OUTPUT_NAME WhiskeyCore)
target_link_libraries(lib_whiskey_core)

add_library(lib_whiskey_lexing ${lib_whiskey_lexing_files})
set_target_properties(lib_whiskey_lexing PROPERTIES OUTPUT_NAME WhiskeyLexing)
target_link_libraries(lib_whiskey_lexing lib_whiskey_source)

add_library(lib_whiskey_messages ${lib_whiskey_messages_files})
set_target_properties(lib_whiskey_messages PROPERTIES OUTPUT_NAME WhiskeyMessages)
target_link_libraries(lib_whiskey_messages lib_whiskey_core lib_whiskey_source)

add_library(lib_whiskey_parsing ${lib_whiskey_parsing_files})
set_target_properties(lib_whiskey_parsing PROPERTIES OUTPUT_NAME WhiskeyParsing)
target_link_libraries(lib_whiskey_parsing lib_whiskey_source)

add_library(lib_whiskey_passes ${lib_whiskey_passes_files})
set_target_properties(lib_whiskey_passes PROPERTIES OUTPUT_NAME WhiskeyPasses)
target_link_libraries(lib_whiskey_passes lib_whiskey_ast)

add_library(lib_whiskey_printing ${lib_whiskey_printing_files})
set_target_properties(lib_whiskey_printing PROPERTIES OUTPUT_NAME WhiskeyPrinting)
target_link_libraries(lib_whiskey_printing lib_whiskey_core lib_whiskey_source)

add_library(lib_whiskey_source ${lib_whiskey_source_files})
set_target_properties(lib_whiskey_source PROPERTIES OUTPUT_NAME WhiskeySource)
target_link_libraries(lib_whiskey_source lib_whiskey_core lib_whiskey_messages)

add_library(lib_whiskey_testing ${lib_whiskey_testing_files})
set_target_properties(lib_whiskey_testing PROPERTIES OUTPUT_NAME WhiskeyTesting)
target_link_libraries(lib_whiskey_testing lib_whiskey_lexing lib_whiskey_parsing lib_whiskey_codegen)

# Unit tests
#-----------------------------------------------------------------------

add_executable(test_unit_whiskey_ast ${test_unit_whiskey_ast_files})
set_target_properties(test_unit_whiskey_ast PROPERTIES OUTPUT_NAME whiskey-test-unit-ast)
target_link_libraries(test_unit_whiskey_ast lib_whiskey_ast gtest)

add_executable(test_unit_whiskey_codegen ${test_unit_whiskey_codegen_files})
set_target_properties(test_unit_whiskey_codegen PROPERTIES OUTPUT_NAME whiskey-test-unit-codegen)
target_link_libraries(test_unit_whiskey_codegen lib_whiskey_codegen gtest)

add_executable(test_unit_whiskey_core ${test_unit_whiskey_core_files})
set_target_properties(test_unit_whiskey_core PROPERTIES OUTPUT_NAME whiskey-test-unit-core)
target_link_libraries(test_unit_whiskey_core lib_whiskey_core gtest)

add_executable(test_unit_whiskey_lexing ${test_unit_whiskey_lexing_files})
set_target_properties(test_unit_whiskey_lexing PROPERTIES OUTPUT_NAME whiskey-test-unit-lexing)
target_link_libraries(test_unit_whiskey_lexing lib_whiskey_lexing gtest)

add_executable(test_unit_whiskey_messages ${test_unit_whiskey_messages_files})
set_target_properties(test_unit_whiskey_messages PROPERTIES OUTPUT_NAME whiskey-test-unit-messages)
target_link_libraries(test_unit_whiskey_messages lib_whiskey_messages gtest)

add_executable(test_unit_whiskey_parsing ${test_unit_whiskey_parsing_files})
set_target_properties(test_unit_whiskey_parsing PROPERTIES OUTPUT_NAME whiskey-test-unit-parsing)
target_link_libraries(test_unit_whiskey_parsing lib_whiskey_ast lib_whiskey_parsing lib_whiskey_lexing gtest)

add_executable(test_unit_whiskey_passes ${test_unit_whiskey_passes_files})
set_target_properties(test_unit_whiskey_passes PROPERTIES OUTPUT_NAME whiskey-test-unit-passes)
target_link_libraries(test_unit_whiskey_passes lib_whiskey_passes gtest)

add_executable(test_unit_whiskey_source ${test_unit_whiskey_source_files})
set_target_properties(test_unit_whiskey_source PROPERTIES OUTPUT_NAME whiskey-test-unit-source)
target_link_libraries(test_unit_whiskey_source lib_whiskey_source gtest)

# Integration tests
#-----------------------------------------------------------------------

add_executable(test_integration_whiskey ${test_integration_whiskey_files})
set_target_properties(test_integration_whiskey PROPERTIES OUTPUT_NAME whiskey-test-integration)
target_link_libraries(test_integration_whiskey lib_whiskey_testing)

# CMake Tests
#-----------------------------------------------------------------------

enable_testing()

add_test(NAME ctest_unit_whiskey_ast COMMAND ./whiskey-test-unit-ast)
add_test(NAME ctest_unit_whiskey_codegen COMMAND ./whiskey-test-unit-codegen)
add_test(NAME ctest_unit_whiskey_core COMMAND ./whiskey-test-unit-core)
add_test(NAME ctest_unit_whiskey_lexing COMMAND ./whiskey-test-unit-lexing)
add_test(NAME ctest_unit_whiskey_messages COMMAND ./whiskey-test-unit-messages)
add_test(NAME ctest_unit_whiskey_parsing COMMAND ./whiskey-test-unit-parsing)
add_test(NAME ctest_unit_whiskey_passes COMMAND ./whiskey-test-unit-passes)
add_test(NAME ctest_unit_whiskey_source COMMAND ./whiskey-test-unit-source)
add_test(NAME ctest_integration COMMAND ./whiskey-test-integration)
