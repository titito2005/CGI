#ifndef SELLVIEW_H
#define SELLVIEW_H

#include <iostream>
#include <string>

#include "../../services/parserService/ParserService.h"
#include "../../services/sellService/SellService.h"
#include "../../services/sessionService/SessionService.h"
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class SellView {
    public:
        SellView();
        ~SellView();
        bool responseGET(char * ip);
        bool responsePOST(char * ip);
        void printHTML();
    private:
        //Variables
        ParserService *parserService;
        SellService *sellService;
        HeaderView *headerView;
        FooterView *footerView;
        SessionService* sessionService;
        bool error;
        string errorMessage;
        bool sesion;
        Sell *searchSell = NULL;
        //Methods
};
#endif