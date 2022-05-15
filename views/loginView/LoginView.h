#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <iostream>
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
        bool responseGET(char* ip);
        bool responsePOST(char* ip);
        bool createCookie(char* ip, char* email);
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