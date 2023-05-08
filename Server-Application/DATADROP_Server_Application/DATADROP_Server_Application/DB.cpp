#include "DB.h"
#include"Exception_connecting_db.h"
#include"Exception_alloc.h"
#include"Exception_query.h"
#include<stdlib.h>

#define MAX_BINARY_SIZE         (2^31-1)  

DB* DB::instance = nullptr;

DB::DB()
{
    SQLRETURN           retcode;
    SQLWCHAR            retconstring[SQL_RETURN_CODE_LEN];

    // Allocate an environment handle
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    // Set the ODBC version
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // Allocate a connection handle
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

    // Connect to the SQL Server database
    SQLWCHAR* dsn = (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DESKTOP-0AQ7BL5;DATABASE=DataDrop;Trusted=true;";
    switch (SQLDriverConnect(hdbc,
        NULL,
        dsn,
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT)) {
    case SQL_SUCCESS:
        std::cout << "Successfully connected to SQL Server";
        std::cout << "\n";
        break;
    case SQL_SUCCESS_WITH_INFO:
        std::cout << "Successfully connected to SQL Server";
        std::cout << "\n";
        break;
    case SQL_INVALID_HANDLE:
        std::cout << "Could not connect to SQL Server";
        std::cout << "\n";
        throw(new Exception_connecting_db("Eroare connecting at the database", 1));
    case SQL_ERROR:
        std::cout << "Could not connect to SQL Server";
        std::cout << "\n";
        throw(new Exception_connecting_db("Eroare connecting at the database", 3));
    default:
        break;
    }

    // Allocate a statement handle
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
}

DB::~DB()
{
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

DB* DB::get_instance()
{
    if (!instance)
        instance = new DB();
    return instance;
}

void DB::destroy_instance()
{
    if (instance)
        delete instance;
}

void DB::resetHanddle()
{
    SQLRETURN retcode;

    // Free the existing statement handle
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    hstmt = SQL_NULL_HSTMT;

    // Allocate a new statement handle
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (!SQL_SUCCEEDED(retcode)) 
    {
        throw(new Exception_alloc("can't realloc handle", 1));
       
    }
}

bool DB::verify_account(std::string username, std::string password)
{
    bool            valid = false;
    SQLRETURN       retcode;
    try {

    resetHanddle();

    // Prepare SQL statement
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"SELECT * FROM Users WHERE UserName = ? AND Password = ?", SQL_NTS);

    // Bind parameters to the statement
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);

    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, (SQLPOINTER)password.c_str(), password.length(), NULL);

    // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (SQLFetch(hstmt) == SQL_SUCCESS) {
                valid = true;
            }
        }
        else 
        {
            throw(new Exception_query("invalid account", 3));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

    return valid;
}

void DB::add_account(std::string username, std::string email, std::string password)
{
    SQLRETURN retcode;
    try {
        resetHanddle();

        // Prepare SQL statement
        retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO Users VALUES ( ? , ? , ? )", SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, (SQLPOINTER)password.c_str(), password.length(), NULL);
        retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, email.length(), 0, (SQLPOINTER)email.c_str(), email.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            if (SQLFetch(hstmt) == SQL_SUCCESS) {
                std::cout << "ACCOUNT CREATED WITH SUCCES" << std::endl;
            }
        }
        else 
        {
            throw(new Exception_query("failed creating account", 4));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

bool DB::add_friend(std::string user1, std::string user2)
{
    SQLRETURN retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"INSERT INTO Friendships VALUES ((SELECT UserID FROM Users WHERE UserName = ? ),(SELECT UserID FROM Users WHERE UserName = ? ))";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, user1.length(), 0, (SQLPOINTER)user1.c_str(), user1.length(), NULL);

        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, user2.length(), 0, (SQLPOINTER)user2.c_str(), user2.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "FRIENDSHIP CREATED" << std::endl;
            return true;
        }
        else 
        {
            throw(new Exception_query("couldn't create friendship, possible wrong username", 5));
        }
    }
    catch (_IException *e)
    {
        e->handle_exception();
        delete e;
        return false;
    }
    return false;
}

std::vector<std::string> DB::get_friend_list(std::string username)
{
    std::vector<std::string>        usernames;
    SQLRETURN                       retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"EXEC FriendsList ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {

            SQLCHAR sqlUsername[SQL_RESULT_LEN];
            SQLLEN ptrSqlUsername;

            while (SQLFetch(hstmt) == SQL_SUCCESS)
            {
                SQLGetData(hstmt, 1, SQL_CHAR, sqlUsername, SQL_RESULT_LEN, &ptrSqlUsername);
                usernames.push_back((char*)sqlUsername);
            }

            std::cout << "FRIEND LIST EXTRACTED" << std::endl;
        }
        else 
        {
            throw(new Exception_query("coundn't exctract friend list", 6));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
    return usernames;
}

std::vector<std::string> DB::get_group_list(std::string username)
{
    std::vector<std::string>        groups;
    SQLRETURN                       retcode;
    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"SELECT g.Name FROM Groups AS G INNER JOIN GroupMembers AS GM ON G.GroupID = GM.GroupID INNER JOIN Users AS U ON GM.UserID = U.UserID WHERE U.UserName = ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {

            SQLCHAR sqlUsername[SQL_RESULT_LEN];
            SQLLEN ptrSqlUsername;

            while (SQLFetch(hstmt) == SQL_SUCCESS)
            {
                SQLGetData(hstmt, 1, SQL_CHAR, sqlUsername, SQL_RESULT_LEN, &ptrSqlUsername);
                groups.push_back((char*)sqlUsername);
            }

            std::cout << "GROUP LIST EXTRACTED" << std::endl;
        }
        else 
        {
            throw(new Exception_query("coundn't exctract group list", 7));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

    return groups;
}

void DB::push_waiting_message(std::string sender, std::string receiver, std::string message)
{
    SQLRETURN retcode;
    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"exec insert_message_user_user @Sender = ? , @Receiver = ? , @Message = ?";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sender.length(), 0, (SQLPOINTER)sender.c_str(), sender.length(), NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);
        retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, message.length(), 0, (SQLPOINTER)message.c_str(), message.length(), NULL);
        // Execute the statement
          // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "MESSAGE STORED" << std::endl;
        }
        else {
            throw(new Exception_query("couldn't store the message", 8));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

}

std::vector<std::pair<std::string, std::string>>  DB::pop_waiting_messages(std::string user)
{
    std::vector<std::pair<std::string,std::string>>        sender_message;
    SQLRETURN                                              retcode;
    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"select U2.UserName, Message from WaitingMessages AS WM INNER JOIN Users AS U1 ON WM.ReceiverID = U1.UserID INNER JOIN Users AS U2 ON WM.SenderID = U2.UserID WHERE U1.UserName = ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, user.length(), 0, (SQLPOINTER)user.c_str(), user.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {

            SQLCHAR sqlSender[SQL_RESULT_LEN];
            SQLLEN ptrSqlSender;
            SQLCHAR sqlMessage[SQL_RESULT_LEN];
            SQLLEN ptrSqlMessage;

            while (SQLFetch(hstmt) == SQL_SUCCESS)
            {
                SQLGetData(hstmt, 1, SQL_CHAR, sqlSender, SQL_RESULT_LEN, &ptrSqlSender);
                SQLGetData(hstmt, 2, SQL_CHAR, sqlMessage, SQL_RESULT_LEN, &ptrSqlMessage);
                sender_message.push_back(std::make_pair((char*)sqlSender, (char*)sqlMessage));
            }

            std::cout << "SENDING MESSAGES TO " << user << std::endl;
        }
        else {
            throw(new Exception_query("couldn't send stored message", 9));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
    return sender_message;
}

std::vector<std::pair<std::string, std::string>> DB::pop_waiting_group_messages(std::string user)
{
    std::vector<std::pair<std::string, std::string>>       group_message;
    SQLRETURN                                              retcode;
    try{
    resetHanddle();

    // Prepare SQL statement
    SQLWCHAR* QUERY = (SQLWCHAR*)L"SELECT GM.Name, GM.Message FROM group_messages_for_user AS GM INNER JOIN Users AS U ON GM.ReceiverID = U.UserID WHERE U.UserName = ? ";
    retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

    // Bind parameters to the statement
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, user.length(), 0, (SQLPOINTER)user.c_str(), user.length(), NULL);

    // Execute the statement
    retcode = SQLExecute(hstmt);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {

        SQLCHAR sqlSender[SQL_RESULT_LEN];
        SQLLEN ptrSqlSender;
        SQLCHAR sqlMessage[SQL_RESULT_LEN];
        SQLLEN ptrSqlMessage;

        while (SQLFetch(hstmt) == SQL_SUCCESS)
        {
            SQLGetData(hstmt, 1, SQL_CHAR, sqlSender, SQL_RESULT_LEN, &ptrSqlSender);
            SQLGetData(hstmt, 2, SQL_CHAR, sqlMessage, SQL_RESULT_LEN, &ptrSqlMessage);
            group_message.push_back(std::make_pair((char*)sqlSender, (char*)sqlMessage));
        }

        std::cout << "EXTRACT MESSAGES FOR " << user << std::endl;
    }
    else {
        throw(new Exception_query("couldn't extract the messages", 10));
    }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

    return group_message;
}

void DB::delete_sent_messages(std::string receiver)
{
    SQLRETURN retcode;
    try{
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"DELETE WaitingMessages FROM WaitingMessages AS wm INNER JOIN Users AS u ON wm.ReceiverID = u.UserID WHERE u.UserName = ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

          // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "MESSAGES DELETED" << std::endl;
        }
        else if (retcode == 100)
        {
            std::cout << "NO MESSAGES LEFT" << std::endl;
        }
        else 
        {
            throw(new Exception_query("couldn't delete the messages", 8));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

}

void DB::delete_sent_group_messages(std::string receiver)
{
    SQLRETURN retcode;

    try{
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"DELETE GroupMessagesUsers FROM GroupMessagesUsers AS GM INNER JOIN Users AS U ON GM.ReceiverID=U.UserID	WHERE U.UserName= ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

          // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "GROUP MESSAGES DELETED" << std::endl;
        }
        else if (retcode == 100)
        {
            std::cout << "NO GROUP MESSAGES LEFT" << std::endl;
        }
        else {
            throw(new Exception_query("couldn't delete group messages", 11));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

void DB::create_group_with_members(std::string group_name, std::vector<std::string> users)
{
    try {
        this->create_empty_group(group_name);
        for (auto user = users.begin(); user != users.end(); user++)
        {
            this->add_member_in_group(group_name, (*user));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

void DB::create_empty_group(std::string group_name)
{
    SQLRETURN retcode;
    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"INSERT INTO Groups VALUES ( ? )";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, group_name.length(), 0, (SQLPOINTER)group_name.c_str(), group_name.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "GROUP CREATED" << std::endl;
        }
        else {
            throw(new Exception_query("couldn't create group", 12));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

void DB::add_member_in_group(std::string group_name, std::string username)
{
    SQLRETURN retcode;
    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"INSERT INTO GroupMembers VALUES((SELECT GroupID  FROM Groups WHERE Name = ?),(SELECT UserID FROM Users WHERE UserName = ?))";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, group_name.length(), 0, (SQLPOINTER)group_name.c_str(), group_name.length(), NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "MEMBER ADDED TO" << group_name << std::endl;
        }
        else {
            throw(new Exception_query("couldn't add member, possible invalid username", 13));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        throw(e);
    }
}

void DB::push_waiting_files(File& file, char* content)
{
    SQLRETURN       retcode;
    std::string     sender=file.get_sender();
    std::string     receiver=file.get_receiver();
    std::string     name=file.get_name();
    int             dimension=file.get_dimension();
    SQLLEN          cbData = dimension;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"exec insert_file_user_user  @Sender = ? , @Receiver = ? , @Name = ? , @Dimension = ? , @Content = ?";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sender.length(), 0, (SQLPOINTER)sender.c_str(), sender.length(), NULL);

        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);
        retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.length(), 0, (SQLPOINTER)name.c_str(), name.length(), NULL);
        retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &dimension, 0, NULL);
        retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_LONGVARBINARY, dimension, 0, (SQLPOINTER)content, 0, &cbData);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            std::cout << "FILE STORED" << name << " dimension :" << dimension << std::endl;
        }
        else {
            throw(new Exception_query("couldn't store the file", 14));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

std::vector<std::pair<File, char*>> DB::pop_waiting_files(std::string receiver)
{
    std::vector<std::pair<File, char*>>        whole_file;
    SQLRETURN                                  retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"SELECT U2.UserName, WF.Name, WF.Dimention, WF.File_content FROM WaitingFiles AS WF INNER JOIN Users AS U1 ON U1.UserID = WF.ReceiverID INNER JOIN Users AS U2 ON U2.UserID = WF.SenderID WHERE U1.UserName = ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {

            SQLCHAR sqlSender[SQL_RESULT_LEN];
            SQLLEN ptrSqlSender;
            SQLCHAR sqlName[SQL_RESULT_LEN];
            SQLLEN ptrSqlName;
            SQLINTEGER Dimension;
            SQLCHAR* binaryVal;
            SQLLEN binaryValLen;

            while (SQLFetch(hstmt) == SQL_SUCCESS)
            {
                SQLGetData(hstmt, 1, SQL_CHAR, sqlSender, SQL_RESULT_LEN, &ptrSqlSender);
                SQLGetData(hstmt, 2, SQL_CHAR, sqlName, SQL_RESULT_LEN, &ptrSqlName);
                SQLGetData(hstmt, 3, SQL_C_LONG, &Dimension, 0, NULL);
                binaryVal = new SQLCHAR[Dimension];
                SQLGetData(hstmt, 4, SQL_C_BINARY, binaryVal, Dimension, &binaryValLen);
                whole_file.push_back(std::make_pair(File((char*)sqlSender, receiver, (char*)sqlName, (int)Dimension), (char*)binaryVal));

            }

            std::cout << "SENDING FILES TO " << receiver << std::endl;
        }
        else {
            throw(new Exception_query("couldn't extract the file", 15));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

    return whole_file;
}

void DB::delete_sent_files(std::string receiver)
{
    SQLRETURN retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"DELETE WaitingFiles FROM WaitingFiles AS fm INNER JOIN Users AS u ON fm.ReceiverID = u.UserID WHERE u.UserName = ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "FILES DELETED" << std::endl;
        }
        else if (retcode == 100)
        {
            std::cout << "NO FILES LEFT" << std::endl;
        }
        else {
            throw(new Exception_query("couldn't delete files", 16));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

}

int DB::push_group_messages(std::string group, std::string sender, std::string message)
{
    SQLRETURN retcode;
    SQLINTEGER index;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"EXEC insert_message_group @Group = ?, @Sender = ?, @Message = ?, @index = ? OUTPUT";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, group.length(), 0, (SQLPOINTER)group.c_str(), group.length(), NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sender.length(), 0, (SQLPOINTER)sender.c_str(), sender.length(), NULL);
        retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, message.length(), 0, (SQLPOINTER)message.c_str(), message.length(), NULL);
        retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &index, 0, NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "GROUP MESSAGE STORED" << std::endl;

            // Bind output value to the index variable
            retcode = SQLBindCol(hstmt, 1, SQL_C_LONG, &index, 0, NULL);

            // Fetch the output value
            retcode = SQLFetch(hstmt);

            return static_cast<int>(index);
        }
        else {
            throw(new Exception_query("couldn't store group message", 17));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
    return 0;
}


void DB::push_group_message_for_user(int index, std::string receiver)
{
    SQLRETURN retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"INSERT INTO GroupMessagesUsers VALUES( ? , (SELECT TOP(1) UserID FROM Users WHERE UserName = ? )) ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &index, 0, NULL);

        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "MESSAGE STORED FOR THE USER" << receiver << std::endl;
        }
        else {
            throw(new Exception_query("couldn't store the message for the user (make the connection)", 18));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

std::vector<std::string> DB::get_group_members(std::string group, std::string sender)
{
    std::vector<std::string>       group_members;
    SQLRETURN                       retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"SELECT U.UserName FROM GroupMembers AS GM INNER JOIN Groups AS G ON GM.GroupID = G.GroupID INNER JOIN Users AS U ON GM.UserID = U.UserID WHERE G.Name = ? AND U.UserName <> ?";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, group.length(), 0, (SQLPOINTER)group.c_str(), group.length(), NULL);

        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sender.length(), 0, (SQLPOINTER)sender.c_str(), sender.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "EXTRACTED GROUP MEMBERS" << std::endl;

            SQLCHAR sqlGroup[SQL_RESULT_LEN];
            SQLLEN ptrSqlGroup;

            while (SQLFetch(hstmt) == SQL_SUCCESS)
            {
                SQLGetData(hstmt, 1, SQL_CHAR, sqlGroup, SQL_RESULT_LEN, &ptrSqlGroup);
                group_members.push_back((char*)sqlGroup);
            }
        }
        else {
            throw(new Exception_query("couldn't extract group members", 19));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

    return group_members;
}

int DB::push_waiting_group_files(File& file, char* content)
{
    SQLRETURN       retcode;
    SQLINTEGER      index;

    std::string     sender = file.get_sender();
    std::string     group = file.get_receiver();
    std::string     name = file.get_name();
    int             dimension = file.get_dimension();
    SQLLEN          cbData = dimension;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"exec insert_file_group @Group= ? ,@Sender= ? ,@Name= ? , @Dimension= ? , @File_content= ? , @index= ?  output";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, group.length(), 0, (SQLPOINTER)group.c_str(), group.length(), NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sender.length(), 0, (SQLPOINTER)sender.c_str(), sender.length(), NULL);
        retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.length(), 0, (SQLPOINTER)name.c_str(), name.length(), NULL);
        retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &dimension, sizeof(int), NULL);
        retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_LONGVARBINARY, dimension, 0, (SQLPOINTER)content, 0, &cbData);
        retcode = SQLBindParameter(hstmt, 6, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &index, sizeof(int), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "GROUP FILE STORED" << std::endl;

            // Bind output value to the index variable
            retcode = SQLBindCol(hstmt, 1, SQL_C_LONG, &index, 0, NULL);
            if (!SQL_SUCCEEDED(retcode)) {
                //TODO: Handle error
            }

            // Fetch the output value
            retcode = SQLFetch(hstmt);
            if (!SQL_SUCCEEDED(retcode)) {
                //TODO: Handle error
            }

            return static_cast<int>(index);
        }
        else {
            throw(new Exception_query("couldn't store group file", 20));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
    return 0;
}

void DB::push_waiting_group_files_for_user(int group_index, std::string receiver)
{
    SQLRETURN retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"INSERT INTO GroupFilesUsers VALUES( ? , (SELECT TOP(1) UserID FROM Users WHERE UserName = ? )) ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &group_index, 0, NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "FILE STORED FOR THE USER" << receiver << std::endl;
        }
        else {
            throw(new Exception_query("couldn't store file for the user (make the connection)", 21));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}

std::vector<std::pair<File, char*>> DB::pop_waiting_group_files(std::string receiver)
{
    std::vector<std::pair<File, char*>>        whole_file;
    SQLRETURN                                  retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"EXEC get_file_group @Username= ?";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        // Bind parameters to the statement
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {

            SQLCHAR sqlGroup[SQL_RESULT_LEN];
            SQLLEN ptrSqlGroup;
            SQLCHAR sqlName[SQL_RESULT_LEN];
            SQLLEN ptrSqlName;
            SQLINTEGER Dimension;
            SQLCHAR* binaryVal;
            SQLLEN binaryValLen;

            while (SQLFetch(hstmt) == SQL_SUCCESS)
            {
                SQLGetData(hstmt, 1, SQL_CHAR, sqlGroup, SQL_RESULT_LEN, &ptrSqlGroup);
                SQLGetData(hstmt, 2, SQL_CHAR, sqlName, SQL_RESULT_LEN, &ptrSqlName);
                SQLGetData(hstmt, 3, SQL_C_LONG, &Dimension, 0, NULL);
                binaryVal = new SQLCHAR[Dimension];
                SQLGetData(hstmt, 4, SQL_C_BINARY, binaryVal, Dimension, &binaryValLen);
                whole_file.push_back(std::make_pair(File("", (char*)sqlGroup, (char*)sqlName, (int)Dimension), (char*)binaryVal));

            }

            std::cout << "SENDING FILES TO " << receiver << std::endl;
        }
        else {
            throw(new Exception_query("couldn't send files", 22));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }

    return whole_file;
}

void DB::delete_sent_group_files(std::string receiver)
{
    SQLRETURN retcode;

    try {
        resetHanddle();

        // Prepare SQL statement
        SQLWCHAR* QUERY = (SQLWCHAR*)L"DELETE GroupFilesUsers FROM GroupFilesUsers AS GF INNER JOIN Users AS U ON GF.ReceiverID=U.UserID	WHERE U.UserName= ? ";
        retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, receiver.length(), 0, (SQLPOINTER)receiver.c_str(), receiver.length(), NULL);

        // Execute the statement
        retcode = SQLExecute(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            std::cout << "GROUP FILES DELETED " << std::endl;
        }
        else if (retcode == 100)
        {
            std::cout << "NO GROUP FILES LEFT" << std::endl;
        }
        else {
            throw(new Exception_query("couldn't delete group files", 23));
        }
    }
    catch (_IException* e)
    {
        e->handle_exception();
        delete e;
    }
}


