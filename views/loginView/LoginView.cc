#include "LoginView.h"

LoginView::LoginView(){

}

LoginView::~LoginView(){

}

bool LoginView::CGI(){
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char *content_length = getenv("CONTENT_LENGTH");


    cout << "Content-type:text/html\r\n\r\n";
    string nombreArchivo = "/home/titito/Desktop/CGI/public/userLogin/userLogin.html";
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
        // Lo vamos imprimiendo
        cout << linea << endl;
    }
    return false;
}

int main(){
    LoginView login;
    login.CGI();
}