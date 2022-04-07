cmake_minimum_required(VERSION 3.16)
project(ArduinoGlove)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version" FORCE)

option(UniversalBinary "Build universal binary for mac" OFF)

if (UniversalBinary)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

add_subdirectory(SDKs)
add_subdirectory(Modules)
add_subdirectory(Plugins)

if (${BUILD_JUCE_PROTOTYPE_EXAMPLES})
    add_subdirectory(Apps)
    add_subdirectory(Plugins)
endif()
