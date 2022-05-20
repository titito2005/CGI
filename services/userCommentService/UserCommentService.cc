#include "UserCommentService.h"

UserCommentService::UserCommentService(){
    db = new Database();
    if (db->connectToDatabase())
    {
        conn = db->getConnection();
    }
    else
    {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }

}

UserCommentService::~UserCommentService(){

}

vector<UserComment> UserCommentService::getAllUserComments(){
    vector<UserComment> userComments;
    MYSQL_ROW row;
    string query = "SELECT * FROM userComment";
    const char *finalQuery = query.c_str();
    // Return 0 for success
    if (!mysql_query(conn, finalQuery))
    {
        res = mysql_use_result(conn);
        // Fetch a result set
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            UserComment comment;
            comment.setId(row[0]);
            comment.setComment(row[1]);
            comment.setCreatedAt(row[4]);
            userComments.push_back(comment);
        }
        // Release memories
        mysql_free_result(res);
    }
    return userComments;
}

bool UserCommentService::addComment(string comment){
    bool addComment = false;
    string query = "INSERT INTO userComment (comment) VALUES(";
    query.append("'" + comment + "')");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery))
    {
        addComment = true;
    }

    return addComment;
}