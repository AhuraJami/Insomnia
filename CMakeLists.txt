#=========================================================================================
# Project Setup
#=========================================================================================
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Global project name
project(INSOMNIA VERSION 0.0.1 LANGUAGES C CXX)

# Tell CMake not to define WIN32 when building with Cygwin.
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

#=========================================================================================
# Setup CMake Options
#=========================================================================================
#option(PIXIE_BUILD_UNIT_TESTS    "Includes and builds unit tests"                       ON)
#option(PIXIE_RUN_UNIT_TESTS      "Allows for the unit tests to be run at compile time"  OFF)

#=========================================================================================
# Add subdirectories
#=========================================================================================
add_subdirectory(Insomnia)



