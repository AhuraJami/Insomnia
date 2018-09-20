cmake_minimum_required(VERSION 3.8.0)
#=========================================================================================
# Define the target and add all source and header files to it
#=========================================================================================
add_library(Insomnia SHARED Source/Insomnia.cpp)

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(Insomnia::Insomnia ALIAS Insomnia)
#=========================================================================================
# Set the include directories for building and installation
#=========================================================================================
set(INSOMNIA_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/Include/Insomnia)
set(INSOMNIA_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_include_directories(Insomnia
        PUBLIC
            $<INSTALL_INTERFACE:include/insomnia>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        PRIVATE
            ${INSOMNIA_SOURCE_DIR})

#=========================================================================================
# Add Source and header files
#=========================================================================================
target_sources(Insomnia
    PUBLIC
        ${INSOMNIA_INCLUDE_DIR}/Core/Insomnia.h
        ${INSOMNIA_INCLUDE_DIR}/Core/Environments.h

        ${INSOMNIA_INCLUDE_DIR}/Misc/InsomniaExports.h

        ${INSOMNIA_INCLUDE_DIR}/ToyText/Blackjack.h
        ${INSOMNIA_INCLUDE_DIR}/ToyText/Blackjack/Agent.h
        ${INSOMNIA_INCLUDE_DIR}/ToyText/Blackjack/GameManager.h
    PRIVATE
        ${INSOMNIA_SOURCE_DIR}/ToyText/Blackjack/GameManager.cpp
        ${INSOMNIA_SOURCE_DIR}/ToyText/Blackjack/Agent.cpp
)

#=========================================================================================
# Set up Insomnia's compile options
#=========================================================================================
# define EXPORT preprocessors
target_compile_definitions(Insomnia PRIVATE INSOMNIA_DLL_EXPORTS=1)

# Set language standard
target_compile_features(Insomnia
        PRIVATE
            cxx_std_17)

# Add compile flags
target_compile_options(Insomnia
    PRIVATE
        # GNU (g++)
        $<$<CXX_COMPILER_ID:GNU>:$<BUILD_INTERFACE:-Wall; -Wextra; -Wpedantic>>
        # Clang
        $<$<CXX_COMPILER_ID:Clang>:$<BUILD_INTERFACE:-Wall; -Wextra; -Wpedantic>>
        # MSVC
        $<$<CXX_COMPILER_ID:MSVC>:$<BUILD_INTERFACE:/W4; /permissive->>)

# Set output build and output directories so that test executables end up next to dll's
set_target_properties(Insomnia PROPERTIES
    FOLDER                     Insomnia
    ARCHIVE_OUTPUT_DIRECTORY   "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY   "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY   "${CMAKE_BINARY_DIR}/bin")
        
#=========================================================================================
# Add thirdparty libraries
#=========================================================================================
add_subdirectory(ThirdParty/Pixie EXCLUDE_FROM_ALL)
target_link_libraries(Insomnia PUBLIC Pixie::Pixie)
set(PIXIE_BUILD_UNIT_TESTS  OFF  CACHE  BOOL  "Includes and builds unit tests" FORCE)

#=========================================================================================
# Enable Examples
#=========================================================================================
add_subdirectory(Example)