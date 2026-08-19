#pragma once
#include <sqlite3.h>
#include <string>

class ConnecterDBSQLite
{
private:
    sqlite3* dbHandler;
public:
    ConnecterDBSQLite(std::string&& DBPath);
    ConnecterDBSQLite(const ConnecterDBSQLite&) = delete;
    ConnecterDBSQLite(ConnecterDBSQLite&&) = delete;
    ConnecterDBSQLite& operator=(const ConnecterDBSQLite&) = delete;
    ConnecterDBSQLite& operator=(ConnecterDBSQLite&&) = delete;
    ~ConnecterDBSQLite();


    sqlite3* getHandle() const;
};
