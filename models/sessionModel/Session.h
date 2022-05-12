#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <string>

using namespace std;

class Session{
    public:
        Session();
        ~Session();
        void setId(string _id);
        void setIp(string _ip);
        void setUserId(string _userId);
        void setLoginCookie(string _loginCookie);
        void setCreatedAt(string _createdAt);
        void setActive(bool _active);
        void printSession();
        string getId();
        string getIp();
        string getUserId();
        string getLoginCookie();
        string getCreatedAt();
        bool getActive();

    private:
        string id;
        string ip;
        string userId;
        string loginCookie;
        string createdAt;
        bool active;
};
#endif