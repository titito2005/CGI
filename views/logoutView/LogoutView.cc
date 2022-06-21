#include "LogoutView.h"

LogoutView::LogoutView(){
    //SERVICES
    sessionService = new SessionService();
    parserService = new ParserService();
    // Read environment variables
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char *content_length = getenv("CONTENT_LENGTH");
    char *requestAddr = getenv("REMOTE_ADDR");
    char *cookie_string = getenv("HTTP_COOKIE");
    int query_length = 0;
    int cookie_length = 0;

    if (content_length != NULL){
        query_length = atoi(content_length);
        query_string = (char *)malloc(query_length);
        if (query_string != NULL){
            for (int pos = 0; pos < query_length; pos++){
                query_string[pos] = fgetc(stdin);
            }
        }
    }
    //PARSE QUERY
    if(query_string != NULL && content_length != NULL){
        if(!parserService->verifyRequest(query_string)) {
            parserService->parseQuery(query_string, query_length);
        }
    }
    //PARSE COOKIES
    if(cookie_string != NULL){
        if(!parserService->verifyRequest(cookie_string)) {
            cookie_length = strlen(cookie_string);
            parserService->parseCookie(cookie_string, cookie_length);
        }
    }
    // Check request_method variable
    if (request_method != NULL){
        // Handle GET requests
        if (strcmp(request_method, "GET") == 0){
            responseGET(requestAddr);
        }
    }
}

LogoutView::~LogoutView(){

}

bool LogoutView::responseGET(char* ip){
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            string userId = sessionService->getUserIdByCookie(sessionID);
            string email = userService->getEmailById(userId);
            parserService->auditLoginAndLogout(false, email, ip, true);
            //LA COOKIE ES VALIDA LA BORRAMOS DE LA BD
            sessionService->deleteSessionByCookie(sessionID);
            cout<<"Status: 200 Ok"<<endl;
            cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
            return true;
        }
    }
    //REDIRIGIMOS A HOME
    cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
    return true;
}

int main(){
    LogoutView logout;
}
