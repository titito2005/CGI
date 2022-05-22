#include "ShoppingCart.h"

ShoppingCart::ShoppingCart(){
    id = "";
    userId = "";
    sellId = "";
    sellCant = "";
    createdAt = "";
}

ShoppingCart::~ShoppingCart(){

}

void ShoppingCart::setId(string _id){
    id = _id;
}

void ShoppingCart::setUserId(string _userId){
    userId = _userId;
}

void ShoppingCart::setSellId(string _sellId){
    sellId = _sellId;
}

void ShoppingCart::setSellCant(string _sellCant){
    sellCant = _sellCant;
}

void ShoppingCart::setCreatedAt(string _createdAt){
    createdAt = _createdAt;
}

string ShoppingCart::getId(){
    return id;
}

string ShoppingCart::getUserId(){
    return userId;
}

string ShoppingCart::getSellId(){
    return sellId;
}

string ShoppingCart::getSellCant(){
    return sellCant;
}

string ShoppingCart::getCreatedAt(){
    return createdAt;
}