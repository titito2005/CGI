#include "ShoppingCartView.h"

ShoppingCartView::ShoppingCartView(){
    error = false;
    //SERVICES
    sessionService = new SessionService();
    parserService = new ParserService();
    shoppingCartService = new ShoppingCartService();
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

ShoppingCartView::~ShoppingCartView(){

}

bool ShoppingCartView::responseGET(char* ip){
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //LA COOKIE ES VALIDA PUEDE ENTRAR AL CARRITO
            string userId = sessionService->getUserIdByCookie(sessionID);
            if(userId.length()>0){
                //OBTENGO EL SHOPPING CART DEL USUARIO.
                userCart =  shoppingCartService->getAllShoppingCartByUserId(userId);
                if(userCart.size() > 0){
                    for(int i=0; i<userCart.size(); i++ ){
                        string sellId = userCart[i].getSellId();
                        char* itemId = (char *) malloc(1 + sellId.size());
                        strcpy(itemId, sellId.c_str());
                        Sell* userSell = sellService->getSellById(itemId);
                        if(userSell != NULL){
                            userItems.push_back(*userSell);
                        }
                        //free(itemId);
                    }
                }
            }
            printHTML();
        } else {
            //NO HAY COOKIE O NO ES VALIDA
            cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
        }
    } else {
        //NO HAY COOKIE O NO ES VALIDA
        cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
    }
    return true;
}

bool ShoppingCartView::responsePOST(char* ip){
    cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
    return true;
}

void ShoppingCartView::printHTML(){
cout<<"Content-type:text/html\r\n\r\n";
cout<<"<!DOCTYPE html>"<<endl;
cout<<"<html lang='en'>"<<endl;
  cout<<"<head>"<<endl;
    cout<<"<meta charset='utf-8'>"<<endl;
    cout<<"<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"<<endl;

    //<!-- Bootstrap CSS -->
    cout<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"<<endl;
    cout<<"<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>"<<endl;
    cout<<"<title>Shopping Cart</title>"<<endl;
  cout<<"</head>"<<endl;
  cout<<"<body>"<<endl;
    headerView->printHeaderHTML(true);
    cout<<"<div class='container'>"<<endl;
      cout<<"<h4 class='mt-2'>Carrito de compras</h4>"<<endl;
      cout<<"<a class='mt-2' href='#'>Seguir comprando</a>"<<endl;
      cout<<"<div class='row mt-3 mb-3'>"<<endl;
        cout<<"<div class='col-9'>"<<endl;

          if(userItems.size() > 0){
              for(int i = 0; i<userItems.size(); i++){
                cout<<"<div class='card mt-2' style='background-color:#EAEAEA'>"<<endl;
                    cout<<"<div class='card-body d-flex justify-content-between'>"<<endl;
                        cout<<"<img src='' alt='hola'>"<<endl;
                        cout<<"<h5>"<<userItems[i].getnameArticle()<<"</h5>"<<endl;
                        cout<<"<p>"<<userItems[i].getDescriptionArticle()<<"</p>"<<endl;
                        cout<<"<h6>"<<userCart[i].getSellCant()<<"Cantidad</h6>"<<endl;
                        cout<<"<button type='button' class='btn btn-danger'>Eliminar producto</button>"<<endl;
                    cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
              }
          }
          cout<<"<button type='button' class='btn btn-secondary mt-3'>Volver</button>"<<endl;
        cout<<"</div>"<<endl;
        cout<<"<div class='col-3'>"<<endl;
          cout<<"<div class='card mt-2' style='background-color:#EAEAEA'>"<<endl;
            cout<<"<div class='card-body'>"<<endl;
              cout<<"<h5>Resumen</h5>"<<endl;
              cout<<"<div class='d-flex mt-1'>"<<endl;
                cout<<"<h6>Producto</h6>"<<endl;
                cout<<"<p>Cantidad</p>"<<endl;
                cout<<"<h6>precio</h6>"<<endl;
              cout<<"</div>"<<endl;
              cout<<"<div class='d-flex mt-1'>"<<endl;
                cout<<"<h6>Total</h6>"<<endl;
                cout<<"<h6>precio</h6>"<<endl;
              cout<<"</div>"<<endl;
              cout<<"<button type='button' class='btn btn-primary'>Finalizar compra</button>"<<endl;
            cout<<"</div>"<<endl;
          cout<<"</div>"<<endl;
        cout<<"</div>"<<endl;
      cout<<"</div>"<<endl;
    cout<<"</div>"<<endl;
    //<!-- Optional JavaScript -->
    //<!-- jQuery first, then Popper.js, then Bootstrap JS -->
    footerView->printFooterHTML();
    cout<<"<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"<<endl;
    cout<<"<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"<<endl;
    cout<<"<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"<<endl;
  cout<<"</body>"<<endl;
cout<<"</html>"<<endl;
}

int main()
{
    ShoppingCartView cart;
}