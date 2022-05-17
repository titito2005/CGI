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
    Sell* findUser = NULL;
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
            findUser = new Sell();
            findUser->setId(row[0]);
            findUser->setnameArticle(row[1]);
            findUser->setvalueArticle(row[2]);
            findUser->setDescriptionArticle(row[3]);
            findUser->setImg(row[4]);
            findUser->setCreatedAt(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findUser;
}

Sell* SellService::getById(int id){
    MYSQL_ROW row;
    Sell* findUser = NULL;
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
            findUser = new Sell();
            findUser->setId(row[0]);
            findUser->setnameArticle(row[1]);
            findUser->setvalueArticle(row[2]);
            findUser->setDescriptionArticle(row[3]);
            findUser->setImg(row[4]);
            findUser->setCreatedAt(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    return findUser;
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

