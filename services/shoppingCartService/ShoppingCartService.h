#ifndef SHOPPINGCARTSERVICE_H
#define SHOPPINGCARTSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include "../../models/shoppingCartModel/ShoppingCart.h"
#include "../Database.h"

using namespace std;

class ShoppingCartService {
    public:
        ShoppingCartService();
        ~ShoppingCartService();
        vector<ShoppingCart> getAllShoppingCartByUserId(string id);
        bool deleteShoppingCartByUserId(string userId);
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif