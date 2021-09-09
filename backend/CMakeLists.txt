cmake_minimum_required(VERSION 3.20)
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

configure_file(scripts/test_db.sql test_db.sql)

add_custom_command(
    OUTPUT test.db
    DEPENDS ../scripts/regenerate_db.sh test_db.sql
    COMMAND /bin/sh ../scripts/regenerate_db.sh
    )