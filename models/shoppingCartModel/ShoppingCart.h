#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <iostream>
#include <string>

using namespace std;

class ShoppingCart{
    public:
        ShoppingCart();
        ~ShoppingCart();
        void setId(string _id);
        void setUserId(string _userId);
        void setSellId(string _sellId);
        void setSellCant(string _sellCant);
        void setCreatedAt(string _createdAt);
        string getId();
        string getUserId();
        string getSellId();
        string getSellCant();
        string getCreatedAt();
    private:
        string id;
        string userId;
        string sellId;
        string sellCant;
        string createdAt;
};
#endif