#include "UserCommentView.h"

UserCommentView::UserCommentView(){
    userLoged = false;
    error = false;
    errorMessage = "";
    //SERVICE
    parserService = new ParserService();
    userCommentService = new UserCommentService();
    sessionService = new SessionService();
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
        if(!parserService->verifyRequest(query_string)) {
            parserService->parseQuery(query_string, query_length);
        } else {
            cout<<"Status: 400 Bad Request"<<endl;
        }
    }
    //PARSE COOKIES
    if(cookie_string != NULL){
        if(!parserService->verifyRequest(cookie_string)) {
            cookie_length = strlen(cookie_string);
            parserService->parseCookie(cookie_string, cookie_length);
        } else {
            cout<<"Status: 400 Bad Request"<<endl;
        }
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

UserCommentView::~UserCommentView(){

}

bool UserCommentView::responseGET(char* ip){
    char *sessionID = parserService->getCookieArg("sessionID");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            userLoged=true;
        }
    }
    printHTML();
    return true;
}

bool UserCommentView::responsePOST(char* ip){
    char *comment = parserService->getQueryArg("comment");
    char *sessionID = parserService->getCookieArg("sessionID");
    regex validationText("[a-zA-Z0-9 áéíóúñÑ:.,]*");
    //HAY UNA COOKIE
    if(sessionID != NULL){
        if(sessionService->validateSession(ip, sessionID)){
            userLoged=true;
        }
    }
    if(comment != NULL){
        if (regex_match(comment, validationText)) {
          if(strlen(comment) <= 1000){
              userCommentService->addComment(comment);
          } else {
            cout << "Location: http://172.24.131.194/cgi-bin/home\n\n" << endl;
          }
        } else {
          error = true;
          errorMessage = "El comentario sólo debe contener letras y números.";
        }
    }
    printHTML();
    return true;
}

void UserCommentView::printHTML(){
    vector<UserComment> userComments = userCommentService->getAllUserComments();
    cout<<"Content-type:text/html\r\n\r\n";
    cout<<"<!DOCTYPE html>"<<endl;
    cout<<"<html lang='en'>"<<endl;
    cout<<"<head>"<<endl;
        cout<<"<meta charset='utf-8'>"<<endl;
        cout<<"<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>"<<endl;

        cout<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>"<<endl;
        cout<<"<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>"<<endl;
        cout<<"<link rel='stylesheet' type='text/css' href='/public/common/footer.css'>"<<endl;
        cout<<"<title>Comments</title>"<<endl;
    cout<<"</head>"<<endl;
    cout<<"<body>"<<endl;
        headerView->printHeaderHTML(userLoged);
        cout<<"<div class='container'>"<<endl;
        cout<<"<h3 class='mt-2'>Reportes y comentarios</h3>"<<endl;
        //VERIFIES ERRORS AND PRINT THEM AS WARNINGS
        if(error){
            cout<<"<div class='alert alert-warning' role='alert'>"<<endl;
                cout<< errorMessage << endl;
            cout<<"</div>"<<endl;
        }
        cout<<"<button type='button' class='btn btn-primary mt-3' data-toggle='modal' data-target='#exampleModal'> Enviar nuevo comentario</button>"<<endl;

        cout<<"<div class='modal fade' id='exampleModal' tabindex='-1' role='dialog' aria-labelledby='exampleModalLabel' aria-hidden='true'>"<<endl;
            cout<<"<div class='modal-dialog' role='document'>"<<endl;
            cout<<"<div class='modal-content'>"<<endl;
                cout<<"<div class='modal-header'>"<<endl;
                cout<<"<h5 class='modal-title' id='exampleModalLabel'>Nuevo comentario</h5>"<<endl;
                cout<<"<button type='button' class='close' data-dismiss='modal' aria-label='Close'>"<<endl;
                    cout<<"<span aria-hidden='true'>&times;</span>"<<endl;
                cout<<"</button>"<<endl;
                cout<<"</div>"<<endl;
                cout<<"<div class='modal-body'>"<<endl;
                cout<<"<form class='form-group' action='comments' method='POST'>"<<endl;
                    cout<<"<label for='exampleFormControlTextarea1'>Ingrese su comentario</label>"<<endl;
                    cout<<"<textarea required name='comment' class='form-control' id='exampleFormControlTextarea1' rows='3' placeholder='Ingrese su comentario' minlength='10' maxlength='1000'></textarea>"<<endl;
                    cout<<"<button data-dismiss='modal' aria-label='Close' class='btn btn-secondary mt-3'>Cancelar</button>"<<endl;
                    cout<<"<button type='submit' class='btn btn-primary mt-3'>Enviar comentario</button>"<<endl;
                cout<<"</form>"<<endl;
                cout<<"</div>"<<endl;
            cout<<"</div>"<<endl;
            cout<<"</div>"<<endl;
        cout<<"</div>"<<endl;

        cout<<"<h5 class='mt-5'>Comentarios anteriores</h5>"<<endl;
        if(userComments.size() > 0){
              for(int i = 0; i<userComments.size(); i++){
                cout<<"<div class='card mt-2 mb-2'>"<<endl;
                    cout<<"<div class='card-body'>"<<endl;
                        cout<<"<h6 class='card-title'>Fecha: "<< userComments[i].getCreatedAt() <<"</h6>"<<endl;
                        cout<<"<p class='card-text'>"<< userComments[i].getComment() <<"</p>"<<endl;
                    cout<<"</div>"<<endl;
                cout<<"</div>"<<endl;
              }
        } else {
            cout<<"<h5 class='mt-5'>Actualmente no hay comentarios</h5>"<<endl;
        }

        cout<<"</div>"<<endl;
        footerView->printFooterHTML(userLoged);
        cout<<"<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>"<<endl;
        cout<<"<script src='https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>"<<endl;
        cout<<"<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>"<<endl;
    cout<<"</body>"<<endl;
    cout<<"</html>"<<endl;
}

int main(){
    UserCommentView userCommentView;
}
