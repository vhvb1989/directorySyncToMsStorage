# Copyright (c) 2020 Victor Vazquez
# SPDX-License-Identifier: MIT

# Main application
cmake_minimum_required (VERSION 3.15)

project(fileSync LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")

include(GetSDK)

find_package(argparse CONFIG REQUIRED)

add_executable (
     storageFileSync
     src/main
     src/helpers.hpp
)

add_compile_definitions(APP_NAME="storageFileSync")

target_link_libraries(storageFileSync PRIVATE azure-core azure-storage-blobs argparse::argparse)

