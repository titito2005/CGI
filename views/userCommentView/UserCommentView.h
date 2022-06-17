#ifndef USERCOMMENTVIEW_H
#define USERCOMMENTVIEW_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
//MODELS
#include "../../models/userCommentModel/UserComment.h"
//SERVICES
#include "../../services/parserService/ParserService.h"
#include "../../services/userCommentService/UserCommentService.h"
#include "../../services/sessionService/SessionService.h"
//VIEWS
#include "../headerView/HeaderView.h"
#include "../footerView/FooterView.h"

using namespace std;
#define MAX_ARGS 100

class UserCommentView {
    public:
        UserCommentView();
        ~UserCommentView();
        bool responseGET(char* ip);
        bool responsePOST(char* ip);
        void printHTML();
    private:
        //Variables
        ParserService *parserService;
        UserCommentService *userCommentService;
        SessionService* sessionService;
        HeaderView *headerView;
        FooterView *footerView;
        bool userLoged;
        bool error;
        string errorMessage;
};
#endif
