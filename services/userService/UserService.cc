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

User* UserService::getUserById(char* id){
    MYSQL_ROW row;
    User* findUser = NULL;
    char* query = "SELECT * FROM user WHERE id = ";
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
            findUser = new User();
            findUser->setId(row[0]);
            findUser->setFirstName(row[1]);
            findUser->setLastName(row[2]);
            findUser->setEmail(row[3]);
            findUser->setPassword(row[4]);
            findUser->setCreatedAt(row[5]);
            findUser->setPhoneNumber(row[6]);
            findUser->setDirection(row[7]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findUser;
}

User* UserService::getUserByEmail(char* email){
    MYSQL_ROW row;
    User* findUser = NULL;
    char* query = "SELECT * FROM user WHERE email = ";
    char* finalQuery = (char *) malloc(3 + strlen(query)+ strlen(email));
    strcpy(finalQuery, query);
    strcat(finalQuery, "'");
    strcat(finalQuery, email);
    strcat(finalQuery, "'");
    //Return 0 for success
    if (!mysql_query(conn, finalQuery)) {
        res = mysql_use_result(conn);
        // Fetch a result set
        if ((row = mysql_fetch_row(res)) != NULL){
            findUser = new User();
            findUser->setId(row[0]);
            findUser->setFirstName(row[1]);
            findUser->setLastName(row[2]);
            findUser->setEmail(row[3]);
            findUser->setPassword(row[4]);
            findUser->setCreatedAt(row[5]);
            findUser->setPhoneNumber(row[6]);
            findUser->setDirection(row[7]);
        }
        // Release memories
        mysql_free_result(res);
    }
    free(finalQuery);
    return findUser;
}

string UserService::getIdByEmail(char* email){
    string userId = "";
    User* findUser = getUserByEmail(email);
    if(findUser!=NULL){
        userId = findUser->getId();
    }
    return userId;
}

bool UserService::verifyPassword(char* email, char* password){
    bool acceptPassword = false;
    User* findUser = getUserByEmail(email);
    if(findUser!=NULL){
        if ((findUser->getPassword().compare(encryption(password))) == 0){
            acceptPassword = true;
        }
    }
    return acceptPassword;
}

bool UserService::insertUserRegister(string name, string lastNames, string email, string password, string phoneNumber, string direction){
    bool insertNewUser = false;
    string query = "INSERT INTO user(firstName,lastName,email,userPassword,phoneNumber,direction)VALUES(";
    query.append("'"+name+"','"+lastNames+"','"+email+"','"+password+"','"+phoneNumber+"','"+direction+"')");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery)){
        insertNewUser = true;
    }

    return insertNewUser;
}

bool UserService::verifyEmailExistence(char* incomingEmail){
    bool emailExist = false;
    User* findUser = getUserByEmail(incomingEmail);
    if (findUser != NULL){
        emailExist = true; // encuentra el email de usuario
    }
    
    return emailExist;
}

string UserService::encryption(string password){
    string encrypt = "";
    for (int i = 0; i < password.length(); i++){
        password[i] = password[i]+2; //key for encryption is 3 and is added to ASCII
    }
    encrypt = password;
    
    return encrypt;
}