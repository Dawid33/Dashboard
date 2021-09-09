#ifndef BACKEND_DATABASECONNECTION_H
#define BACKEND_DATABASECONNECTION_H
#include <sqlite3.h>
#include <string>

class DatabaseConnection {
public:
    DatabaseConnection();
    ~DatabaseConnection();
    bool open(std::string filename);
    std::string exec(std::string sql,
                int (*callback)(void*,int,char**,char**),
                void *);
private:
    sqlite3 *db;
};


#endif //BACKEND_DATABASECONNECTION_H
