#ifndef SESSIONSERVICE_H
#define SESSIONSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "../../models/sessionModel/Session.h"
#include "../Database.h"

using namespace std;

class SessionService {
    public:
        SessionService();
        ~SessionService();
        //Setea una nueva cookie
        bool setSessionCookie(string ip, string userId, string cookie);
        //Retorna el id del usuario de una cookie.
        string getUserIdByCookie(char* cookie);
        //Verifica si existe una sesion con la cookie.
        Session* getSessionByUserCookie(char* cookie);
        //Verifica si existe una sesion para un usuario.
        Session* getSessionByUserId(char* userId);
        //Genera strings de cookies aleatorias.
        string generateCookieString();
        //Verifica si una session es valida.
        bool validateSession(char* ip, char* cookie);
        //Borra una sesion por cookie
        bool deleteSessionByUserId(string userID);
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif
