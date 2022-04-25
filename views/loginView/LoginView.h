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

using namespace std;

class LoginView {
    public:
        LoginView();
        ~LoginView();
        bool CGI();
    private:
        //Variables
        //Methods
};
#endif