#ifndef LOGOUTVIEW_H
#define LOGOUTVIEW_H

#include <iostream>
#include <string>

#include "../../services/parserService/ParserService.h"
#include "../../services/sessionService/SessionService.h"
#include "../../services/userService/UserService.h"

using namespace std;

#define MAX_ARGS 100

class LogoutView {
    public:
        LogoutView();
        ~LogoutView();
        bool responseGET(char* ip);
        bool responsePOST(char* ip);
    private:
        //Variables
        SessionService *sessionService;
        ParserService *parserService;
        UserService *userService;
        //Methods
};
#endif
