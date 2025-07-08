cmake_minimum_required(VERSION 3.10)
include(CMakePrintHelpers)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Configure.cmake)

# TODO: https://batuhankoc.medium.com/use-cmake-to-create-and-use-dynamic-libraries-5f6498417b3c

# define project name, version, langs, desc
project(libcds
    VERSION 0.0.1
    LANGUAGES C CXX
    DESCRIPTION "Thread-Safe C++ Data Structure Library"
)

# save the home folder for later use
set(PROJECT_HOME ${CMAKE_CURRENT_SOURCE_DIR})

# CMake Variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# set install directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Setting install prefix...")

    if("${CMAKE_GENERATOR}" MATCHES "x64")
        set(CMAKE_INSTALL_PREFIX "${PROJECT_HOME}/bin64" CACHE PATH "Install Prefix" FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX "${PROJECT_HOME}/bin" CACHE PATH "Install Prefix" FORCE)
    endif()
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

cmake_print_variables(CMAKE_INSTALL_PREFIX)

# GNU
# include(GNUInstallDirs)

# enable folders globally
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

# add subdirectories for proper project structure
add_subdirectory(include/libcds) # libcds
add_subdirectory(test/unit) # libcds unit tests
