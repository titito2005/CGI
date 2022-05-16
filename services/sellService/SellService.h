#ifndef SELLSERVICE_H
#define SELLSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <cstring>
#include <stdio.h>

#include "../../models/sellModel/Sell.h"
#include "../Database.h"

using namespace std;

class SellService {
    public:
        SellService();
        ~SellService();
        Sell* getSellById(char* id);
        Sell* getById(int id);
        bool addSell(string GameName, string GameValue, string GameDescription);
        int getSellCountAll();
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
        MYSQL_FIELD *field;
};
#endif
