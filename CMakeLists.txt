cmake_minimum_required(VERSION 2.6)
project(raymarcher)

# Prepare the build environment
set(SHARED_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# Add your project files
include_directories("include/")
file(GLOB SRCFILES src/*.cpp src/sdf/*.cpp src/Objects/*.cpp)
list(APPEND SRCFILES main.cpp)

# create executable
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=c++17")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_executable(${PROJECT_NAME} ${SRCFILES})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${SHARED_ROOT}/shared/eigen)
target_link_libraries(${PROJECT_NAME} )
