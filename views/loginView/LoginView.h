#ifndef LOGINVIEW_H
#define LOGINVIEW_H

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
#include "../../services/userService/UserService.h"
#include "../../services/sessionService/SessionService.h"
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class LoginView {
    public:
        LoginView();
        ~LoginView();
        bool responseGET();
        bool responsePOST(char* ip);
        void printHTML();
    private:
        //Variables
        //VIEWS
        HeaderView *headerView;
        FooterView *footerView;
        //SERVICES
        SessionService *sessionService;
        ParserService *parserService;
        UserService *userService;

        bool error;
        string errorMessage;
        //Methods
};
#endif