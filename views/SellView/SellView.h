#ifndef SELLVIEW_H
#define SELLVIEW_H

#include <iostream>
#include <string>

#include "../../services/parserService/ParserService.h"
#include "../../services/SellService/SellService.h"
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class SellView {
    public:
        SellView();
        ~SellView();
        bool responseGET();
        bool responsePOST();
        void printHTML();
    private:
        //Variables
        ParserService *parserService;
        SellService *sellService;
        HeaderView *headerView;
        FooterView *footerView;

        bool error;
        string errorMessage;
        //Methods
};
#endif