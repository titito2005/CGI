#include "ShoppingCheckout.h"

ShoppingCheckout::ShoppingCheckout(){
    id = "";
    userId = "";
    cardName = "";
    cardNumber = "";
    cardExpireMonth = "";
    cardExpireYear = "";
    cardCVV = "";
    createdAt = "";
}

ShoppingCheckout::~ShoppingCheckout(){

}

void ShoppingCheckout::setId(string _id){
    id = _id;
}

void ShoppingCheckout::setUserId(string _userId){
    userId = _userId;
}

void ShoppingCheckout::setCardName(string _cardName){
    cardName= _cardName;
}

void ShoppingCheckout::setCardNumber(string _cardNumber){
    cardNumber = _cardNumber;
}

void ShoppingCheckout::setCardExpireMonth(string _cardExpireMonth){
    cardExpireMonth = _cardExpireMonth;
}

void ShoppingCheckout::setCardExpireYear(string _cardExpireYear){
    cardExpireYear = _cardExpireYear;
}

void ShoppingCheckout::setCardCVV(string _cardCVV){
    cardCVV = _cardCVV;
}

void ShoppingCheckout::setCreatedAt(string _createdAt){
    createdAt = _createdAt;
}

string ShoppingCheckout::getId(){
    return id;
}

string ShoppingCheckout::getUserId(){
    return userId;
}

string ShoppingCheckout::getCardName(){
    return cardName;
}

string ShoppingCheckout::getCardNumber(){
    return cardNumber;
}

string ShoppingCheckout::getCardExpireMonth(){
    return cardExpireMonth;
}

string ShoppingCheckout::getCardExpireYear(){
    return cardExpireYear;
}

string ShoppingCheckout::getCardCVV(){
    return cardCVV;
}

string ShoppingCheckout::getCreatedAt(){
    return createdAt;
}