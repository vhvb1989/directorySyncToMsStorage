# Get Storage SDK from source
include(FetchContent)
FetchContent_Declare(cppstoragesdk
    GIT_REPOSITORY      https://github.com/Azure/azure-sdk-for-cpp.git
    GIT_TAG             azure-template_1.0.0-beta.3)
FetchContent_GetProperties(cppstoragesdk)
if(NOT cppstoragesdk_POPULATED)
    FetchContent_Populate(cppstoragesdk)
    add_subdirectory(${cppstoragesdk_SOURCE_DIR} ${cppstoragesdk_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
