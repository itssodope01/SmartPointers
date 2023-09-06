cmake_minimum_required(VERSION 3.10.0)
project(SmartPointers VERSION 1.0.0)

file(GLOB_RECURSE ${PROJECT_NAME}_HEADER_H CONFIGURE_DEPENDS include/**.h*)
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_CPP CONFIGURE_DEPENDS src/**.cpp)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADER_H}
                            ${${PROJECT_NAME}_SRC_CPP})
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_Example src/main.cpp)
target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_Example PUBLIC include)

# add each test file as separate test executable
file(GLOB_RECURSE ${PROJECT_NAME}_TEST_CPP CONFIGURE_DEPENDS test/**.cpp)
foreach(TEST_FILE ${${PROJECT_NAME}_TEST_CPP})
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_executable(${TEST_NAME} test/${TEST_NAME}.cpp)

  target_link_libraries(${TEST_NAME} gtest_main ${PROJECT_NAME})
  set_target_properties(
    ${TEST_NAME}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${PROJECT_NAME})
  add_test(
    NAME ${TEST_NAME}
    COMMAND ${TEST_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${PROJECT_NAME})
endforeach()
