#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include <cstring>
#include <stdio.h>
#include <memory.h>
#include <cstdlib>

class User{
    public:
        User();
        User(char* _id, char* _firstName, char* _lastName, char* _email, char* _password, char* _createdAt);
        ~User();
        void setId(char* _id);
        void setFirstName(char* _firstName);
        void setLastName(char* _lastName);
        void setEmail(char* _email);
        void setPassword(char* _password);
        void setCreatedAt(char* _createdAt);
        char* getId();
        char* getFirstName();
        char* getLastName();
        char* getEmail();
        char* getPassword();
        char* getCreatedAt();
        void printUser();
        char* id;
        char* firstName;
        char* lastName;
        char* email;
        char* password;
        char* createdAt;
};
#endif