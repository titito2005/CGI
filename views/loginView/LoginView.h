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

#include "../../services/parserService/ParserService.h"

using namespace std;

#define MAX_ARGS 100

class LoginView {
    public:
        LoginView();
        ~LoginView();
        bool responseGET();
        bool responsePOST(char* content_length, char* query_string);
    private:
        //Variables
        ParserService *parser;
        //Methods
};
#endif