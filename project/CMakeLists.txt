cmake_minimum_required(VERSION 3.24)
project(search_server)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json tests)
add_executable(search_server src/main.cpp include/ConverterJSON.h include/InvertedIndex.h include/SearchServer.h src/ConverterJSON.cpp src/InvertedIndex.cpp src/SearchServer.cpp
        tests/index_tests.cpp tests/server_tests.cpp)
target_link_libraries(search_server PRIVATE nlohmann_json::nlohmann_json)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(search_server PRIVATE gtest_main)

include(GoogleTest)
#gtest_discover_tests(search_server)
