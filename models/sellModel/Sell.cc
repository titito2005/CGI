#include "Sell.h"

Sell::Sell(){
    id = "";
    nameArticle = "";
    valueArticle = "";
    descriptionArticle = "";
    createdAt = "";
}

Sell::Sell(string _id, string _nameArticle, string _valueArticle, string _descriptionArticle, string _createdAt){
    id = _id;
    nameArticle = _nameArticle;
    valueArticle = _valueArticle;
    descriptionArticle = _descriptionArticle;
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

void Sell::setDescriptionArticle(string _descriptionArticle){
    descriptionArticle = _descriptionArticle;
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
    return descriptionArticle;
}

string Sell::getCreatedAt(){
    return createdAt;
}

void Sell::printSell(){
    cout<<id<<nameArticle<<valueArticle<<descriptionArticle<<createdAt<<endl;
}