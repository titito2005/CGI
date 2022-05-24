#ifndef SHOPPINGCARTVIEW_H
#define SHOPPINGCARTVIEW_H

#include <iostream>
#include <string>
#include <vector>
//MODELS
#include "../../models/sellModel/Sell.h"
#include "../../models/shoppingCartModel/ShoppingCart.h"
#include "../../models/shoppingCheckoutModel/ShoppingCheckout.h"
//SERVICES
#include "../../services/parserService/ParserService.h"
#include "../../services/sellService/SellService.h"
#include "../../services/sessionService/SessionService.h"
#include "../../services/shoppingCartService/ShoppingCartService.h"
#include "../../services/shoppingCheckoutService/ShoppingCheckoutService.h"
//VIEWS
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class ShoppingCartView {
    public:
        ShoppingCartView();
        ~ShoppingCartView();
        bool responseGET(char* ip);
        bool responsePOST(char* ip);
        bool responseDELETE(char* ip);
        void printHTML();
    private:
        //Variables
        ParserService *parserService;
        SellService *sellService;
        ShoppingCartService* shoppingCartService;
        SessionService* sessionService;
        ShoppingCheckoutService* shoppingCheckoutService;
        HeaderView *headerView;
        FooterView *footerView;

        bool error;
        bool shoppingSuccesfull;
        bool existentCreditCard;
        bool checkboxChecked;
        string creditCard;
        string userIdCheckout;
        string errorMessage;
        vector<ShoppingCart> userCart;
        vector<Sell> userItems;
        //Methods
};
#endif