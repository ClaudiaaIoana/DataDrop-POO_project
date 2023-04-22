#include "DB.h"

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
        //TODO EXCEPTION
    case SQL_ERROR:
        std::cout << "Could not connect to SQL Server";
        std::cout << "\n";
        //TODO EXCEPTION
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
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
       
    }
}

bool DB::verify_account(std::string username, std::string password)
{
    bool valid = false;
    SQLRETURN retcode;

    resetHanddle();

    // Prepare SQL statement
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"SELECT * FROM Users WHERE UserName = ? AND Password = ?", SQL_NTS);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
        return false;
    }

    // Bind parameters to the statement
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
        return false;
    }
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, (SQLPOINTER)password.c_str(), password.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
        return false;
    }

    // Execute the statement
    retcode = SQLExecute(hstmt);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        if (SQLFetch(hstmt) == SQL_SUCCESS) {
            valid = true;
        }
    }
    else {
        //TODO: Handle error
        return false;
    }

    return valid;
}

void DB::add_account(std::string username, std::string email, std::string password)
{
    SQLRETURN retcode;

    resetHanddle();

    // Prepare SQL statement
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO Users VALUES ( ? , ? , ? )", SQL_NTS);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
        
    }

    // Bind parameters to the statement
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
        
    }
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, (SQLPOINTER)password.c_str(), password.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error

    }
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, email.length(), 0, (SQLPOINTER)email.c_str(), email.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error
        
    }

    // Execute the statement
    retcode = SQLExecute(hstmt);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        if (SQLFetch(hstmt) == SQL_SUCCESS) {
            std::cout << "ACCOUNT CREATED WITH SUCCES" << std::endl;
        }
    }
    else {
        //TODO: Handle error
        std::cout << "ERROR AT CREATING CODE, POSSIBLE EXISTING"<<std::endl;
    }
}

bool DB::add_friend(std::string user1, std::string user2)
{
    SQLRETURN retcode;

    resetHanddle();

    // Prepare SQL statement
    SQLWCHAR* QUERY = (SQLWCHAR*)L"INSERT INTO Friendships VALUES ((SELECT UserID FROM Users WHERE UserName = ? ),(SELECT UserID FROM Users WHERE UserName = ? ))";
    retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error

    }

    // Bind parameters to the statement
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, user1.length(), 0, (SQLPOINTER)user1.c_str(), user1.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error

    }
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, user2.length(), 0, (SQLPOINTER)user2.c_str(), user2.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error

    }

    // Execute the statement
    retcode = SQLExecute(hstmt);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
        std::cout << "FRIENDSHIP CREATED" << std::endl;
        return true;
    }
    else {
        //TODO: Handle error
        std::cout << "ERROR, POSSIBLE WORNG USERNAME" << std::endl;
    }

    return false;
}

std::vector<std::string> DB::get_friend_list(std::string username)
{
    std::vector<std::string>        usernames;
    SQLRETURN                       retcode;

    resetHanddle();

    // Prepare SQL statement
    SQLWCHAR* QUERY = (SQLWCHAR*)L"EXEC FriendsList ? ";
    retcode = SQLPrepare(hstmt, QUERY, SQL_NTS);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error

    }

    // Bind parameters to the statement
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);
    if (!SQL_SUCCEEDED(retcode)) {
        //TODO: Handle error

    }

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
    else {
        //TODO: Handle error
        std::cout << "ERROR WHILE EXECUTING QUERY" << std::endl;
    }

    return usernames;
}


