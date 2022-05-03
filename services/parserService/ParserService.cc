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
        if (strcmp(name, queryName[arg]) == 0){
            return queryValue[arg];
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