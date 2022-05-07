#include "User.h"

User::User(){
    id = "";
    firstName = "";
    lastName = "";
    email = "";
    password = "";
    createdAt = "";
}

User::User(string _id, string _firstName, string _lastName, string _email, string _password, string _createdAt){
    id = _id;
    firstName = _firstName;
    lastName = _lastName;
    email = _email;
    password = _password;
    createdAt = _createdAt;
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

void User::printUser(){
    cout<<id<<firstName<<lastName<<email<<password<<createdAt<<endl;
}