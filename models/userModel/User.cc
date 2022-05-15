#include "User.h"

User::User(){
    id = "";
    firstName = "";
    lastName = "";
    email = "";
    password = "";
    createdAt = "";
    phoneNumber = "";
    direction = "";
}

User::User(string _id, string _firstName, string _lastName, string _email, string _password, string _createdAt, string _phoneNumber, string _direction){
    id = _id;
    firstName = _firstName;
    lastName = _lastName;
    email = _email;
    password = _password;
    createdAt = _createdAt;
    phoneNumber = _phoneNumber;
    direction = _direction;
}

User::~User(){
}

void User::setId(string _id){
    id = _id;
}

void User::setFirstName(string _firstName){
    firstName = _firstName;
}

void User::setLastName(string _lastName){
    lastName = _lastName;
}

void User::setEmail(string _email){
    email = _email;
}

void User::setPassword(string _password){
    password = _password;
}

void User::setCreatedAt(string _createdAt){
    createdAt = _createdAt;
}

void User::setPhoneNumber(string _phoneNumber){
    phoneNumber = _phoneNumber;
}

void User::setDirection(string _direction){
    direction = _direction;
}

string User::getId(){
    return id;
}

string User::getFirstName(){
    return firstName;
}

string User::getLastName(){
    return lastName;
}

string User::getEmail(){
    return email;
}

string User::getPassword(){
    return password;
}

string User::getCreatedAt(){
    return createdAt;
}

string User::getPhoneNumber(){
    return phoneNumber;
}

string User::getDirection(){
    return direction;
}

void User::printUser(){
    cout<<id<<firstName<<lastName<<email<<password<<createdAt<<phoneNumber<<direction<<endl;
}