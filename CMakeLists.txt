cmake_minimum_required(VERSION 3.26)

# -------------------------------
# Project
# -------------------------------
project(
    spatial_index
    VERSION 0.1.0
    DESCRIPTION "Modern C++23 spatial index library (KD-Tree)"
    LANGUAGES CXX
)

# -------------------------------
# Global C++ Settings
# -------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Useful defaults
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------
# Library Target
# -------------------------------
add_library(spatial_index INTERFACE)

target_include_directories(spatial_index
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(spatial_index
    INTERFACE
        cxx_std_23
)

# -------------------------------
# Warnings (Consumers Inherit These)
# -------------------------------
if (MSVC)
    target_compile_options(spatial_index
        INTERFACE
            /W4
            /permissive-
    )
else()
    target_compile_options(spatial_index
        INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
    )
endif()

# -------------------------------
# Options
# -------------------------------
# option(SPATIAL_INDEX_BUILD_EXAMPLES "Build examples" ON)
# option(SPATIAL_INDEX_BUILD_TESTS "Build tests" ON)
# option(SPATIAL_INDEX_BUILD_BENCHMARKS "Build benchmarks" OFF)

# -------------------------------
# Subdirectories
# -------------------------------
# if (SPATIAL_INDEX_BUILD_EXAMPLES)
#     add_subdirectory(examples)
# endif()

# if (SPATIAL_INDEX_BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

# if (SPATIAL_INDEX_BUILD_BENCHMARKS)
#     add_subdirectory(benchmarks)
# endif()
