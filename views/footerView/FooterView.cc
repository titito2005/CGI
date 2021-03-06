#include "FooterView.h"

FooterView::FooterView(){

}

FooterView::~FooterView(){

}

void FooterView::printFooterHTML(bool loged){
    cout<<"<footer class='text-center text-white' style='background-color: #0a4275;'>"<<endl;
        cout<<"<div class='container p-4 pb-0'>"<<endl;
            cout<<"<section class=''>"<<endl;
                cout<<"<p class='d-flex justify-content-center align-items-center'>"<<endl;
                    if(loged){
                        cout<<"<button type='button' class='btn btn-outline-light btn-rounded'>"<<endl;
                            cout<<"<a class='nav-link' href='/cgi-bin/cart'>Carrito!</a>"<<endl;
                        cout<<"</button>"<<endl;
                    } else {
                        cout<<"<button type='button' class='btn btn-outline-light btn-rounded'>"<<endl;
                            cout<<"<a class='nav-link' href='/cgi-bin/login'>Inicie sesión!</a>"<<endl;
                        cout<<"</button>"<<endl;
                    }
                cout<<"</p>"<<endl;
            cout<<"</section>"<<endl;
        cout<<"</div>"<<endl;
        cout<<"<div class='text-center p-3' style='background-color: rgba(0, 0, 0, 0.2);'>"<<endl;
            cout<<"© 2022 Copyright:"<<endl;
            cout<<"<a class='text-white' href='#'>FREAKY's GAME STORE</a>"<<endl;
        cout<<"</div>"<<endl;
    cout<<"</footer>"<<endl;
}