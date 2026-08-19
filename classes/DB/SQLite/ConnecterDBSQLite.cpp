#include "ConnecterDBSQLite.h"
#include <iostream>

ConnecterDBSQLite::ConnecterDBSQLite(std::string&& DBPath) {
    if (sqlite3_open(DBPath.c_str(), &dbHandler) != SQLITE_OK) {
        throw std::runtime_error("Failed to open SQLite");
    }
    sqlite3_exec(dbHandler, "PRAGMA journal_mode = WAL;", nullptr, nullptr, nullptr);
}


ConnecterDBSQLite::~ConnecterDBSQLite(){
    if(dbHandler){
        sqlite3_exec(dbHandler, "PRAGMA journal_mode = DELETE;", nullptr, nullptr, nullptr);
        sqlite3_close(dbHandler);
    }
}

sqlite3* ConnecterDBSQLite::getHandle() const{
    return dbHandler;
}
