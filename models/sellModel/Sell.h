#ifndef SELL_H
#define SELL_H

#include <iostream>
#include <string>

using namespace std;

class Sell{
    public:
        Sell();
        Sell(string _id, string _firstName, string _lastName, string _description, string _createdAt);
        ~Sell();
        void setId(string _id);
        void setnameArticle(string _firstName);
        void setvalueArticle(string _lastName);
        void setDescriptionArticle(string _Description);
        void setCreatedAt(string _createdAt);
        void printSell();
        string getId();
        string getnameArticle();
        string getvalueArticle();
        string getDescriptionArticle();
        string getCreatedAt();
        string id;
        string nameArticle;
        string valueArticle;
        string descriptionArticle;
        string createdAt;
};
#endif