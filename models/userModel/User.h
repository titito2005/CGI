#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User{
    public:
        User();
        User(string _id, string _firstName, string _lastName, string _email, string _password, string _createdAt);
        ~User();
        void setId(string _id);
        void setFirstName(string _firstName);
        void setLastName(string _lastName);
        void setEmail(string _email);
        void setPassword(string _password);
        void setCreatedAt(string _createdAt);
        void printUser();
        string getId();
        string getFirstName();
        string getLastName();
        string getEmail();
        string getPassword();
        string getCreatedAt();

    private:
        string id;
        string firstName;
        string lastName;
        string email;
        string password;
        string createdAt;
};
#endif