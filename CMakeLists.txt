#
# TODO: Copyright Notice Goes Here
#

cmake_minimum_required(VERSION 3.23)

#
# Starlight-Core
#
project(StarlightCore VERSION 1.0.0 LANGUAGES CXX)

set(FILE_SOURCES_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sl/Log.cpp"
)

add_library(StarlightCore STATIC "${FILE_SOURCES_CPP}")

set_target_properties(StarlightCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(StarlightCore PUBLIC cxx_std_20)
target_compile_options(StarlightCore PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)

target_precompile_headers(StarlightCore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch/slpch.hpp")

target_include_directories(StarlightCore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
