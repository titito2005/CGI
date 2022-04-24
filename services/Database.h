#ifndef DATABASE_H
#define DATABASE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev

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