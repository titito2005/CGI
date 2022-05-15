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
    char* finalQuery = (char *) malloc(1 + strlen(query)+ strlen(id));
    strcpy(finalQuery, query);
    strcat(finalQuery, id);
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
            findUser->setCreatedAt(row[4]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
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

