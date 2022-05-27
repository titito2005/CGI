#ifndef DATABASE_H
#define DATABASE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <iostream>
#include <cstdlib>
#include <cstring>

class Database {
    public:
        Database();
        ~Database();
        bool connectToDatabase();
        MYSQL* getConnection();
    private:
        //Variables
        MYSQL* conn;
        //Methods
};
#endif