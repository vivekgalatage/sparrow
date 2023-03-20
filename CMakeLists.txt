cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

option(USE_COMPILER_ERROR "Option to toggle compiler errors. Default: OFF" OFF)

# Add Google Test as an external project
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)

# Add the test executable
file(GLOB TEST_SOURCES "tests/*.cc")

add_executable(sparrow_tests ${TEST_SOURCES})
include_directories(tests include)

if(USE_COMPILER_ERROR)
  target_compile_definitions(sparrow_tests PRIVATE -DUSE_COMPILER_ERROR)
endif()

# Link the test executable with Google Test
target_link_libraries(sparrow_tests gtest_main)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(sparrow_tests)
