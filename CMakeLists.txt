cmake_minimum_required(VERSION 3.15)

project(computer-science)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused-parameter -Wno-implicit-fallthrough -Wno-unused-function -Wextra -pedantic -O2 -g")

file(GLOB_RECURSE DSA_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE UTILS_SOURCES "${CMAKE_SOURCE_DIR}/lib/*.c")
set(ALL_SOURCES ${DSA_SOURCES} ${UTILS_SOURCES})

add_library(dsa-utils STATIC ${ALL_SOURCES})
target_include_directories(dsa-utils PUBLIC "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.c")

foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TARGET ${TEST_SRC} NAME_WE)
    add_executable(${TARGET} ${TEST_SRC})
    target_link_libraries(${TARGET} PRIVATE dsa-utils)

    if(UNIX)
        target_link_libraries(${TARGET} PRIVATE m)
    endif()
endforeach()
