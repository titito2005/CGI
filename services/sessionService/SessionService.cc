#include "SessionService.h"

SessionService::SessionService(){
    //Rand for cookie
    srand((unsigned)time(NULL) * getpid());  
    db = new Database();
    if(db->connectToDatabase()){
        conn = db->getConnection();
    } else {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }   
}

SessionService::~SessionService(){

}

Session* SessionService::getSessionByUserId(char* userId){
    MYSQL_ROW row;
    Session* findSession = NULL;
    char* query = "SELECT * FROM userSession WHERE userId = ";
    char* finalQuery = (char *) malloc(3 + strlen(query)+ strlen(userId));
    strcpy(finalQuery, query);
    strcat(finalQuery, "'");
    strcat(finalQuery, userId);
    strcat(finalQuery, "'");
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)){
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            findSession = new Session();
            findSession->setId(row[0]);
            findSession->setIp(row[1]);
            findSession->setUserId(row[2]);
            findSession->setLoginCookie(row[3]);
            findSession->setCreatedAt(row[4]);
            findSession->setActive(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findSession;
}

Session* SessionService::getSessionByUserCookie(char* cookie){
    MYSQL_ROW row;
    Session* findSession = NULL;
    char* query = "SELECT * FROM userSession WHERE loginCookie = ";
    char* finalQuery = (char *) malloc(3 + strlen(query)+ strlen(cookie));
    strcpy(finalQuery, query);
    strcat(finalQuery, "'");
    strcat(finalQuery, cookie);
    strcat(finalQuery, "'");
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)){
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            findSession = new Session();
            findSession->setId(row[0]);
            findSession->setIp(row[1]);
            findSession->setUserId(row[2]);
            findSession->setLoginCookie(row[3]);
            findSession->setCreatedAt(row[4]);
            findSession->setActive(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findSession;
}

string SessionService::getUserIdByCookie(char* cookie){
    string userId = "";
    Session* findSession = new Session();
    findSession = getSessionByUserCookie(cookie);
    if(findSession!=NULL){
        userId = findSession->getUserId();
    }
    return userId;
}

bool SessionService::validateSession(char* ip, char* cookie){
    bool validateSession = false;
    Session *findSession = getSessionByUserCookie(cookie);
    if(findSession != NULL){
        if(findSession->getIp().compare(ip) == 0){
            validateSession = true;
        }
    }
    return validateSession;
}

bool SessionService::setSessionCookie(string ip, string userId, string cookie){
    bool setCookie = false;
    string query = "INSERT INTO userSession(ip,userId,loginCookie,active)VALUES(";
    query.append("'"+ip+"','"+userId+"','"+cookie+"',TRUE)");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery)){
        setCookie = true;
    }

    return setCookie;
}

bool SessionService::deleteSessionByUserId(string userID);
    bool deleteCookie = false;
    string query = "DELETE FROM userSession WHERE userId = '"+userID+"'";
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery)){
        deleteCookie = true;
    }
    return deleteCookie;
}

string SessionService::generateCookieString(){
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(15);

    for (int i = 0; i < 15; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}