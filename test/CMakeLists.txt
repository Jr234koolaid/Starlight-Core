#
# TODO: Copyright Notice Goes Here
#

#
# Starlight-Core-Test
#

include(FetchContent)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(googletest
    URL "https://github.com/google/googletest/archive/283c17563fe7a1111cd7f581aa5d541e8baeff2f.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

set(FILE_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/sl/Test.cpp"
)

include(CTest)
enable_testing()

add_executable(StarlightCoreTest)

set_target_properties(StarlightCoreTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin/$<CONFIG>")

target_compile_features(StarlightCoreTest PUBLIC cxx_std_20)
target_compile_options(StarlightCoreTest PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)
target_compile_definitions(StarlightCoreTest PRIVATE $<$<BOOL:${WIN32}>:UNICODE;_UNICODE>)
target_link_libraries(StarlightCoreTest PRIVATE StarlightCore GTest::gtest_main)
target_precompile_headers(StarlightCoreTest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../pch/slpch.hpp")
target_sources(StarlightCoreTest PRIVATE ${FILE_TEST_SOURCES})

include(GoogleTest)
gtest_discover_tests(StarlightCoreTest)
