cmake_minimum_required(VERSION 2.6)
project(raytracing)

# Prepare the build environment
set(LIB_ROOT "$library/")
# Add project files
include_directories("include/")
set(SRC_DIR "src/")
file(GLOB SRCFILES "${SRC_DIR}/*.cpp")
list(APPEND SRCFILES main.cpp)
# create executable
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_executable(${PROJECT_NAME} ${SRCFILES} ${LIBIGL_EXTRA_SOURCES})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${LIB_ROOT}/eigen-git-mirror ${LIB_ROOT}/json)
