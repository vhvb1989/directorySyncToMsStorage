# Copyright (c) 2020 Victor Vazquez
# SPDX-License-Identifier: MIT

# Main application
cmake_minimum_required (VERSION 3.15)

project(fileSync LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")

include(GetSDK)

add_executable (
     storageFileSync
     src/main
)

target_link_libraries(storageFileSync PRIVATE azure-core azure-storage-blobs)

