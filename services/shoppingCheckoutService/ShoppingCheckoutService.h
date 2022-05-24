#ifndef SHOPPINGCHECKOUTSERVICE_H
#define SHOPPINGCHECKOUTSERVICE_H

#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstring>
#include <unistd.h>

#include "../../models/shoppingCheckoutModel/ShoppingCheckout.h"
#include "../../services/parserService/ParserService.h"
#include "../../services/sessionService/SessionService.h"
#include "../../services/shoppingCartService/ShoppingCartService.h"
#include "../Database.h"

using namespace std;

class ShoppingCheckoutService {
    public:
        ShoppingCheckoutService();
        ~ShoppingCheckoutService();
        ShoppingCheckout* getCheckoutByUserId(char* id);
        bool insertCardData(string idUser, string name, string number, string month, string year, string cvv);
        string encryptionCardData(string stringToBeEncrypted);
        string getCardByUserId(char* userId);
        
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;

};
#endif