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

bool DB::verify_account(std::string username, std::string password)
{
    bool            valid = false;
    SQLRETURN       retcode;

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"SELECT * FROM Users WHERE UserName = ? AND Password = ?", SQL_NTS);

    // Bind the parameters to the variables
    retcode=SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), username.length(), NULL);
    retcode=SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, (SQLPOINTER)password.c_str(), password.length(), NULL);
    retcode = SQLExecute(hstmt);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
    {
        if(SQLFetch(hstmt) == SQL_SUCCESS) 
        {
            valid = true;
        }
    }
    else {
        //TODO EXCEPTION
    }

    // Reset the statement for the next uses
    SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    SQLFreeStmt(hstmt, SQL_UNBIND);

    return valid;
}
