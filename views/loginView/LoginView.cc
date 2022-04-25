#include "LoginView.h"

LoginView::LoginView(){

}

LoginView::~LoginView(){

}

bool LoginView::CGI(){
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char *content_length = getenv("CONTENT_LENGTH");

    int query_length = 0;

    // Check request_method variable
    if (!request_method == NULL){
        // Handle GET requests
        if (strcmp(request_method, "GET") == 0)
        {
            if (!query_string == NULL){
                if (content_length == NULL){
                    query_length = strlen(query_string); 
                } else {
                    query_length = atoi(content_length);
                }
                cout << "Content-type:text/html\r\n\r\n";
                string nombreArchivo = "/var/www/html/public/userLogin/userLogin.html";
                ifstream archivo(nombreArchivo.c_str());
                string linea;
                // Obtener línea de archivo, y almacenar contenido en "linea"
                while (getline(archivo, linea)) {
                    // Lo vamos imprimiendo
                    cout << linea << endl;
                }
            }
        }
    }


/*
    cout << "Content-type:text/html\r\n\r\n";
    string nombreArchivo = "public/userLogin/userLogin.html";
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
        // Lo vamos imprimiendo
        cout << linea << endl;
    }
    cout<<"fin peticion"<<endl;
    return false;
    */
}

int main(){
    LoginView login;
    login.CGI();
}