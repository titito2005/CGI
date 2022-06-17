#include "RegisterView.h"

RegisterView::RegisterView()
{
    error = false;
    errorMessage = "";
    parserService = new ParserService();
    userService = new UserService();
    sessionService = new SessionService();
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

RegisterView::~RegisterView()
{
}

bool RegisterView::responseGET(char* ip){
    char *sessionID = parserService->getCookieArg("sessionID");
    //THERE IS A COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //IF THE COOKIE IS VALID, IT SHOULDN'T ENTER IN LOGIN
            cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
        }
    }
    printHTML();
    return true;
}

bool RegisterView::responsePOST(char* ip){
    bool userLoged = false;
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            //LA COOKIE ES VALIDA NO DEBERIA ENTRAR A LOGIN.
            userLoged = true;
            cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
        }
    }

    if(!userLoged) {
      //EXPECTED VARIABLES FROM QUERY
      char* userName = parserService->getQueryArg("userName");
      char* userLastNames = parserService->getQueryArg("userLastNames");
      char* userEmail = parserService->getQueryArg("userEmail");
      char* userPassword = parserService->getQueryArg("userPassword");
      char* userPhoneNumber = parserService->getQueryArg("userPhoneNumber");
      char* userDirection = parserService->getQueryArg("userDirection");
      //REGEX VALIDATIONS FOR REGISTER FORM
      regex validateNames("[a-zA-Z áéíóúñÑ]*");
      regex validationEmail("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
      regex validationPhoneNumber("[0-9]+");
      regex validationText("[a-zA-Z0-9 áéíóúñÑ]*");
      //STRING FOR ENCRYPTION
      string encryptPassword = "";

      //VERIFY THAT FORM HAS COMPLETE DATA
      if(userName != NULL && userLastNames != NULL && userPhoneNumber != NULL && userDirection != NULL && userEmail != NULL && userPassword != NULL){
          //VERIFY IF ANOTHER USER HAS THE SAME EMAIL
          if (userService->verifyEmailExistence(userEmail) == false){
              //VERIFICATIONS OF DATA FORMAT OF THE FORM
              if (regex_match(userName, validateNames) && regex_match(userLastNames, validateNames)) {

                  if (regex_match(userEmail, validationEmail)){

                      if (regex_match(userPhoneNumber, validationPhoneNumber)){

                          if (regex_match(userDirection, validationText)) {

                            if (verifyPassword(userPassword)) {
                                string hashedPassword = "";
                                hash<string> hasher;
                                //ENCRYPTION OF PASSWORD FOR INSERTION IN DB
                                hashedPassword = to_string(hasher(userPassword));
                                userPassword = "";
                                if(strlen(userName) <= 30 && strlen(userLastNames) <= 30 && strlen(userPhoneNumber) <= 8 && strlen(userDirection) <= 1000 && strlen(userEmail) <= 50 && hashedPassword.length() <= 100){
                                //INSERT THE NEW USER DATA TO THE DB
                                if(userService->insertUserRegister(userName, userLastNames, userEmail, hashedPassword, userPhoneNumber, userDirection)){
                                    cout<<"Status: 200 Ok"<<endl;
                                    cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
                                } else {
                                    error = true;
                                    errorMessage = "Error registrando el usuario.";
                                }
                                } else {
                                error = true;
                                errorMessage = "Error registrando el usuario, datos inválidos.";
                                }

                            } else {
                                error = true;
                                errorMessage = "La contraseña debe contener letras mayúscula, minúscula, números y caracteres especiales.";
                            }
                          } else {
                              //PRINT ERROR DIRECTION FORMAT
                              error = true;
                              errorMessage = "La dirección no debe contener caracteres especiales.";
                          }
                      } else {
                          //PRINT ERROR PHONE FORMAT
                          error = true;
                          errorMessage = "El teléfono debe contener sólo números.";
                      }
                  } else {
                      //PRINT ERROR EMAIL FORMAT
                      error = true;
                      errorMessage = "El correo no tiene un formato correcto.";
                  }
              } else {
                  //PRINT ERROR NAME OR LAST NAMES FORMAT
                  error = true;
                  errorMessage = "Los datos para su nombre completo deben tener solo letras.";
              }
          } else {
              //PRINT ERROR EXISTENCE OF EMAIL IN OTHER USER
              error = true;
              errorMessage = "Este correo ya existe, ingrese uno válido.";
          }
      } else {
          //PRINT ERROR INCOMPLETE DATA
          error = true;
          errorMessage = "Hay datos incompletos. Por favor inserte todos los datos solicitados.";
      }

    }

    if(error){
        //VERIFY ERRORS AND PRINT THEM
        printHTML();
    }
    return true;
}

void RegisterView::printHTML(){
    cout << "Content-type:text/html\r\n\r\n";
    cout<<"<!doctype html>"<<endl;
    cout<<"<html lang='en'"<<endl;
        cout<<"<head>"<<endl;
            cout<<"<meta charset='utf-8'>"<<endl;
            cout<<"<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"<<endl;
            cout<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"<<endl;
            cout<<"<link rel='stylesheet' type='text/css' href='/public/userRegister/userRegister.css'>"<<endl;
            cout<<"<link rel='stylesheet' type='text/css' href='/public/common/footer.css'>"<<endl;
            cout<<"<title>User Register page</title>"<<endl;
        cout<<"</head>"<<endl;
        //PRINT HEADER
        cout<<"<body>"<<endl;
            headerView->printHeaderHTML(false);
            cout<<"<div class='main-content'>"<<endl;
                cout<<"<div class='card mt-20' style='width: 30rem;'>"<<endl;
                    cout<<"<div class='card-body'>"<<endl;
                    //VERIFIES ERRORS AND PRINT THEM AS WARNINGS
                    if(error){
                        cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                            cout<< errorMessage << endl;
                        cout<<"</div>"<<endl;
                    }
                        cout<<"<form action='userRegister' method='POST'>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputName'>Nombre</label>"<<endl;
                                cout<<"<input required name='userName' type='text' minlength='2' maxlength='30' class='form-control' id='inputName' placeholder='Ingrese su nombre'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputLastNames'>Apellidos</label>"<<endl;
                                cout<<"<input required name='userLastNames' type='text' minlength='2' maxlength='30' class='form-control' id='inputLastNames' placeholder='Ingrese sus dos apellidos'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputEmail'>Email</label>"<<endl;
                                cout<<"<input required name='userEmail' type='email' minlength='5' maxlength='50' class='form-control' id='inputEmail' placeholder='Ingrese su correo electrónico'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputPassword'>Contraseña</label>"<<endl;
                                cout<<"<input required name='userPassword' type='password' minlength='8' maxlength='20' class='form-control' id='inputPassword' placeholder='Ingrese su contraseña'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputPhoneNumber'>Teléfono</label>"<<endl;
                                cout<<"<input required name='userPhoneNumber' type='text' minlength='8' maxlength='8' class='form-control' id='inputPhoneNumber' placeholder='Ingrese su número de teléfono'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<div class='form-group'>"<<endl;
                                cout<<"<label for='inputDirection'>Dirección</label>"<<endl;
                                cout<<"<input required name='userDirection' type='text' minlength='5' maxlength='1000' class='form-control' id='inputDirection' placeholder='Ingrese su dirección'>"<<endl;
                            cout<<"</div>"<<endl;
                            cout<<"<button type='submit' class='btn btn-primary'>Registrarse</button>"<<endl;
                        cout<<"</form>"<<endl;
                    cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
            cout<<"</div>"<<endl;
            //PRINT FOOTER
            footerView->printFooterHTML(false);
            cout<<"<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"<<endl;
            cout<<"<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"<<endl;
            cout<<"<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"<<endl;
        cout<<"</body>"<<endl;
    cout<<"</html>"<<endl;
}

bool RegisterView::verifyPassword(char* input) {
   string password(input);
   int n = password.length();
   // Checking lower alphabet in string
   bool hasLower = false, hasUpper = false;
   bool hasDigit = false, specialChar = false;
   string normalChars = "abcdefghijklmnopqrstu" "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
   
   for (int i = 0; i < n; i++) {
      if (islower(password[i])) {
        hasLower = true;
      }
      if (isupper(password[i])) {
        hasUpper = true;
      }
      if (isdigit(password[i])) {
        hasDigit = true;
      }
      size_t special = password.find_first_not_of(normalChars);
      if (special != string::npos) {
        specialChar = true;
      }
   }
   if(n>8 && hasLower && hasUpper && hasDigit && specialChar){
       return true;
   }
   return false;
}

int main(){
    RegisterView regist;
}
