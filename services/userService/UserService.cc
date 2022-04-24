#include "UserService.h"

UserService::UserService(){
    db = new Database();
    if(db->connectToDatabase()){
        conn = db->getConnection();
    } else {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }
}

UserService::~UserService(){
    //delete db;
    //delete conn;
    //red
}

User UserService::getUserById(char* id){
    MYSQL_ROW row;
    User findUser;

    char* query = "SELECT * FROM user WHERE id = ";
    char* finalQuery = (char *) malloc(1 + strlen(query)+ strlen(id));

    strcpy(finalQuery, query);
    strcat(finalQuery, id);

    //Return 0 for success
    if (!mysql_query(conn, finalQuery)) {
        res = mysql_use_result(conn);
        // Fetch a result set
        while ((row = mysql_fetch_row(res)) != NULL){
            findUser.setId(row[0]);
            findUser.setFirstName(row[1]);
            findUser.setLastName(row[2]);
            findUser.setEmail(row[3]);
            findUser.setPassword(row[4]);
            findUser.setCreatedAt(row[5]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findUser;
}