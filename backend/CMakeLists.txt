cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 14)
project(backend CXX)
find_program(MAKE NAMES make)

include(ExternalProject)
# don't repeatedly build ExternalProjects.
set_directory_properties(PROPERTIES EP_UPDATE_DISCONNECTED true)
set(DEPS ${PROJECT_BINARY_DIR}/deps)
ExternalProject_Add(target_libcjson
    GIT_REPOSITORY  https://github.com/DaveGamble/cJSON
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${DEPS}
    )
ExternalProject_Add(target_libmicrohttpd
    URL "https://mirror.lyrahosting.com/gnu/libmicrohttpd/libmicrohttpd-0.9.16.tar.gz"
    CONFIGURE_COMMAND "${PROJECT_BINARY_DIR}/target_libmicrohttpd-prefix/src/target_libmicrohttpd/configure" "--prefix=${DEPS}"
    )
ExternalProject_Add(target_sqlite3
    URL "https://sqlite.org/2021/sqlite-autoconf-3360000.tar.gz"
    CONFIGURE_COMMAND "${PROJECT_BINARY_DIR}/target_sqlite3-prefix/src/target_sqlite3/configure" "--prefix=${DEPS}"
    )
add_library(libmicrohttpd SHARED IMPORTED)
set_property(TARGET libmicrohttpd PROPERTY IMPORTED_LOCATION ${DEPS}/lib/libmicrohttpd.so)
add_library(libsqlite3 SHARED IMPORTED)
set_property(TARGET libsqlite3 PROPERTY IMPORTED_LOCATION ${DEPS}/lib/libsqlite3.so)
add_library(libcjson SHARED IMPORTED)
set_property(TARGET libcjson PROPERTY IMPORTED_LOCATION ${DEPS}/lib/libcjson.so)

#backend
add_executable(backend
    test.db
    src/main.cpp
    src/HttpServer.cpp
    src/DatabaseConnection.cpp)
add_dependencies(backend target_libmicrohttpd target_sqlite3 target_libcjson)
target_include_directories(backend PRIVATE include)
target_include_directories(backend PUBLIC ${DEPS}/include)
target_link_libraries(backend PUBLIC libsqlite3 libmicrohttpd libcjson)

# Debug database
add_custom_command(
    OUTPUT test.db
    DEPENDS ${CMAKE_SOURCE_DIR}/scripts/regenerate_db.sh ${CMAKE_SOURCE_DIR}/scripts/test_db.sql
    COMMAND /bin/sh -c 'cp -r ${CMAKE_SOURCE_DIR}/scripts . && ./scripts/regenerate_db.sh'
    )

