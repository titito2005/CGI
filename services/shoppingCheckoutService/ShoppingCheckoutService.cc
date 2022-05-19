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

}

ShoppingCheckout* ShoppingCheckoutService::getCheckoutByUserId(char* userId){
    MYSQL_ROW row;
    ShoppingCheckout* checkout = NULL;
    char* query = "SELECT * FROM shoppingCheckout WHERE userId = ";
    char* finalQuery = (char *) malloc(3 + strlen(query)+ strlen(userId));
    strcpy(finalQuery, query);
    strcat(finalQuery, "'");
    strcat(finalQuery, userId);
    strcat(finalQuery, "'");
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)) {
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            checkout = new ShoppingCheckout();
            checkout->setId(row[0]);
            checkout->setUserId(row[1]);
            checkout->setCardName(row[2]);
            checkout->setCardNumber(row[3]);
            checkout->setCardExpireMonth(row[4]);
            checkout->setCardExpireYear(row[5]);
            checkout->setCardCVV(row[6]);
            checkout->setCreatedAt(row[7]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return checkout;
}

bool ShoppingCheckoutService::insertCardData(string cardName, string cardNumber, string cardExpireMonth, string cardExpireYear, string cardCVV){
    bool insertNewCardData = false;
    string query = "INSERT INTO shoppingCheckout(cardName,cardNumber,cardExpireMonth, cardExpireYear,cardCVV)VALUES(";
    query.append("'"+cardName+"','"+cardNumber+"','"+cardExpireMonth+"','"+cardExpireYear+"','"+cardCVV+"')");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery)){
        insertNewCardData = true;
    }

    return insertNewCardData;
}

string ShoppingCheckoutService::encryptionCardData(string stringToBeEncrypted){
    string encrypt = "";
    for (int i = 0; i < stringToBeEncrypted.length(); i++){
        stringToBeEncrypted[i] = stringToBeEncrypted[i]+2; //key for encryption is 3 and is added to ASCII
    }
    encrypt = stringToBeEncrypted;
    
    return encrypt;
}

string ShoppingCheckoutService::getCardByUserId(char* userId){
    string card = "";
    ShoppingCheckout* checkout = getCheckoutByUserId(userId);

    if(checkout!= NULL){
        card = checkout->getCardNumber();
    }
    return card;
}
