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
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class LoginView {
    public:
        LoginView();
        ~LoginView();
        bool responseGET();
        bool responsePOST();
        void printHTML();
    private:
        //Variables
        ParserService *parserService;
        UserService *userService;
        HeaderView *headerView;
        FooterView *footerView;

        bool error;
        string errorMessage;
        //Methods
};
#endif