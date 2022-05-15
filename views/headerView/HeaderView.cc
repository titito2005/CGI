#include "HeaderView.h"

HeaderView::HeaderView(){

}

HeaderView::~HeaderView(){

}

void HeaderView::printHeaderHTML(bool loged){
    cout<<"<nav class='navbar navbar-expand-lg navbar-dark' style='background-color: #0a4275;'>"<<endl;
        cout<<"<a class='navbar-brand' href='#'>Nombre de la tienda</a>"<<endl;
        cout<<"<button class='navbar-toggler' type='button' data-toggle='collapse' data-target='#navbarSupportedContent' aria-controls='navbarSupportedContent' aria-expanded='false' aria-label='Toggle navigation'>"<<endl;
            cout<<"<span class='navbar-toggler-icon'></span>"<<endl;
        cout<<"</button>"<<endl;
        cout<<"<div class='collapse navbar-collapse' id='navbarSupportedContent'>"<<endl;
            cout<<"<ul class='navbar-nav mr-auto'>"<<endl;
                cout<<"<li class='nav-item active'>"<<endl;
                    cout<<"<a class='nav-link' href='#'>Inicio</a>"<<endl;
                cout<<"</li>"<<endl;
                //SI ESTA LOGEADO
                if(loged){
                cout<<"<li class='nav-item active'>"<<endl;
                    cout<<"<a class='nav-link' href='#'>Agregar producto</a>"<<endl;
                cout<<"</li>"<<endl;
                }
            cout<<"</ul>"<<endl;
            cout<<"<div class='form-inline my-2 my-lg-0'>"<<endl;
                cout<<"<ul class='navbar-nav mr-auto'>"<<endl;
                //SI ESTA LOGEADO
                if(loged){
                    cout<<"<li class='nav-item active'>"<<endl;
                        cout<<"<a class='nav-link' href='#'>Carrito</a>"<<endl;
                    cout<<"</li>"<<endl;
                    cout<<"<li class='nav-item active'>"<<endl;
                        cout<<"<a class='nav-link' href='#'>Cerrar sesión</a>"<<endl;
                    cout<<"</li>"<<endl;  
                } else {
                    //NO ESTA LOGEADO
                    cout<<"<li class='nav-item active'>"<<endl;
                        cout<<"<a class='nav-link' href='#'>Iniciar sesión</a>"<<endl;
                    cout<<"</li>"<<endl;
                    cout<<"<li class='nav-item active'>"<<endl;
                        cout<<"<a class='nav-link' href='#'>Registrarse</a>"<<endl;
                    cout<<"</li>"<<endl;    
                }
                cout<<"</ul>"<<endl;
            cout<<"</div>"<<endl;
        cout<<"</div>"<<endl;
    cout<<"</nav>"<<endl;
}