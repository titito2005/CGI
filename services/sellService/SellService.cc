#include "SellService.h"

SellService::SellService(){
    db = new Database();
    if(db->connectToDatabase()){
        conn = db->getConnection();
    } else {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }
}

SellService::~SellService(){
    //delete db;
    //delete conn;
    //red
}

Sell* SellService::getSellById(char* id){
    MYSQL_ROW row;
    Sell* findSell = NULL;
    char* query = "SELECT * FROM sell WHERE id = ";
    char* finalQuery = (char *) malloc(3 + strlen(query)+ strlen(id));
    strcpy(finalQuery, query);
    strcat(finalQuery, "'");
    strcat(finalQuery, id);
    strcat(finalQuery, "'");
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)){
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            findSell = new Sell();
            findSell->setId(row[0]);
            findSell->setnameArticle(row[1]);
            findSell->setvalueArticle(row[2]);
            findSell->setDescriptionArticle(row[3]);
            findSell->setImg(row[4]);
            findSell->setCreatedAt(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findSell;
}

Sell* SellService::getById(int id){
    MYSQL_ROW row;
    Sell* findSell = NULL;
    string query = "SELECT * FROM sell WHERE id = ";
    string sellId=to_string(id);
    query.append("'");
    query.append(sellId);
    query.append("'");
    const char *finalQuery = query.c_str();
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)){
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            findSell = new Sell();
            findSell->setId(row[0]);
            findSell->setnameArticle(row[1]);
            findSell->setvalueArticle(row[2]);
            findSell->setDescriptionArticle(row[3]);
            findSell->setImg(row[4]);
            findSell->setCreatedAt(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    return findSell;
}

int SellService::getSellCountAll(){
    MYSQL_ROW row;
    Sell* findUser = NULL;
    char* query = "SELECT * FROM sell";
    int num_fields=0;
    //Return 0 for success
    if (!mysql_query(conn, query)){
        res = mysql_store_result (conn);
        field = mysql_fetch_fields(res);
        num_fields = mysql_num_rows(res);
 
    }
    // Release memories
    mysql_free_result(res);
    return num_fields;
}
Sell*  SellService::sellByName(string searchName){
    MYSQL_ROW row;
    Sell* findSell = NULL;
    string query = "SELECT * FROM sell WHERE nameArticle LIKE \"%";
    query.append(searchName);
    query.append("%\"");
    const char *finalQuery = query.c_str();
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)){
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            findSell = new Sell();
            findSell->setId(row[0]);
            findSell->setnameArticle(row[1]);
            findSell->setvalueArticle(row[2]);
            findSell->setDescriptionArticle(row[3]);
            findSell->setImg(row[4]);
            findSell->setCreatedAt(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    return findSell;
}

bool SellService::addSell(string GameName, string GameValue, string GameDescription){
    bool addSell = false;
    ///var/www/html/public/img
    string img="http://localhost/public/img/indice.jpeg";
    string query = "INSERT INTO sell(nameArticle, valueArticle, descriptionArticle, img)VALUES(";
    query.append("'"+GameName+"','"+GameValue+"','"+GameDescription+"','"+img+"')");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery)){
        addSell = true;
    }

    return addSell;
}
