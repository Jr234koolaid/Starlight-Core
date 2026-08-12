#
# TODO: Copyright Notice Goes Here
#

cmake_minimum_required(VERSION 3.23)

#
# Starlight-Core
#
project(StarlightCore VERSION 1.0.0 LANGUAGES CXX)

set(FILE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sl/Log.cpp"
)

set(FILE_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Alias.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Assert.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Cast.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Check.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Convert.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Define.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Hash.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Integral.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Log.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/SparseSet.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Trait.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Type.hpp"
)

add_library(StarlightCore STATIC)

set_target_properties(StarlightCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(StarlightCore PUBLIC cxx_std_20)
target_compile_options(StarlightCore PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)
target_compile_definitions(StarlightCore PRIVATE $<$<BOOL:${WIN32}>:UNICODE;_UNICODE>)

target_precompile_headers(StarlightCore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch/slpch.hpp")

target_sources(StarlightCore PRIVATE ${FILE_SOURCES} PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${FILES_INCLUDES})

target_include_directories(StarlightCore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
