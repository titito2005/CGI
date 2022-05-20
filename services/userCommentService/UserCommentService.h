#ifndef USERCOMMENTSERVICE_H
#define USERCOMMENTSERVICE_H
#include <mysql/mysql.h>  // require libmysqlclient-dev
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "../../models/userCommentModel/UserComment.h"
#include "../Database.h"
#include <vector>

using namespace std;

class UserCommentService {
    public:
        UserCommentService();
        ~UserCommentService();
        vector<UserComment> getAllUserComments();
        bool addComment(string comment);
  
    private:
        Database* db;
        MYSQL* conn;
        MYSQL_RES *res;
};
#endif