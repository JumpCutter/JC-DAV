cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(CHNAGEME_project_name CXX)
include(cmake/CompileCommands.cmake)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# Should use boost?
option(USE_BOOST "Get boost through conan. Configurable in cmake/boost.cmake" OFF)
include(cmake/boost.cmake)
config_boost()

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES ${BOOST_REQ})
set(CONAN_EXTRA_OPTIONS ${BOOST_OPTS})
include(cmake/Conan.cmake)
run_conan()

add_subdirectory(native)
