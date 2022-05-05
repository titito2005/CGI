#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <cstring>
#include <stdio.h>
#include <memory.h>

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
        bool verifySession(char* userId);
        char* createSession(char* userId);
        char* cretaeCookieSession();
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif

//sprintf(sql_statement, "INSERT INTO USERS_TBL(LOGIN, PASSWORD) VALUES('%s', '%s')", login, password);