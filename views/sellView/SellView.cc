#include "SellView.h"

SellView::SellView()
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

SellView::~SellView()
{
}

bool SellView::responseGET(char* ip)
{
    sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //LA COOKIE ES VALIDA PUEDE ENTRAR AL CARRITO
            sesion=true;
            printHTML();
        } else {
            //NO HAY COOKIE O NO ES VALIDA
            //cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
            sesion=false;
            printHTML();
        }
    } else {
        //NO HAY COOKIE O NO ES VALIDA
        //cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
        sesion=false;
        printHTML();
    }
    return true;
}

bool SellView::responsePOST(char* ip)
{
    char* searchName = parserService->getQueryArg("SearchName");
    char* sellId = parserService->getQueryArg("SellId");
    if(searchName != NULL){
        searchSell=sellService->sellByName(searchName);
        if(searchSell!=NULL){
            printHTML();
        } else {
            error = true;
            errorMessage = "No se encontro resultados";
            printHTML();
        }
    }
    else if(sellId != NULL){
        if(sessionID!=NULL){
            Session* userId=sessionService->getSessionByUserCookie(sessionID);
            shoppingCartService->addShoppingCart(sellId,userId->getUserId());
            printHTML();
        }
        else{
            error=true;
            errorMessage = "error al agregar al carrito";
            printHTML();
        }
    }
    else {
        error = true;
        errorMessage = "No ingreso datos ";
        printHTML();
    }

    return true;
}

void SellView::printHTML()
{
    // FALTA IMPRIMIR HEADER Y FOOTER
    int SellCount = 0;
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<!doctype html>" << endl;
    cout << "<html lang='en'" << endl;
    cout << "<head>" << endl;
        cout << "<meta charset='utf-8'>" << endl;
        cout << "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>" << endl;
        cout << "<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>" << endl;
        cout << "<link rel='stylesheet' type='text/css' href='/public/home/home.css'>" << endl;
        cout << "<title>home page</title>" << endl;
    cout << "</head>" << endl;
    // PRINT HEADER
    cout << "<body>" << endl;
        headerView->printHeaderHTML(sesion);
        cout<<"<form action='home' method='POST'>"<<endl;
            cout<<"<div class='form-group'>"<<endl;
            cout<<"<label for='inputSearch'>Buscar</label>"<<endl;
            cout<<"<input name='SearchName' type='search' class='form-control' id='inputSearch' placeholder='Ingrese el nombre del videojuego a buscar'>"<<endl;
            cout<<"</div>"<<endl;
            cout<<"<button type='submit' class='btn btn-primary'>Buscar</button>"<<endl;
        cout<<"</form>"<<endl;

        if(error){
                cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                cout<< errorMessage << endl;
                cout<<"</div>"<<endl;
        }
        else if(searchSell!=NULL){
                cout << "<div class='main-content'>" << endl;
                cout << "<div class='card mt-20' style='width: 30rem;'>" << endl;
                cout << "<div class='card-body'>" << endl;
                cout << "<div class=\"card mb-3\">" << endl;
                cout << "<div class=\"card-body\">" << endl;
                cout << "<img src=\"/home/elvis/proyecto/CGI/public/img/index.jpeg\"height=\"200px\"width=\"200px\"/>" << endl;
                cout << "<h5 class=\"card-title\">"+searchSell->getnameArticle()+"</h5>" << endl;
                cout << "<h5 class=\"card-title\">"+searchSell->getvalueArticle()+"</h5>" << endl;
                cout << "<p class=\"card-text\">"+searchSell->getDescriptionArticle()+"</p>" << endl;
                if(sesion){
                    cout<<"<form action='home' method='POST'>"<<endl;
                    cout<<"<div class='claseDiv'>"<<endl;
                    cout<<"<input name='SellId' type='sell' class='form-control' id='sellInput' value=\""+searchSell->getId()+"\">"<<endl;
                    cout<<"</div>"<<endl;
                    cout<<"<button type='submit' class='btn btn-primary'>Agregar al carrito</button>"<<endl;
                    cout<<"</form>"<<endl;
                }
                cout << "</div>" << endl;
                cout << "</div>" << endl;
                cout << "</div>" << endl;
                cout << "</div>" << endl;
                cout << "</div>" << endl;
        }
        else{
            Sell *sell = NULL;
            SellCount =sellService->getSellCountAll();
            for (int i = 1; i <= SellCount; i++)
            {   
                sell = sellService->getById(i);
                cout << "<div class='main-content'>" << endl;
                cout << "<div class='card mt-20' style='width: 30rem;'>" << endl;
                cout << "<div class='card-body'>" << endl;
                cout << "<div class=\"card mb-3\">" << endl;
                cout << "<div class=\"card-body\">" << endl;
                cout << "<img src=\"/home/elvis/proyecto/CGI/public/img/index.jpeg\"height=\"200px\"width=\"200px\"/>" << endl;
                cout << "<h5 class=\"card-title\">"+sell->getnameArticle()+"</h5>" << endl;
                cout << "<h5 class=\"card-title\">"+sell->getvalueArticle()+"</h5>" << endl;
                cout << "<p class=\"card-text\">"+sell->getDescriptionArticle()+"</p>" << endl;
                if(sesion){
                    cout<<"<form action='home' method='POST'>"<<endl;
                    cout<<"<div class='claseDiv'>"<<endl;
                    cout<<"<input name='SellId' type='sell' class='form-control' id='sellInput' value=\""+sell->getId()+"\">"<<endl;
                    cout<<"</div>"<<endl;
                    cout<<"<button type='submit' class='btn btn-primary'>Agregar al carrito</button>"<<endl;
                    cout<<"</form>"<<endl;
                }
                cout << "</div>" << endl;
                cout << "</div>" << endl;
                cout << "</div>" << endl;
                cout << "</div>" << endl;
                cout << "</div>" << endl;
            }
        }
        footerView->printFooterHTML();
        cout << "<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>" << endl;
        cout << "<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>" << endl;
        cout << "<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>" << endl;
    cout << "</body>" << endl;
    cout << "</html>" << endl;
}

int main()
{
    SellView sell;
}