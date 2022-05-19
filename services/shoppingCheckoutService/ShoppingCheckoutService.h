#ifndef SHOPPINGCHECKOUTSERVICE_H
#define SHOPPINGCHECKOUTSERVICE_H

#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>

#include "../../models/shoppingCheckoutModel/ShoppingCheckout.h"
#include "../Database.h"

using namespace std;

class ShoppingCheckoutService {
    public:
        ShoppingCheckoutService();
        ~ShoppingCheckoutService();
        bool insertCardData(string cardNumber, string cardType, string cardName, string cardExpireDate, string cardPin);
        string encryptionCardData(string pin);
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif