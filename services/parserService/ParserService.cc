#include "ParserService.h"

ParserService::ParserService(){
    queryArgCnt = 0;
    for (int i = 0; i < MAX_ARGS; i++){
        queryName[i] = queryValue[i] = NULL;
    }

    cookieArgCnt = 0;
    for (int i = 0; i < MAX_ARGS; i++){
        cookieName[i] = cookieValue[i] = NULL;
    }

    db = new Database();
    if(db->connectToDatabase()){
        conn = db->getConnection();
    } else {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }
}

ParserService::~ParserService(){

}

//QUERY PARSER
void ParserService::parseQuery(char* query_string, int query_length){
    // Separate query_string into arguments
    int start_name, end_name, start_value, end_value = -1;
    while (end_value < query_length){
        // Find argument name
        start_name = end_name = end_value + 1;
        while ((end_name<query_length) && (query_string[end_name] != '=')){
            end_name++;
        }

        // Copy and decode name string
        queryName[queryArgCnt] = copy_string(query_string, start_name, end_name);
        decode_string(queryName[queryArgCnt]);

        // Find argument value
        start_value = end_value = end_name + 1;
        while ((end_value<query_length) && (query_string[end_value] != '&')){
            end_value++;
        }
        // Copy and decode value string
        queryValue[queryArgCnt] = copy_string(query_string, start_value, end_value);
        decode_string(queryValue[queryArgCnt]);
        queryArgCnt++;
    }
}

char* ParserService::getQueryArg(const char name[]){
    // Lookup argument by name
    for (int arg=0; arg<queryArgCnt; arg++){
        //Verify if exists argument name
        if (strcmp(name, queryName[arg]) == 0){
            //Verify if value exists and is different to NULL.
            if(strlen(queryValue[arg]) > 0){
                return queryValue[arg];
            }
        }
    }
    // Return NULL if not found
    return NULL;
}

char* ParserService::getQueryName(int index){
    // Lookup argument by location
    if ((index >= 0) && (index < queryArgCnt)){
        return queryName[index];
    }else{
        return NULL;
    }
}

char* ParserService::getQueryValue(int index){
    // Lookup argument by location
    if ((index >= 0) && (index < queryArgCnt)){
        return queryValue[index];
    }else{
        return NULL;
    }
}

int ParserService::getQueryCant(){
    return queryArgCnt;
}

//COOKIE PARSER
void ParserService::parseCookie(char* cookie_string, int cookie_length){
    // Separate cookie_string into arguments
    int start_name, end_name, start_value, end_value = -1;
    while (end_value < cookie_length){
        // Find argument name
        start_name = end_name = end_value + 1;
        while ((end_name<cookie_length) && (cookie_string[end_name] != '=')){
            end_name++;
        }
        // Copy and decode name string
        cookieName[cookieArgCnt] = copy_string(cookie_string, start_name, end_name);
        // Find argument value
        start_value = end_value = end_name + 1;
        while ((end_value<cookie_length) && (cookie_string[end_value] != ';')){
            end_value++;
        }
        // Copy and decode value string
        cookieValue[cookieArgCnt] = copy_string(cookie_string, start_value, end_value);
        cookieArgCnt++;
        //White space
        end_value++;
    }
}

char* ParserService::getCookieArg(const char name[]){
    // Lookup argument by name
    for (int arg=0; arg<cookieArgCnt; arg++){
        //Verify if exists argument name
        if (strcmp(name, cookieName[arg]) == 0){
            //Verify if value exists and is different to NULL.
            if(strlen(cookieValue[arg]) > 0){
                return cookieValue[arg];
            }
        }
    }
    // Return NULL if not found
    return NULL;
}

char* ParserService::getCookieName(int index){
    // Lookup argument by location
    if ((index >= 0) && (index < cookieArgCnt)){
        return cookieName[index];
    }else{
        return NULL;
    }
}

char* ParserService::getCookieValue(int index){
    // Lookup argument by location
    if ((index >= 0) && (index < cookieArgCnt)){
        return cookieValue[index];
    }else{
        return NULL;
    }
}

int ParserService::getCookieCant(){
    return cookieArgCnt;
}

//OTHER METHODS
char* ParserService::copy_string(char *str, int start, int end){
    // Create string
    char *copy = (char *)malloc(end-start+1);
    if (copy == NULL) {
        return NULL;
    }
    // Copy substring
    int pos;
    for (pos = start; pos < end; pos++){
        copy[pos-start] = str[pos];
    }
    copy[pos-start] = '\0';
    return copy;
}

void ParserService::decode_string(char *str){
    const char *digits = "0123456789ABCDEF";
    int length = strlen(str);
    int outpos = 0;

    for (int pos=0; pos<length; pos++){
        // Handle white space
        if (str[pos] == '+'){
            str[outpos++] = ' ';
        }else{
            if (str[pos] == '%'){
                char ch1 = toupper(str[++pos]);
                char ch2 = toupper(str[++pos]);
                str[outpos++] = 16*(strchr(digits, ch1)-strchr(digits,'0'))
                + strchr(digits, ch2)-strchr(digits,'0');
            }else{
                str[outpos++] = str[pos];
            }
        }
    }
    // Mark end of string
    str[outpos] = '\0';
}

bool ParserService::verifyRequest(char* request){
    bool badWordFound = false;
    if(request != NULL){
        string stringRequest(request);
        string badWords[6] = {"delete", "insert", "update", "select", "from", "where"};

        for_each(stringRequest.begin(), stringRequest.end(), [](char & c) {
            c = ::tolower(c);
        });

        for (int i = 0; i<6 && !badWordFound; i++)  {
            if (stringRequest.find(badWords[i]) != string::npos) {
                badWordFound = true;
            }
        }
    }
    return badWordFound;
}

//If isLogin is true, user is trying to Login.
//If isLogin is false, user is login out.
void ParserService::auditLoginAndLogout(bool isLogin, string user, string ip, bool success){
  string action = "";
  string response = "";
  if(isLogin){
    action = "Login";
  } else {
    action = "Logout";
  }

  if(success){
    response = "Success";
  } else {
    response = "Fail";
  }

  string query = "INSERT INTO auditLogin(action,userEmail,userIp,success) VALUES (";
  query.append("'"+action+"','"+user+"','"+ip+"','"+response+"')");
  const char *finalQuery = query.c_str();
  if (mysql_query(conn, finalQuery)){
    printf("%s \n", "Error audit");
    exit(1);
  }
}

//If isPurchase is true, user is trying to buying.
//If isPurchase is false, user tryng to set new item to sell it.
void ParserService::auditBuyProducts(bool isPurchase, string user, string ip, bool success){
  string action = "";
  string response = "";
  if(isPurchase){
    action = "Buy";
  } else {
    action = "AddItem";
  }

  if(success){
    response = "Success";
  } else {
    response = "Fail";
  }

  string query = "INSERT INTO auditSell(action,userEmail,userIp,success) VALUES (";
  query.append("'"+action+"','"+user+"','"+ip+"','"+response+"')");
  const char *finalQuery = query.c_str();
  if (mysql_query(conn, finalQuery)){
    printf("%s \n", "Error audit");
    exit(1);
  }
}
