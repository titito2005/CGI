#ifndef SHOPPINGCHECKOUT_H
#define SHOPPINGCHECKOUT_H

#include <iostream>
#include <string>

using namespace std;

class ShoppingCheckout{
    public:
        ShoppingCheckout();
        ~ShoppingCheckout();
        void setId(string _id);
        void setUserId(string _userId);
        void setCardName(string _cardName);
        void setCardNumber(string _cardNumber);
        void setCardExpireMonth(string _cardExpireMonth);
        void setCardExpireYear(string _cardExpireYear);
        void setCardCVV(string _cardCVV);
        void setCreatedAt(string _createdAt);
        string getId();
        string getUserId();
        string getCardName();
        string getCardNumber();
        string getCardExpireMonth();
        string getCardExpireYear();
        string getCardCVV();
        string getCreatedAt();
    private:
        string id;
        string userId;
        string cardName;
        string cardNumber;
        string cardExpireMonth;
        string cardExpireYear;
        string cardCVV;
        string createdAt;
};
#endif