#
# TODO: Copyright Notice Goes Here
#

cmake_minimum_required(VERSION 3.23)

#
# Starlight-Core Project
#
project(StarlightCore VERSION 1.0.0 LANGUAGES CXX)

#
# Starlight-Core Library
#
set(FILE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sl/utility/Log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sl/utility/MultiByteString.cpp"
)

set(FILE_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Address.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Alias.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Assert.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Character.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Check.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Define.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Enum.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Trait.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Type.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/utility/Convert.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/utility/Hash.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/utility/Integral.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/utility/Log.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/utility/MultiByteString.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/utility/SparseSet.hpp"
)

add_library(StarlightCore STATIC)

set_target_properties(StarlightCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(StarlightCore PUBLIC cxx_std_23)
target_precompile_headers(StarlightCore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch/slpch.hpp")
target_include_directories(StarlightCore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_sources(StarlightCore PRIVATE ${FILE_SOURCES} PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${FILES_INCLUDES})

#
# Testing
#
include(CTest)
if (BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
    add_subdirectory(test)
endif()
