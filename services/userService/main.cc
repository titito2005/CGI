#include "UserService.h"
#include "../../models/userModel/User.h"

int main(){
    UserService* u = new UserService();
    User user1; 
    User user2;
    User user3;
    
    user1 = u->getUserById("1");
    user2 = u->getUserById("2");
    user3 = u->getUserById("3");

    user1.printUser();
    user2.printUser();
    user3.printUser();
    delete u;
    return 0;
}