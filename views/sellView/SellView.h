#ifndef SELLVIEW_H
#define SELLVIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <cstring>
#include <string>

#include "../../services/parserService/ParserService.h"
#include "../../services/sellService/SellService.h"
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