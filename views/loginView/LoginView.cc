#include "LoginView.h"

LoginView::LoginView()
{
    parser = new ParserService();
    // Read environment variables
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char *content_length = getenv("CONTENT_LENGTH");
    char *requestAddr = getenv("REMOTE_ADDR");
    char *requestCookies = getenv("HTTP_COOKIE");

    // Check request_method variable
    if (request_method != NULL){
        // Handle GET requests
        if (strcmp(request_method, "GET") == 0){
            responseGET();
        }
        // Handle POST requests
        if (strcmp(request_method, "POST") == 0){
            responsePOST(content_length, query_string);
        }
    }
}

LoginView::~LoginView()
{
}

bool LoginView::responseGET(){
    //cout << "Set-Cookie: prueba = holiwis; SameSite=None; Secure" << endl;
    //cout << "Set-Cookie: prueba = holiwis; SameSite=None; Secure" << endl;  
    cout << "Content-type:text/html\r\n\r\n";
    string nombreArchivo = "/var/www/html/public/userLogin/userLogin.html";
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    return true;
}

bool LoginView::responsePOST(char* content_length, char* query_string){
    cout << "Content-type:text/plain\r\n\r\n";
    int query_length = 0;

    if (content_length == NULL){
        return false; 
    }else{
        query_length = atoi(content_length);
    }

    query_string = (char *)malloc(query_length);
    if (query_string == NULL){
        return false;
    }
    for (int pos = 0; pos < query_length; pos++){
        query_string[pos] = fgetc(stdin);
    }

    //PARSE QUERY
    parser->parseQuery(query_string, query_length);
    //PRINT VARIABLES
    cout << parser->getQueryCant() << endl;
    cout << parser->getQueryArg("userEmail") << endl;
    cout << parser->getQueryArg("userPassword") << endl;
    return true;
}

int main(){
    LoginView login;
}