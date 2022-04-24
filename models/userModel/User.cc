#include "User.h"

User::User(){
}

User::User(char* _id, char* _firstName, char* _lastName, char* _email, char* _password, char* _createdAt){
    id = (char *) malloc(1 + strlen(_id));
    strcpy(id, _id);

    firstName = (char *) malloc(1 + strlen(_firstName));
    strcpy(firstName, _firstName);

    lastName = (char *) malloc(1 + strlen(_lastName));
    strcpy(lastName, _lastName);

    email = (char *) malloc(1 + strlen(_email));
    strcpy(email, _email);

    password = (char *) malloc(1 + strlen(_password));
    strcpy(password, _password);

    createdAt = (char *) malloc(1 + strlen(_createdAt));
    strcpy(createdAt, _createdAt);
}

User::~User(){
}

void User::setId(char* _id){
    id = (char *) malloc(1 + strlen(_id));
    strcpy(id, _id);
}

void User::setFirstName(char* _firstName){
    firstName = (char *) malloc(1 + strlen(_firstName));
    strcpy(firstName, _firstName);
}

void User::setLastName(char* _lastName){
    lastName = (char *) malloc(1 + strlen(_lastName));
    strcpy(lastName, _lastName);
}

void User::setEmail(char* _email){
    email = (char *) malloc(1 + strlen(_email));
    strcpy(email, _email);
}

void User::setPassword(char* _password){
    password = (char *) malloc(1 + strlen(_password));
    strcpy(password, _password);
}

void User::setCreatedAt(char* _createdAt){
    createdAt = (char *) malloc(1 + strlen(_createdAt));
    strcpy(createdAt, _createdAt);
}

char* User::getId(){
    return id;
}

char* User::getFirstName(){
    return firstName;
}

char* User::getLastName(){
    return lastName;
}

char* User::getEmail(){
    return email;
}

char* User::getPassword(){
    return password;
}

char* User::getCreatedAt(){
    return createdAt;
}

void User::printUser(){
    printf("%s \n", id);
    printf("%s \n", firstName);
    printf("%s \n", lastName);
    printf("%s \n", email);
    printf("%s \n", password);
    printf("%s \n", createdAt);
}