#include "ShoppingCheckoutService.h"

ShoppingCheckoutService::ShoppingCheckoutService(){
    db = new Database();
    if(db->connectToDatabase()){
        conn = db->getConnection();
    } else {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }
}

ShoppingCheckoutService::~ShoppingCheckoutService(){
    //delete db;
    //delete conn;
    //red
}

bool ShoppingCheckoutService::insertCardData(string cardNumber, string cardType, string cardName, string cardExpireDate, string cardPin){
    bool insertNewCardData = false;
    string query = "INSERT INTO shoppingCheckout(cardNumber,cardType,cardName,cardExpireDate,cardPin)VALUES(";
    query.append("'"+cardNumber+"','"+cardType+"','"+cardName+"','"+cardExpireDate+"','"+cardPin+"')");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery)){
        insertNewCardData = true;
    }

    return insertNewCardData;
}

string ShoppingCheckoutService::encryptionCardData(string pin){
    string encrypt = "";
    for (int i = 0; i < pin.length(); i++){
        pin[i] = pin[i]+2; //key for encryption is 3 and is added to ASCII
    }
    encrypt = pin;
    
    return encrypt;
}