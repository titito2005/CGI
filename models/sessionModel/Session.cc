#include "Session.h"

Session::Session(){
    id = "";
    ip = "";
    userId = "";
    loginCookie = "";
    createdAt = "";
    active = false;
}

Session::~Session(){
    
}

void Session::setId(string _id){
    id = _id;
}

void Session::setIp(string _ip){
    ip = _ip;
}

void Session::setUserId(string _userId){
    userId = _userId;
}

void Session::setLoginCookie(string _loginCookie){
    loginCookie = _loginCookie;
}

void Session::setCreatedAt(string _createdAt){
    createdAt = _createdAt;
}

void Session::setActive(bool _active){
    active = _active;
}

void Session::printSession(){
    cout<<id<<ip<<userId<<loginCookie<<createdAt<<active;
}

string Session::getId(){
    return id;
}

string Session::getIp(){
    return ip;
}

string Session::getUserId(){
    return  userId;
}

string Session::getLoginCookie(){
    return loginCookie;
}

string Session::getCreatedAt(){
    return createdAt;
}

bool Session::getActive(){
    return active;
}