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
    printHTML();
    return true;
}

bool RegisterView::responsePOST(){
    //EXPECTED VARIABLES FROM QUERY
    char* userName = parserService->getQueryArg("userName");
    char* userLastNames = parserService->getQueryArg("userLastNames");
    char* userEmail = parserService->getQueryArg("userEmail");
    char* userPassword = parserService->getQueryArg("userPassword");
    char* userPhoneNumber = parserService->getQueryArg("userPhoneNumber");
    char* userDirection = parserService->getQueryArg("userDirection");

    if(userName != NULL && userLastNames != NULL && userPhoneNumber != NULL && userDirection != NULL && userEmail != NULL && userPassword != NULL){
        if (userService->verifyEmailExistence(userEmail) == false){ //No existe el usuario x el correo
            if(userService->insertUserRegister(userName, userLastNames, userEmail, userPassword, userPhoneNumber, userDirection)){
            cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
            } else {
                error = true;
                errorMessage = "Error registrando el usuario.";
            }
        } else { //verify es true, o sea que sí existe el correo
            error = true;
            errorMessage = "Este correo ya existe, ingrese uno válido.";
        }
        
    } else {
        error = true;
        errorMessage = "Hay datos incompletos. Por favor inserte todos los datos solicitados.";
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
            cout<<"<link rel='stylesheet' type='text/css' href='/public/userRegister/userRegister.css'>"<<endl;
            cout<<"<title>User Register page</title>"<<endl;
        cout<<"</head>"<<endl;
        //PRINT HEADER
        cout<<"<body>"<<endl;
            headerView->printHeaderHTML(false);
            cout<<"<div class='main-content'>"<<endl;
                cout<<"<div class='card mt-20' style='width: 30rem;'>"<<endl;
                    cout<<"<div class='card-body'>"<<endl;
                    //SI HAY ERROR LO IMPRIMO COMO UN WARNING
                    if(error){
                        cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                            cout<< errorMessage << endl;
                        cout<<"</div>"<<endl;
                    }
                        cout<<"<form action='userRegister' method='POST'>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputName'>Nombre</label>"<<endl;
                                cout<<"<input name='userName' type='name' class='form-control' id='inputName' placeholder='Ingrese su nombre'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputLastNames'>Apellidos</label>"<<endl;
                                cout<<"<input name='userLastNames' type='lastNames' class='form-control' id='inputLastNames' placeholder='Ingrese sus dos apellidos'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputEmail'>Email</label>"<<endl;
                                cout<<"<input name='userEmail' type='email' class='form-control' id='inputEmail' placeholder='Ingrese su correo electrónico'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputPassword'>Contraseña</label>"<<endl;
                                cout<<"<input name='userPassword' type='password' class='form-control' id='inputPassword' placeholder='Ingrese su contraseña'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputPhoneNumber'>Teléfono</label>"<<endl;
                                cout<<"<input name='userPhoneNumber' type='phoneNumber' class='form-control' id='inputPhoneNumber' placeholder='Ingrese su número de teléfono'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputDirection'>Dirección</label>"<<endl;
                                cout<<"<input name='userDirection' type='direction' class='form-control' id='inputDirection' placeholder='Ingrese su dirección'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<button type='submit' class='btn btn-primary'>Registrarse</button>"<<endl;
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