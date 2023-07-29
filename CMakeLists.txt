cmake_minimum_required(VERSION 3.7)
include(FetchContent)

project(AutomataGadget)

set(
    SOURCES
    include/Main.h
    include/cApp.h
    include/InventoryPanel.hpp
    include/SettingsPanel.hpp
    include/PlayerPanel.hpp
    include/WeaponPanel.hpp
    include/defines.h
    include/CheatsPanel.hpp

    src/Main.cpp
    src/cApp.cpp
    src/InventoryPanel.cpp
    src/SettingsPanel.cpp
    src/PlayerPanel.cpp
    src/WeaponPanel.cpp
    src/CheatsPanel.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
target_sources(${PROJECT_NAME} PRIVATE resources/resources.rc)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}) 
include_directories(include)
include_directories(lib/NieRHook/include)

###########    NieRHook   ###########

add_definitions(-DUSING_WINSOCK2)
add_subdirectory(lib/NieRHook)
target_link_libraries(${PROJECT_NAME} NieRHook)
target_include_directories(${PROJECT_NAME} PUBLIC /lib/NieRHook/include)

###########   wxWidgets   ###########

set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
set(wxBUILD_PRECOMP OFF CACHE BOOL "Use precompiled headers")
set(wxBUILD_MONOLITHIC OFF CACHE BOOL "Build a single library")

FetchContent_Declare(
    wxWidgets 
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG        v3.1.4
    GIT_SHALLOW     TRUE
)

FetchContent_GetProperties(wxWidgets)
FetchContent_MakeAvailable(wxWidgets)

target_link_libraries(${PROJECT_NAME}
    wxbase
    wxcore
    wxnet
)