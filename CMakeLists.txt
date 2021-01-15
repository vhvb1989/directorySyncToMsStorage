# Copyright (c) 2020 Victor Vazquez
# SPDX-License-Identifier: MIT

# Main application
cmake_minimum_required (VERSION 3.15)

project(fileSync LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")

include(GetSDK)

add_executable (
     storageFileSync
     src/main
     src/helpers.hpp
)

if(MSVC)
    add_compile_definitions(APP_NAME="storageFileSync.exe")
else()
    add_compile_definitions(APP_NAME="storageFileSync")
endif()

target_link_libraries(storageFileSync azure-storage-blobs)
# target_include_directories(
# storageFileSync
#     PUBLIC
#       ${azure-storage-blobs-cpp_INCLUDE_DIRS}
# )

