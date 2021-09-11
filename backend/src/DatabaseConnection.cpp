#include "DatabaseConnection.h"
#include <sqlite3.h>
#include <memory>
#include <string>
#include <stdio.h>

DatabaseConnection::DatabaseConnection() {}

DatabaseConnection::~DatabaseConnection() {
    sqlite3_close(db);
}

bool DatabaseConnection::open(std::string filename) {
    if(sqlite3_open("test.db", &db)){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }
    return true;
}

std::string DatabaseConnection::exec(std::string sql, int (*callback)(void *, int, char **, char **), void *callback_var) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), callback, callback_var, &zErrMsg);
    if(rc != SQLITE_OK){
        std::string result = std::string(zErrMsg);
        sqlite3_free(zErrMsg);
        return result;
    }
    return std::string("Successfully executed SQL");
}
