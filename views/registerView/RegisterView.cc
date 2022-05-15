#include "RegisterView.h"

RegisterView::RegisterView()
{
    error = false;
    parserService = new ParserService();
    userService = new UserService();
    headerView = new HeaderView();
    footerView = new FooterView();
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
        parserService->parseQuery(query_string, query_length);
    }
    //PARSE COOKIES
    if(cookie_string != NULL){
        cookie_length = strlen(cookie_string);
        parserService->parseCookie(cookie_string, cookie_length);
    }
    // Check request_method variable
    if (request_method != NULL){
        // Handle GET requests
        if (strcmp(request_method, "GET") == 0){
            responseGET();
        }
        // Handle POST requests
        if (strcmp(request_method, "POST") == 0){
            responsePOST();
        }
    }
}

RegisterView::~RegisterView()
{
}

bool RegisterView::responseGET(){
    cout << "Set-Cookie:prueba1=holiwis1; SameSite=None; Secure" << endl;
    cout << "Set-Cookie:prueba2=holiwis2; SameSite=None; Secure" << endl;
    cout << "Set-Cookie:prueba3=holiwis3; SameSite=None; Secure" << endl;    
    printHTML();
    return true;
}

bool RegisterView::responsePOST(){
    //EXPECTED VARIABLES FROM QUERY
    char* userEmail = parserService->getQueryArg("userEmail");
    char* userPassword = parserService->getQueryArg("userPassword");
    if(userEmail != NULL){
        if(userPassword != NULL){
            if(userService->verifyPassword(userEmail, userPassword)){
                //MOVE LOCATION TO ANOTHER PAGE, CORRECT LOGIN, ASSIGN COOKIES.
                cout << "Content-type:text/plain\r\n\r\n";
                cout << "USER LOGED" << endl;
                cout << parserService->getCookieArg("prueba1") << endl;
                cout << parserService->getCookieArg("prueba2") << endl;
                cout << parserService->getCookieArg("prueba3") << endl;
            }else{
                //PRINT ERROR VERIFY PASSWORD
                error = true;
                errorMessage = "El email y la contraseña no coinciden.";
            }
        }else{
            //PRINT ERROR NO PASSWORD
            error = true;
            errorMessage = "No se ha ingresado la contraseña, asegúrese de rellenar todos los espacios.";
        }
    }else{
        //PRINT ERROR NO EMAIL
        error = true;
        errorMessage = "No se ha ingresado el email, asegúrese de rellenar todos los espacios.";
    }

    if(error){
        //SI HAY ERROR IMPRIME EL HTML DE NUEVO CON LOS ERRORES.
        printHTML();
    }
    return true;
}

void RegisterView::printHTML(){
     //FALTA IMPRIMIR HEADER Y FOOTER
    cout << "Content-type:text/html\r\n\r\n";
    cout<<"<!doctype html>"<<endl;
    cout<<"<html lang='en'"<<endl;
        cout<<"<head>"<<endl;
            cout<<"<meta charset='utf-8'>"<<endl;
            cout<<"<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"<<endl;
            cout<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"<<endl;
            cout<<"<link rel='stylesheet' type='text/css' href='/public/userLogin/userLogin.css'>"<<endl;
            cout<<"<title>Login page</title>"<<endl;
        cout<<"</head>"<<endl;
        //PRINT HEADER
        cout<<"<body>"<<endl;
            headerView->printHeaderHTML();
            cout<<"<div class='main-content'>"<<endl;
                cout<<"<div class='card mt-20' style='width: 30rem;'>"<<endl;
                    cout<<"<div class='card-body'>"<<endl;
                    //SI HAY ERROR LO IMPRIMO COMO UN WARNING
                    if(error){
                        cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                            cout<< errorMessage << endl;
                        cout<<"</div>"<<endl;
                    }
                        cout<<"<form action='login' method='POST'>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputEmail1'>Email</label>"<<endl;
                                cout<<"<input name='userEmail' type='email' class='form-control' id='inputEmail1' placeholder='Ingrese su correo electrónico'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputPassword'>Contraseña</label>"<<endl;
                                cout<<"<input name='userPassword' type='password' class='form-control' id='inputPassword' placeholder='Ingrese su contraseña'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<button type='submit' class='btn btn-primary'>Iniciar sesión</button>"<<endl;
                        cout<<"</form>"<<endl;
                    cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
            cout<<"</div>"<<endl;
            footerView->printFooterHTML();
            cout<<"<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"<<endl;
            cout<<"<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"<<endl;
            cout<<"<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"<<endl;
        cout<<"</body>"<<endl;
    cout<<"</html>"<<endl;
}

int main(){
    RegisterView regist;
}