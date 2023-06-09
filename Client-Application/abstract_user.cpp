#include "abstract_user.h"
#include <QString>


Abstract_User::Abstract_User()
{

}
Abstract_User::Abstract_User(string Email,string Username, vector <string> UserFriends,vector <string> GroupName):Email(Email),
    Username(Username),UsernameFriends(UserFriends),GroupName(GroupName)
{

}

Abstract_User::Abstract_User(string username):
    Username(username)
{
}

string Abstract_User::_getUsername()const
{
    return this->Username;
}

int Abstract_User::_getSizeFriendBuffer()const
{
    return this->UsernameFriends.size();
}

int Abstract_User::_getSizeGroups()const
{
   return this->GroupName.size();
}

string Abstract_User::_getUsernameIndex(int i) const
{
    return this->UsernameFriends[i];
}

string Abstract_User::_getGroupIndex(int i) const
{
    return this->GroupName[i];
}

void Abstract_User::_addFriend(QString username)
{
    string name= username.toStdString();
    this->UsernameFriends.push_back(name);
}
 void Abstract_User::_addGroup(QString GroupName)
 {
      string name= GroupName.toStdString();
      this->GroupName.push_back(name);
 }

 void Abstract_User::_clearFriendsList()
 {
     this->UsernameFriends.clear();
 }

 bool Abstract_User::isGroup(QString nameGroup)
 {
     for ( auto it = GroupName.begin();it!= GroupName.end();it++)
     {
         if(QString::fromStdString((*it))==nameGroup)
             return true;
     }
     return false ;
 }

