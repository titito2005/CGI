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

        }
    }
    //NO HAY COOKIE O NO ES VALIDA
    cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
    return true;
}

bool ShoppingCartView::responsePOST(char* ip){
    cout << "Location: http://localhost/cgi-bin/home\n\n" << endl;
    return true;
}

void ShoppingCartView::printHTML(){

}

int main()
{
    ShoppingCartView cart;
}