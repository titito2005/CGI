#include "UserComment.h"  

UserComment::UserComment(){
    id = "";
    comment = "";
    createdAt = "";
}

UserComment::~UserComment(){

}

void UserComment::setId(string _id){
    id = _id;
}

void UserComment::setComment(string _comment){
    comment = _comment;
}

void UserComment::setCreatedAt(string _createdAt){
    createdAt = _createdAt;
}

string UserComment::getId(){
    return id;
}

string UserComment::getComment(){
    return comment;
}

string UserComment::getCreatedAt(){
    return createdAt;
}