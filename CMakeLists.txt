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
set(SL_FILE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sl/core/Log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sl/core/MultiByteString.cpp"
)

set(SL_FILE_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Address.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Alias.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Array.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Assert.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Atomic.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Attributes.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Byte.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Character.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Check.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Chrono.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Compare.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Compiler.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Crash.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Deque.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Enum.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/FileSystem.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/ForwardList.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Fstream.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Functional.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Integral.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/IOS.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Istream.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Limits.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/List.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Map.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Memory.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Optional.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Ostream.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Platform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Queue.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Random.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Set.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Span.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Stack.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/String.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/StringView.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/SystemError.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Traits.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Tuple.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/TypeIndex.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/TypeInfo.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/TypeTraits.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/UnorderedMap.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/UnorderedSet.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Utility.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Variant.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/Vector.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sl/core/Log.hpp"
)

add_library(StarlightCore STATIC)

set_target_properties(StarlightCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(StarlightCore PUBLIC cxx_std_23)
target_precompile_headers(StarlightCore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch/slpch.hpp")
target_include_directories(StarlightCore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_sources(StarlightCore PRIVATE ${SL_FILE_SOURCES} PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${SL_FILE_INCLUDES})

#
# Starlight-Core Tests
#
include(CTest)
if (BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
    add_subdirectory(test)
endif()
