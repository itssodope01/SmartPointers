cmake_minimum_required(VERSION 3.10.0)
project(programming_languages_2 VERSION 0.3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
# fetch google tests
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b796f7d # release-v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_compile_options(
  -Wall
  -Wextra
  -Werror
  -Weffc++
  -Wunused
  -Wpedantic
  -Wnarrowing
  -Wlogical-op
  -Wcast-align
  -Wconversion
  -Winvalid-pch
  -Wuseless-cast
  -Wold-style-cast
  -Wredundant-decls
  -Wsign-conversion
  -Wduplicated-cond
  -Wunused-parameter
  -Wnull-dereference
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wduplicated-branches
  -Wmissing-declarations
  -Wmissing-include-dirs
  -Wmisleading-indentation
  -Wmissing-format-attribute)

# add_subdirectory(HelloWorld) add_subdirectory(Basics)
# add_subdirectory(Functions) add_subdirectory(Containers)
# add_subdirectory(Structures) add_subdirectory(Classes)
add_subdirectory(SmartPointers)
