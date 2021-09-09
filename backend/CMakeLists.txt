cmake_minimum_required(VERSION 3.16.3)
project(backend)
set(CMAKE_CXX_STANDARD 14)

find_library(MICRO libmicrohttpd.so REQUIRED)
find_library(SQLITE3 sqlite3 REQUIRED)

add_executable(backend
    test.db
    src/main.cpp
    src/HttpServer.cpp
    src/DatabaseConnection.cpp)
target_include_directories(backend PRIVATE include)
target_link_libraries(backend PUBLIC ${MICRO})
target_link_libraries(backend PUBLIC ${SQLITE3})

add_custom_command(
    OUTPUT test.db
    DEPENDS ${CMAKE_SOURCE_DIR}/scripts/regenerate_db.sh ${CMAKE_SOURCE_DIR}/scripts/test_db.sql
    COMMAND /bin/sh -c 'cp -r ${CMAKE_SOURCE_DIR}/scripts . && ./scripts/regenerate_db.sh'
    )

install(TARGETS backend)