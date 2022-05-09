#ifndef SELLSERVICE_H
#define SELLSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <cstring>
#include <stdio.h>
#include <memory.h>

#include "../../models/SellModel/Sell.h"
#include "../Database.h"

using namespace std;

class SellService {
    public:
        SellService();
        ~SellService();
        Sell* getSellById(char* id);
        char* createSession(char* SellId);
        char* cretaeCookieSession();
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif

//sprintf(sql_statement, "INSERT INTO USERS_TBL(LOGIN, PASSWORD) VALUES('%s', '%s')", login, password);