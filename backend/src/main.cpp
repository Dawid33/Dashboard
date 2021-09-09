#include "DatabaseConnection.h"
#include "HttpServer.h"
#include <sqlite3.h>

//Docs
int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

int callback(void *NotUsed,int argc ,char **argv,char **azColName) {
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    DatabaseConnection db = DatabaseConnection();
    db.open("test.db");
    db.exec("SELECT * FROM users", callback, nullptr);

    HttpServer server = HttpServer(8888);
    server.start();

    while(!kbhit()) {}
    return 0;
}