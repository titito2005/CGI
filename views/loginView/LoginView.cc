#include "LoginView.h"

LoginView::LoginView()
{
    error = false;
    parser = new ParserService();
    userService = new UserService();
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
    printHTML();
    return true;
}

bool LoginView::responsePOST(char* content_length, char* query_string){
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
    //EXPECTED VARIABLES FROM QUERY
    char* userEmail = parser->getQueryArg("userEmail");
    char* userPassword = parser->getQueryArg("userPassword");
    if(userEmail != NULL){
        if(userPassword != NULL){
            if(userService->verifyPassword(userEmail, userPassword)){
                //MOVE LOCATION TO ANOTHER PAGE, CORRECT LOGIN, ASSIGN COOKIES.
                cout << "Content-type:text/plain\r\n\r\n";
                cout << "USER LOGED" << endl;
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
        //SI HAY ERROR IMPRIME EL HTML DE NUEVO.
        printHTML();
    }
    return true;
}

void LoginView::printHTML(){
    cout << "Content-type:text/html\r\n\r\n";
    count<<"
        <!doctype html>
        <html lang='en'>
        <head>
            <!-- Required meta tags -->
            <meta charset='utf-8'>
            <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>

            <!-- Bootstrap CSS -->
            <link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>
            <!-- Private CSS -->
            <link rel='stylesheet' type='text/css' href='/public/userLogin/userLogin.css'>
            <title>Login page</title>
        </head>
        <body class='d-flex justify-content-center'>
            <div class='card mt-20' style='width: 30rem;'>
                <div class='card-body'>"<<endl;
            if(error){
                cout<<"
                    <div class='alert alert-warning' role='alert'>"
                    << 
                        errorMessage
                    <<"
                    </div>
                "<<endl;
            }
                cout<<"
                    <form action='login' method='POST'>
                        <div class='form-group'>
                        <label for='inputEmail1'>Email</label>
                        <input name='userEmail' type='email' class='form-control' id='inputEmail1' placeholder='Ingrese su correo electrónico'>
                        </div>
                        <div class='form-group'>
                        <label for='inputPassword'>Contraseña</label>
                        <input name='userPassword' type='password' class='form-control' id='inputPassword' placeholder='Ingrese su contraseña'>
                        </div>
                        <button type='submit' class='btn btn-primary'>Iniciar sesión</button>
                    </form>
                </div>
            </div>

            <!-- Optional JavaScript -->
            <!-- jQuery first, then Popper.js, then Bootstrap JS -->
            <script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>
            <script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>
            <script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>
        </body>
        </html>
    "<<endl;
}

int main(){
    LoginView login;
}