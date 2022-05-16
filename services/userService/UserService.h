#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <cstring>
#include <stdio.h>

#include "../../models/userModel/User.h"
#include "../Database.h"

using namespace std;

class UserService {
    public:
        UserService();
        ~UserService();
        User* getUserById(char* id);
        User* getUserByEmail(char* email);
        bool verifyPassword(char* email, char* password);
        string getIdByEmail(char* email);
        bool insertUserRegister(string name, string lastNames, string email, string password, string phoneNumber, string direction);
        bool verifyEmailExistence(char* incomingEmail);
        
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif

//sprintf(sql_statement, "INSERT INTO USERS_TBL(LOGIN, PASSWORD) VALUES('%s', '%s')", login, password);