#ifndef USERCOMMENT_H
#define USERCOMMENT_H

#include <iostream>
#include <string>

using namespace std;

class UserComment{
    public:
        UserComment();
        ~UserComment();
        void setId(string _id);
        void setComment(string _comment);
        void setCreatedAt(string _createdAt);
        string getId();
        string getComment();
        string getCreatedAt();
    private:
        string id;
        string comment;
        string createdAt;
};
#endif