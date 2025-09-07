cmake_minimum_required(VERSION 3.20)
project(GuessingGame)

set(CMAKE_CXX_STANDARD 17)

# vcpkg integration (agar install kiya hua hai)
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Include Crow headers
include_directories($ENV{VCPKG_ROOT}/installed/x64-windows/include)

# Find Boost system
find_package(Boost REQUIRED COMPONENTS system)

# Add executable
add_executable(server Backend/server.cpp)

# Link libraries
target_link_libraries(server PRIVATE Boost::system ws2_32 Mswsock winmm)
