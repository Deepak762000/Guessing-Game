cmake_minimum_required(VERSION 3.20)
project(GuessingGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

include_directories(${CMAKE_SOURCE_DIR}/Backend)
include_directories($ENV{VCPKG_ROOT}/installed/x64-windows/include)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(server Backend/server.cpp)

target_link_libraries(server PRIVATE Boost::system ws2_32 Mswsock winmm)

target_compile_definitions(server PRIVATE UNICODE _UNICODE _WIN32_WINNT=0x0601)