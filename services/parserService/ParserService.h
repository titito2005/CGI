#ifndef PARSERSERVICE_H
#define PARSERSERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <cstring>

#define MAX_ARGS 100

using namespace std;

class ParserService {
    public:
        ParserService();
        ~ParserService();
        //Parser query
        void parseQuery(char* query_string, int query_length);
        char *getQueryArg(const char name[]);
        char *getQueryName(int index);
        char *getQueryValue(int index);
        int getQueryCant();

        //Parser cookies
        void parseCookie();
        char *getCookieArg(const char name[]);
        char *getCookieName(int index);
        char *getCookieValue(int index);
        int getCookieCant();

        //Others
        char* copy_string(char *str, int start, int end);
        void decode_string(char *str);

    private:
        //Query variables
        int queryArgCnt;
        char *queryName[MAX_ARGS];
        char *queryValue[MAX_ARGS];

        //Cookie variables
        int cookieArgCnt;
        char *cookieName[MAX_ARGS];
        char *cookieValue[MAX_ARGS];
};
#endif