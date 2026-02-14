cmake_minimum_required(VERSION 3.16)
project(RockScissorsPaperGame VERSION 1.0.0 LANGUAGES CXX)

# ── C++17 standard ──────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Kernel static library (pure logic – no GUI dependency) ──────────
file(GLOB_RECURSE KERNEL_SOURCES "src/kernel/*.cpp")
file(GLOB_RECURSE KERNEL_HEADERS "src/kernel/*.h")

add_library(kernel STATIC ${KERNEL_SOURCES} ${KERNEL_HEADERS})
target_include_directories(kernel PUBLIC ${CMAKE_SOURCE_DIR}/src)

# ── Console entry-point (no SFML needed) ────────────────────────────
add_executable(rsp_console main.cpp)
target_link_libraries(rsp_console PRIVATE kernel)

# ── Unit tests ──────────────────────────────────────────────────────
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(rsp_tests ${TEST_SOURCES})
target_link_libraries(rsp_tests PRIVATE kernel)
target_include_directories(rsp_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_test(NAME UnitTests COMMAND rsp_tests)

# ── GUI target (opt-in when SFML is available) ──────────────────────
option(BUILD_GUI "Build the SFML-based GUI front-end" OFF)

if(BUILD_GUI)
    # Hint: SFML installed under MinGW64 (C:/mingw64)
    # Install with: pacman -S mingw-w64-x86_64-sfml  (MSYS2)
    # Or extract SFML manually to C:/mingw64
    list(APPEND CMAKE_PREFIX_PATH "C:/mingw64")

    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

    file(GLOB_RECURSE GUI_SOURCES "src/gui/*.cpp")
    add_executable(rsp_gui ${GUI_SOURCES})
    target_link_libraries(rsp_gui PRIVATE kernel sfml-graphics sfml-window sfml-system)
    target_include_directories(rsp_gui PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()
