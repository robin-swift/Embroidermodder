# The Embroidermodder Project
#

cmake_minimum_required(VERSION 3.16)
project(embroidermodder VERSION 2.0.0 LANGUAGES C CXX)

include(config.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets PrintSupport OpenGLWidgets)

find_package(Git QUIET)
if (GIT_FOUND)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE GIT_SUBMOD_RESULT)
endif()

# Seeing if the lines below emulate this function well enough, since
# current Ubuntu users can't rely on access to Qt 6.3
# qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
include(GNUInstallDirs)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

set(USE_FOLDERS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -g
    -O2
    -Wall
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    add_compile_options(
        -Wextra
        -fprofile-arcs
        -ftest-coverage
    )

    add_link_options(
        -fprofile-arcs
        -ftest-coverage
    )

endif()

#add_subdirectory(extern/SDL2-2.28.5)
#add_subdirectory(extern/freetype-2.13.2)

qt_add_executable(embroidermodder2 WIN32 MACOSX_BUNDLE
    ${CMAKE_SOURCE_DIR}/src/core.c
    ${CMAKE_SOURCE_DIR}/src/data.c
    ${CMAKE_SOURCE_DIR}/src/object_core.c

    ${CMAKE_SOURCE_DIR}/src/interface.cpp
    ${CMAKE_SOURCE_DIR}/src/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/src/objects.cpp
    ${CMAKE_SOURCE_DIR}/src/settings-dialog.cpp
    ${CMAKE_SOURCE_DIR}/src/view.cpp

    ${CMAKE_SOURCE_DIR}/src/embroidermodder.h
    ${CMAKE_SOURCE_DIR}/src/core.h

    ${CMAKE_SOURCE_DIR}/extern/tomlc99/toml.c
    ${CMAKE_SOURCE_DIR}/extern/tomlc99/toml.h

    ${CMAKE_SOURCE_DIR}/extern/libembroidery/embroidery.c
    ${CMAKE_SOURCE_DIR}/extern/libembroidery/embroidery.h

    ${CMAKE_SOURCE_DIR}/assets/assets.qrc
)

include_directories(
    ${CMAKE_SOURCE_DIR}/extern/libembroidery
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(embroidermodder2 PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::PrintSupport
    Qt6::OpenGLWidgets)

if (WIN32)
#set_target_properties(embroidermodder2
#    WIN32_EXECUTIBLE ON
#    MACOS BUNDLE ON)
else(WIN32)
target_link_libraries(embroidermodder2 PRIVATE m)
endif()

install(TARGETS embroidermodder2
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build
)
