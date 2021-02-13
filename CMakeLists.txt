cmake_minimum_required(VERSION 3.12)
project(template)

# boilerplate
include(cmake/Common.cmake)

# requirements for imgui
find_package(glfw 3.3 QUIET)
find_package(OpenGL REQUIRED)

# add dependencies
add_subdirectory(external)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make an interface target that will carry standard project settings
add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/Doxygen.cmake)
enable_doxygen()

include(cmake/StaticAnalyzers.cmake)

# options
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

# the code
add_subdirectory(src)
