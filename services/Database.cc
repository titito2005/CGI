#include "Database.h"

Database::Database(){

}

Database::~Database(){
    mysql_close(conn);
    delete conn;
}
        
bool Database::connectToDatabase(){
    bool connected = true;
    const char* MY_HOSTNAME = "localhost";
    const char* MY_DATABASE = "server";
    const char* MY_USERNAME = "admin";
    const char* MY_PASSWORD = "admin";
    const char* MY_SOCKET = NULL;

    conn = mysql_init(NULL);
    // Establish a MySQL connection
    if (!mysql_real_connect(
            conn,
            MY_HOSTNAME, MY_USERNAME,
            MY_PASSWORD, MY_DATABASE,
            3306, MY_SOCKET, 0)) {
        connected = false;
    }
    return connected;
}

MYSQL* Database::getConnection(){
    return conn;
}