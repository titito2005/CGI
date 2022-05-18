#ifndef ADDVIEW_H
#define ADDVIEW_H

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
#include "../../services/sessionService/SessionService.h"
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class AddView {
    public:
        AddView();
        ~AddView();
        bool responseGET(char *);
        bool responsePOST(char *);
        void printHTML();
    private:
          //Variables
        //VIEWS
        HeaderView *headerView;
        FooterView *footerView;
        //SERVICES
        SessionService *sessionService;
        ParserService *parserService;
        SellService * sellService;

        bool error;
        string errorMessage;
        bool sesion;
        //Methods

};
#endif