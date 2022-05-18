#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

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
#include <regex>

#include "../../services/parserService/ParserService.h"
#include "../../services/userService/UserService.h"
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;

#define MAX_ARGS 100

class RegisterView {
    public:
        RegisterView();
        ~RegisterView();
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
};
#endif