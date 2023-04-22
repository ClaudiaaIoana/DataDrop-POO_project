#include "user.h"

User::User()
{

}

User::User(string Username):
    Abstract_User(Username)
{
}

User::User(string Email,string Username,vector <string> UsernameFriends,vector <string> GroupName):
    Abstract_User(Email,Username,UsernameFriends,GroupName)
{

}
