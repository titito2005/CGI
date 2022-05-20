#include "AddView.h"

AddView::AddView()
{
    error = false;
    //SERVICES
    sessionService = new SessionService();
    parserService = new ParserService();
    sellService = new SellService();
    //VIEWS
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
            responseGET(requestAddr);
        }
        // Handle POST requests
        if (strcmp(request_method, "POST") == 0){
            responsePOST(requestAddr);
        }
    }
}

AddView::~AddView()
{
}

bool AddView::responseGET(char* ip){ 
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //LA COOKIE ES VALIDA PUEDE ENTRAR AL CARRITO
            sesion=true;
            printHTML();
        } else {
            //NO HAY COOKIE O NO ES VALIDA
            cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
            //printHTML();
        }
    } else {
        //NO HAY COOKIE O NO ES VALIDA
        cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
        //printHTML();
    }
    return true;
}

bool AddView::responsePOST(char* ip){
 //EXPECTED VARIABLES FROM QUERY
    char* GameName = parserService->getQueryArg("GameName");
    char* GameValue = parserService->getQueryArg("GameValue");
    char* GameDescription = parserService->getQueryArg("GameDescription");
    //char* img = parserService->getQueryArg("Img");

    if(GameName != NULL && GameValue != NULL && GameDescription != NULL ){
        if(sellService->addSell(GameName, GameValue, GameDescription)){
            cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
        } else {
            error = true;
            errorMessage = "Error al agregar juego";
            printHTML();
        }
    } else {
        error = true;
        errorMessage = "no se relleno toda la informacion";
        printHTML();
    }

    return true;
}

void AddView::printHTML(){
     //FALTA IMPRIMIR HEADER Y FOOTER
    cout << "Content-type:text/html\r\n\r\n";
    cout<<"<!doctype html>"<<endl;
    cout<<"<html lang='en'"<<endl;
        cout<<"<head>"<<endl;
            cout<<"<meta charset='utf-8'>"<<endl;
            cout<<"<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"<<endl;
            cout<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"<<endl;
            cout<<"<link rel='stylesheet' type='text/css' href='/public/home/home.css'>"<<endl;
            cout<<"<link rel='stylesheet' type='text/css' href='/public/common/footer.css'>"<<endl;
            cout<<"<title>Add Sell </title>"<<endl;
        cout<<"</head>"<<endl;
        //PRINT HEADER
        cout<<"<body>"<<endl;
            headerView->printHeaderHTML(sesion);
            cout<<"<div class='main-content'>"<<endl;
                cout<<"<div class='card mt-20' style='width: 30rem;'>"<<endl;
                    cout<<"<div class='card-body'>"<<endl;
                    //SI HAY ERROR LO IMPRIMO COMO UN WARNING
                    if(error){
                        cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                            cout<< errorMessage << endl;
                        cout<<"</div>"<<endl;
                    }
                        cout<<"<form enctype='multipart/form-data' action='addSell' method='POST'>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputName'>Nombre del Juego</label>"<<endl;
                                cout<<"<input name='GameName' type='name' class='form-control' id='inputName' placeholder='Ingrese el nombre del videojuego nombre'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputValue'>Valor del juego </label>"<<endl;
                                cout<<"<input name='GameValue' type='value' class='form-control' id='inputValue' placeholder='Ingrese el valor del juego'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputDescription'>Descripcion</label>"<<endl;
                                cout<<"<input name='GameDescription' type='descripcion' class='form-control' id='inputDescription' placeholder='Ingrese la descripcion'>"<<endl;
                            cout<<"</div>"<<endl;
                            //cout<<"<input name='Img' accept='image/png,image/jpeg' type='file'>"<<endl;
                            cout<<"<button type='submit' class='btn btn-primary'>Agregar</button>"<<endl;
                        cout<<"</form>"<<endl;
                    cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
            cout<<"</div>"<<endl;
            footerView->printFooterHTML(true);
            cout<<"<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"<<endl;
            cout<<"<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"<<endl;
            cout<<"<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"<<endl;
        cout<<"</body>"<<endl;
    cout<<"</html>"<<endl;
}

int main(){
    AddView addSell;
}