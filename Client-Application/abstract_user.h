#ifndef ABSTRACT_USER_H
#define ABSTRACT_USER_H
#include "Utility.h"

class Abstract_User
{
protected:
    string Email;
    string Username;
    vector <string> UsernameFriends;
    vector <string> GroupName;

public:
    Abstract_User();
    Abstract_User(string Email,string Username, vector <string> UserFriends,vector <string> GroupName);

};

#endif // ABSTRACT_USER_H
