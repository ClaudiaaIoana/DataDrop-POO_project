#ifndef ABSTRACT_USER_H
#define ABSTRACT_USER_H
#include "Utility.h"
#include <QString>

class Abstract_User
{
protected:
    string          Email;
    string          Username;
    vector <string> UsernameFriends;
    vector <string> GroupName;

public:
    Abstract_User();
    Abstract_User(string Email,string Username,
                  vector <string> UserFriends,vector <string> GroupName);
    Abstract_User(string username);

    //get-ere
    string _getUsername()const;
    int _getSizeFriendBuffer()const;
    int _getSizeGroups()const;
    string _getUsernameIndex(int i) const;
    string _getGroupIndex(int i) const;

    //push-uri in vector
    void _addFriend(QString username);
    void _addGroup(QString GroupName);

    bool isGroup(QString nameGroup);

    void _clearFriendsList();

};

#endif // ABSTRACT_USER_H
