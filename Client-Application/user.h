#ifndef USER_H
#define USER_H
#include "Utility.h"
#include "abstract_user.h"
class User: public Abstract_User
{
private:


public:
    User();
    User(string Email,string Username,vector <string> UsernameFriends,vector <string> GroupName);
    User(string Username);
};

#endif // USER_H
