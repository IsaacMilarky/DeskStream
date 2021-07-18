cmake_minimum_required(VERSION 3.10)

#Set the project name
project(DeskStream VERSION 0.01)
enable_testing()

#This part was not explained well in the tutorial.
configure_file(
    "${PROJECT_SOURCE_DIR}/DeskStreamConfig.h.in"
    "${PROJECT_SOURCE_DIR}/DeskStreamConfig.h")

#C++ 11
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

include(LibFindMacros.cmake)

#add_executable(DeskStream main.cpp)

#Remove to remove debug symbols.
set(CMAKE_BUILD_TYPE Debug)
#Hmm, today I will try to compile a boost library (clueless)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

#Include pulseaudio libraries
libfind_pkg_check_modules(LibPulseSimple_PKGCONF libpulse-simple)

find_path(LibPulseSimple_INCLUDE_DIR
    NAMES pulse/simple.h 
    HINTS ${LibPulseSimple_PKGCONF_INCLUDE_DIRS}
)

find_library(LibPulseSimple_LIBRARY
    NAMES pulse-simple
    HINTS ${LibPulseSimple_PKGCONF_LIBRARY_DIRS}
)

set(LibPulseSimple_PROCESS_INCLUDES LibPulseSimple_INCLUDE_DIR)
set(LibPulseSimple_PROCESS_LIBS LibPulseSimple_LIBRARY)
libfind_process(LibPulseSimple)

find_package(Boost 1.75.0 COMPONENTS serialization filesystem)
if(Boost_FOUND AND LibPulseSimple_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${LibPulseSimple_INCLUDE_DIRS})
    add_executable(DeskStream ActiveAudio.cpp main.cpp)
    target_link_libraries(DeskStream ${Boost_LIBRARIES} ${LibPulseSimple_LIBRARIES})

    #For Tests
    #add_executable(test_exec ListItem.cpp priorityTodoQueue.cpp ListItemLoadWrapper.cpp TodoController.cpp test_simp_list.cpp)
    #target_link_libraries(test_exec ${Boost_LIBRARIES})
    #add_test(NAME simpTest COMMAND test_exec)
endif()

target_include_directories(DeskStream PUBLIC
                            "{PROJECT BINARY_DIR}")

