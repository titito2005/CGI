#include "ShoppingCartView.h"

ShoppingCartView::ShoppingCartView(){
    error = false;
    creditCard = false;
    existentCreditCard = false;
    shoppingSuccesfull = false;
    payment = 0;
    errorMessage = "";
    //SERVICES
    sessionService = new SessionService();
    parserService = new ParserService();
    shoppingCartService = new ShoppingCartService();
    sellService = new SellService();
    shoppingCheckoutService = new ShoppingCheckoutService();
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
        // Handle DELETE requests.
        if (strcmp(request_method, "DELETE") == 0){
            responseDELETE(requestAddr);
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
                char* _userId = (char*) malloc(1 + userId.size());
                strcpy(_userId, userId.c_str());
                creditCard = shoppingCheckoutService->getCardByUserId(_userId);
                if(creditCard.size() > 0){
                  existentCreditCard = true;
                }  else {
                  existentCreditCard = false;
                }
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
            cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
        }
    } else {
        //NO HAY COOKIE O NO ES VALIDA
        cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
    }
    return true;
}

bool ShoppingCartView::responsePOST(char* ip){
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //LA COOKIE ES VALIDA PUEDE ENTRAR AL CARRITO
            string userId = sessionService->getUserIdByCookie(sessionID);
            
            if(userId.length()>0){

              char* _userId = (char*) malloc(1 + userId.size());
              strcpy(_userId, userId.c_str());
              creditCard = shoppingCheckoutService->getCardByUserId(_userId);
              if(creditCard.size() > 0){
                existentCreditCard = true;
              } else {
                existentCreditCard = false;
              }
              //EXPECTED VARIABLES FROM QUERY 
              char* cardName = parserService->getQueryArg("cardName");
              char* cardNumber = parserService->getQueryArg("cardNumber");
              char* cardExpireMonth = parserService->getQueryArg("cardExpireMonth");
              char* cardExpireYear = parserService->getQueryArg("cardExpireYear");
              char* cardCVV = parserService->getQueryArg("cardCVV");
              char* checkbox = parserService->getQueryArg("checkbox");

              regex validationOnlyNumbers("[0-9]+");
              regex validateNames("[\w íéóúáñ]+");
              regex validateMonth ("^([1-9]|1[012])$");
              //STRING FOR USERID AND ENCRYPT VARIABLE
              string encryptCVV = "";

              //INITIALIZE FOR RANDOM ACCEPTANCE OF PAYMENT
              payment = shoppingCheckoutService->getRandomPayment();
                  
              if (!existentCreditCard) {
                  //VERIFY THAT FORM HAS COMPLETE DATA
                  if(cardName != NULL && cardNumber != NULL && cardExpireMonth != NULL && cardExpireYear != NULL && cardCVV != NULL ){
                    if (regex_match(cardNumber, validationOnlyNumbers)) {
                      if (regex_match(cardExpireYear, validationOnlyNumbers)) {
                        if (regex_match(cardCVV, validationOnlyNumbers)) {
                          if (regex_match(cardName, validateNames)) {
                            if (regex_match(cardExpireMonth, validateMonth)) {
                              //ENCRYPTION OF PASSWORD FOR INSERTION IN DB
                              encryptCVV = shoppingCheckoutService->encryptionCardData(cardCVV);
                              //CHECKBOX IS CHECKED
                              if (checkbox != NULL){
                                  //INSERTS CARD CREDENTIALS IN DATABASE
                                  if(shoppingCheckoutService->insertCardData(userId, cardName, cardNumber, cardExpireMonth, cardExpireYear, encryptCVV)){ 
                                    shoppingSuccesfull = true;
                                  } else {
                                    error = true;
                                    errorMessage = "Error guardando tarjeta";
                                  }
                              } else {
                                //CHECKBOX IS NOT CHECKED
                                shoppingSuccesfull = true;
                              }
                            } else {
                              error = true;
                              errorMessage = "El mes de vencimiento debe contener un número entre el 1 y 12.";         
                            }
                          } else {
                            error = true;
                            errorMessage = "El nombre de la tarjeta debe incluir sólo letras.";    
                          }
                        } else {
                          error = true;
                          errorMessage = "El CVV debe incluir sólo valores numéricos.";  
                        }
                      } else {
                        error = true;
                        errorMessage = "El año de vencimiento sólo debe incluir valores numéricos.";  
                      }
                    } else {
                      error = true;
                      errorMessage = "El número de la tarjeta sólo debe incluir valores numéricos.";   
                    }
                  } else{
                    //PRINT ERROR INCOMPLETE DATA
                    error = true;
                    errorMessage = "Hay datos incompletos. Por favor inserte todos los datos.";        
                  }
              } else {
                //THE CARD IS ALREADY REGISTERED
                shoppingSuccesfull = true;
              }

              if(error == true || shoppingSuccesfull == true){
                //VERIFY ERRORS AND PRINT THEM || VERIFY CORRECT PAYMENT
                printHTML();
              }
            }
        } else {
          //NO HAY COOKIE O NO ES VALIDA
          cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
        }
    } else {
        //NO HAY COOKIE O NO ES VALIDA
        cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
    }
  return true;
}

bool ShoppingCartView::responseDELETE(char* ip){
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //LA COOKIE ES VALIDA PUEDE BORRAR DEL CARRITO
            string userId = sessionService->getUserIdByCookie(sessionID);
            if(userId.length()>0){
                char* sellId = parserService->getQueryArg("sellId");
                if(sellId!= NULL){
                    string itemId(sellId);
                    shoppingCartService->deleteCartByUserAndItemId(userId, itemId);
                    cout<<"Status: 200 Ok"<<endl;
                } else {
                  cout<<"Status: 400 Bad Request"<<endl;
                }
            } else {
              cout<<"Status: 400 Bad Request"<<endl;
            }
        } else {
          cout<<"Status: 400 Bad Request"<<endl;
        }
    } else {
      cout<<"Status: 400 Bad Request"<<endl;
    }
    return true;
}

void ShoppingCartView::printHTML(){
  double precioTotal = 0;
  cout<<"Content-type:text/html\r\n\r\n";
  cout<<"<!DOCTYPE html>"<<endl;
  cout<<"<html lang='en'>"<<endl;
  cout<<"<head>"<<endl;
    cout<<"<meta charset='utf-8'>"<<endl;
    cout<<"<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"<<endl;

    //<!-- Bootstrap CSS -->
    cout<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"<<endl;
    cout<<"<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>"<<endl;
    cout<<"<link rel='stylesheet' type='text/css' href='/public/common/footer.css'>"<<endl;
    cout<<"<title>Shopping Cart</title>"<<endl;
  cout<<"</head>"<<endl;
  cout<<"<body>"<<endl;
    headerView->printHeaderHTML(true);
    cout<<"<div class='container'>"<<endl;
      cout<<"<h4 class='mt-2'>Carrito de compras</h4>"<<endl;
      cout<<"<div class='row mt-3 mb-3'>"<<endl;
        cout<<"<div class='col-9'>"<<endl;

          if(userItems.size() > 0){
              for(int i = 0; i<userItems.size(); i++){
                cout<<"<div class='card mt-2' style='background-color:#EAEAEA'>"<<endl;
                    cout<<"<div class='card-body d-flex justify-content-between'>"<<endl;
                        cout<<"<h5 class='ml-2 mr-2'>"<<userItems[i].getnameArticle()<<"</h5>"<<endl;
                        cout<<"<p class='ml-1 mr-1'>"<<userItems[i].getDescriptionArticle()<<"</p>"<<endl;
                        cout<<"<h6 class='ml-1 mr-1'> Cantidad: "<<userCart[i].getSellCant()<<"</h6>"<<endl;
                        cout<<"<button onclick='deleteItem("<<userItems[i].getId()<<")' type='button' class='btn btn-danger ml-1 mr-1'>Eliminar</button>"<<endl;
                    cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
              }
          } else {
            cout<<"<h4>En este momento no cuentas con productos en tu carrito</h4>"<<endl;
            cout<<"<h6>¡Vuelve y agrega algunos!</h6>"<<endl;
          }
          cout<<"<button type='button' class='btn btn-secondary mt-3'><a href='/cgi-bin/home'>Volver</a></button>"<<endl;
        cout<<"</div>"<<endl;
        cout<<"<div class='col-3'>"<<endl;
          cout<<"<div class='card mt-2' style='background-color:#EAEAEA'>"<<endl;
            cout<<"<div class='card-body'>"<<endl;
              cout<<"<h5>Resumen</h5>"<<endl;
                if(userItems.size() > 0){
                  for(int i = 0; i<userItems.size(); i++){
                    int cant = stoi(userCart[i].getSellCant());
                    int precio = stoi(userItems[i].getvalueArticle());
                    cout<<"<div class='d-flex mt-1'>"<<endl;
                      cout<<"<h6>"<<userItems[i].getnameArticle()<<"</h6>"<<endl;
                      cout<<"<p> C"<<precio<<"</p>"<<endl;
                      precioTotal += cant * precio;
                    cout<<"</div>"<<endl;
                  }
                  cout<<"<h6>Servicio: C2000</h6>"<<endl;
                  cout<<"<h6>Total Final: "<<precioTotal +2000<<"</h6>"<<endl;
                } else {
                  cout<<"<p>No hay productos actualmente</p>"<<endl;
                  cout<<"<h6>Servicio: C0</h6>"<<endl;
                  cout<<"<h6>Total Final: C0</h6>"<<endl; 
                }
                
            //SHOPPING CHECKOUT STARTS HERE
             cout << "<button type='button' class='btn btn-primary' data-toggle='modal' data-target='#exampleModal'>Checkout de compra </button>" << endl;
              //MODAL
              cout<<"<div class='modal fade' id='exampleModal' tabindex='-1' role='dialog' aria-labelledby='exampleModalLabel' aria-hidden='false'>"<<endl;
                cout<<"<div class='modal-dialog' role='document'>"<<endl;
                  cout<<"<div class='modal-content'>"<<endl;
                    cout<<"<div class='modal-header'>"<<endl;
                      cout<<"<h5 class='modal-title' id='exampleModalLabel'>Pago de compra</h5>"<<endl;
                      cout<<"<button type='button' class='close' data-dismiss='modal' aria-label='Close'>"<<endl;
                        cout<<"<span aria-hidden='true'>&times;</span>"<<endl;
                      cout<<"</button>"<<endl;
                    cout<<"</div>"<<endl;
                    cout<<"<div class='modal-body'>"<<endl;
                    
                  if(existentCreditCard) { //Si existe la tarjeta

                    if(shoppingSuccesfull){ //Compra fue exitosa (1) o no (0)
                      if(payment == 1){
                        cout<<"<div class='alert alert-success' role='alert'>"<<endl;
                            cout<< "<h6>¡Gracias por la compra!</h6>" << endl;
                            cout<< "<p>Su compra fue realizada de manera exitosa.</p>" << endl;
                        cout<<"</div>"<<endl;
                      } else {
                        cout<<"<div class='alert alert-danger' role='alert'>"<<endl;
                            cout<< "<h6>¡Ups, fondos insuficientes!</h6>" << endl;
                            cout<< "<p>Su compra no ha podido ser realizada de manera correcta.</p>" << endl;
                        cout<<"</div>"<<endl;
                      }
                    } else {
                      cout<<"<form action='cart' method='POST'>"<<endl;

                      cout<<"<div class='container'>"<<endl;
                        cout<<"<label for='fname'>Usted ya tiene una tarjeta registrada. Esta es:</label>"<<endl;
                        cout << "<p>" << creditCard << "</p>"<<endl;
                        cout<<"<label for='fname1'>Seleccione pagar si desea continuar.</label>"<<endl;
                      cout<<"</div>"<<endl; 

                      cout<<"<div class='modal-footer'>"<<endl;
                              cout<<"<button data-dismiss='modal' aria-label='Close' class='btn btn-secondary mt-3'>Cancelar</button>"<<endl;
                              cout<<"<button type='submit' class='btn btn-primary mt-3'>Pagar</button>"<<endl;
                            cout<<"</div>"<<endl;
                    cout<<"</form>"<<endl;
                    }
        
                  } else {  //No ha registrado tarjeta

                    if(shoppingSuccesfull){ //Compra fue exitosa
                       if(payment == 1){
                        cout<<"<div class='alert alert-success' role='alert'>"<<endl;
                            cout<< "<h6>¡Gracias por la compra!</h6>" << endl;
                            cout<< "<p>Su compra fue realizada de manera exitosa.</p>" << endl;
                        cout<<"</div>"<<endl;
                      } else {
                        cout<<"<div class='alert alert-danger' role='alert'>"<<endl;
                            cout<< "<h6>¡Ups, fondos insuficientes!</h6>" << endl;
                            cout<< "<p>Su compra no ha podido ser realizada de manera correcta.</p>" << endl;
                        cout<<"</div>"<<endl;
                      }
                    } else {

                      //VERIFIES ERRORS AND PRINT THEM AS WARNINGS
                      if(error){
                          cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                              cout<< errorMessage << endl;
                          cout<<"</div>"<<endl;
                      }
                        cout<<"<div class='container'>"<<endl;
                          cout<<"<label for='fname'>Tarjetas aceptadas</label>"<<endl;
                          cout<<"<div class='icon-container'>"<<endl;
                            cout<<"<i class='fa fa-cc-visa' style='color:navy;'></i>"<<endl;
                            cout<<"<i class='fa fa-cc-amex' style='color:blue;'></i>"<<endl;
                            cout<<"<i class='fa fa-cc-mastercard' style='color:red;'></i>"<<endl;
                            cout<<"<i class='fa fa-cc-discover' style='color:orange;'></i>"<<endl;
                          cout<<"</div>"<<endl;

                            cout<<"<form action='cart' method='POST'>"<<endl;
                              cout<<"<div class='form-group'>"<<endl;
                                  cout<<"<label for='inputName'>Nombre de la tarjeta</label>"<<endl;
                                  cout<<"<input required name='cardName' type='text' minlength='2' maxlength='50' class='form-control' id='inputName'  style='width: 100%;' placeholder='Ingrese el nombre de la tarjeta'>"<<endl;
                              cout<<"</div>"<<endl;

                              cout<<"<div class='form-group'>"<<endl;
                                  cout<<"<label for='inputcardnumber'>Número de la tarjeta</label>"<<endl;
                                  cout<<"<input required name='cardNumber' type='text' minlength='2' maxlength='20' class='form-control'  id='inputcardnumber' style='width: 100%;' placeholder='Ingrese el número de la tarjeta'>"<<endl;
                              cout<<"</div>"<<endl;

                              cout<<"<div class='form-group'>"<<endl;
                                  cout<<"<label for='inputexpmonth'>Mes de vencimiento</label>"<<endl;
                                  cout<<"<input required name='cardExpireMonth' type='text' minlength='2' maxlength='20' class='form-control' id='inputexpmonth'  style='width: 100%;' placeholder='Ingrese el mes de vencimiento 1-12'>"<<endl;
                              cout<<"</div>"<<endl;

                              cout<<"<div class='form-group'>"<<endl;
                                  cout<<"<label for='inputexpyear'>Año de vencimiento</label>"<<endl;
                                  cout<<"<input required name='cardExpireYear' type='text' maxlength='4' minlength='4' class='form-control' id='inputexpyear'  style='width: 100%;' placeholder='Ingrese el año de vencimiento'>"<<endl;
                              cout<<"</div>"<<endl;

                              cout<<"<div class='form-group'>"<<endl;
                                  cout<<"<label for='inputcvv'>CVV</label>"<<endl;
                                  cout<<"<input required name='cardCVV' type='text' minlength='4' maxlength='4' class='form-control' id='inputcvv'  style='width: 100%;' placeholder='Ingrese el CVV, por ejemplo '123''>"<<endl;
                              cout<<"</div>"<<endl;     

                              cout<<"<div class='form-group'>"<<endl;
                                cout<<"<input name='checkbox' class='form-check-input' type='checkbox' value='1' id='flexCheckDefault'>"<<endl;
                                cout<<"<label class='form-check-label' for='flexCheckDefault'> Guardar tarjeta de crédito </label>"<<endl;
                              cout<<"</div>"<<endl;

                              cout<<"<div class='modal-footer'>"<<endl;
                                cout<<"<button data-dismiss='modal' aria-label='Close' class='btn btn-secondary mt-3'>Cancelar</button>"<<endl;
                                cout<<"<button type='submit' class='btn btn-primary mt-3'>Pagar</button>"<<endl;
                              cout<<"</div>"<<endl;
                            cout<<"</div>"<<endl;
                          cout<<"</form>"<<endl;
                    }
                  }
                       cout<<"</div>"<<endl;
                      cout<<"</div>"<<endl;
                    cout<<"</div>"<<endl;
                   
                  cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
              cout<<"</div>"<<endl;
              //CHECKOUT & MODAL END HERE
              
            cout<<"</div>"<<endl;
          cout<<"</div>"<<endl;
        cout<<"</div>"<<endl;
      cout<<"</div>"<<endl;
    cout<<"</div>"<<endl;
    //<!-- Optional JavaScript -->
    //<!-- jQuery first, then Popper.js, then Bootstrap JS -->
    footerView->printFooterHTML(true);
    cout<<"<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"<<endl;
    cout<<"<script src='/public/shoppingCart/shoppingCart.js'></script>"<<endl;
    if (error == true || shoppingSuccesfull == true){
      cout<<"<script src='/public/shoppingCheckout/shoppingCheckout.js'></script>"<<endl;
    }
    cout<<"<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"<<endl;
    cout<<"<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"<<endl;
  cout<<"</body>"<<endl;
  cout<<"</html>"<<endl;
}

int main()
{
    ShoppingCartView cart;
}