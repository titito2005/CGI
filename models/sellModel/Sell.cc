#include "Sell.h"

Sell::Sell(){
    id = "";
    nameArticle = "";
    valueArticle = "";
    DescriptionArticle = "";
    img = "";
    createdAt = "";
}

Sell::Sell(string _id, string _nameArticle, string _valueArticle, string _DescriptionArticle, string _img, string _createdAt){
    id = _id;
    nameArticle = _nameArticle;
    valueArticle = _valueArticle;
    DescriptionArticle = _DescriptionArticle;
    img=_img;
    createdAt = _createdAt;
}

Sell::~Sell(){
}

void Sell::setId(string _id){
    id = _id;
}

void Sell::setnameArticle(string _nameArticle){
    nameArticle = _nameArticle;
}

void Sell::setvalueArticle(string _valueArticle){
    valueArticle = _valueArticle;
}

void Sell::setDescriptionArticle(string _DescriptionArticle){
    DescriptionArticle = _DescriptionArticle;
}
void Sell::setImg(string _Img){
    img = _Img;
}
void Sell::setCreatedAt(string _createdAt){
    createdAt = _createdAt;
}

string Sell::getId(){
    return id;
}

string Sell::getnameArticle(){
    return nameArticle;
}

string Sell::getvalueArticle(){
    return valueArticle;
}

string Sell::getDescriptionArticle(){
    return DescriptionArticle;
}

string Sell::getImg(){
    return img;
}


string Sell::getCreatedAt(){
    return createdAt;
}

void Sell::printSell(){
    cout<<id<<nameArticle<<valueArticle<<DescriptionArticle<<img<<createdAt<<endl;
}