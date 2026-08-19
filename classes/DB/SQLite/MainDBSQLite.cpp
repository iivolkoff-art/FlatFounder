#include "MainDBSQLite.h"
#include <iostream>

MainDBSQLite::MainDBSQLite(std::string dbPath) : dbPath(std::move(dbPath)) {
}

bool MainDBSQLite::connectToDb(){
    try{
        sqlConnecter = std::make_unique<ConnecterDBSQLite>(std::move(dbPath));
    }
    catch(const std::runtime_error& error){
        std::cerr << "Error: Connector error: " << error.what() << std::endl;
        return false;
    }

    sqlite3* db = sqlConnecter->getHandle();

    sqlite3_exec(db, "PRAGMA journal_mode = DELETE;", nullptr, nullptr, nullptr);
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    std::string create_landlords =
        "CREATE TABLE IF NOT EXISTS landlords ("
        "phone TEXT PRIMARY KEY, "
        "name TEXT, "
        "is_agent INTEGER DEFAULT 0, "
        "is_ban INTEGER DEFAULT 0);";

    std::string create_listings =
        "CREATE TABLE IF NOT EXISTS listings ("
        "url TEXT PRIMARY KEY, "
        "price_info TEXT, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char* err_msg = nullptr;
    sqlite3_exec(db, create_landlords.c_str(), nullptr, nullptr, &err_msg);
    sqlite3_exec(db, create_listings.c_str(), nullptr, nullptr, &err_msg);

    if (err_msg) {
        std::cerr << "Error: cannot create tables: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

bool MainDBSQLite::saveProperty(const Result& res) {
    if(!sqlConnecter) return false;
    sqlite3* db = sqlConnecter->getHandle();
    sqlite3_stmt* stmt;

    if (!res.number.empty()) {
        std::string sql_landlord =
            "INSERT INTO landlords (phone, name, is_agent) VALUES (?, ?, ?) "
            "ON CONFLICT(phone) DO UPDATE SET "
            "name = excluded.name, "
            "is_agent = CASE WHEN excluded.is_agent = 1 THEN 1 ELSE is_agent END;";

        if (sqlite3_prepare_v2(db, sql_landlord.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, res.number.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, res.ownerName.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, res.isAgent ? 1 : 0);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Error: failed to prepare UPSERT landlords: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
    }

    std::string sql_listing = "INSERT INTO listings (url, price_info) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql_listing.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error: failed to prepare INSERT listings: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, res.link.c_str(), -1, SQLITE_STATIC);

    std::string full_price = res.price + " " + res.currency;
    sqlite3_bind_text(stmt, 2, full_price.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (rc == SQLITE_DONE);
}

bool MainDBSQLite::clearOldHistory(int daysToKeep){
    if(!sqlConnecter) return false;
    sqlite3_stmt* stmt;
    std::string sql = "DELETE FROM listings WHERE created_at < datetime('now', '-' || ? || ' days');";

    if (sqlite3_prepare_v2(sqlConnecter->getHandle(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, daysToKeep);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

bool MainDBSQLite::isUrlExists(const std::string& url){
    if(!sqlConnecter) return false;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT 1 FROM listings WHERE url = ?;";

    if (sqlite3_prepare_v2(sqlConnecter->getHandle(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, url.c_str(), -1, SQLITE_STATIC);
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);

    return exists;
}

bool MainDBSQLite::isBan(const std::string& phone){
    if(!sqlConnecter) return false;
    if (phone.empty()) return false;

    sqlite3_stmt* stmt;
    std::string sql = "SELECT is_ban FROM landlords WHERE phone = ?;";

    if (sqlite3_prepare_v2(sqlConnecter->getHandle(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, phone.c_str(), -1, SQLITE_STATIC);

    bool banned = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        banned = (sqlite3_column_int(stmt, 0) == 1);
    }

    sqlite3_finalize(stmt);
    return banned;
}

bool MainDBSQLite::isAgent(const std::string& phone){
    if(!sqlConnecter) return false;
    if (phone.empty()) return false;

    sqlite3_stmt* stmt;
    std::string sql = "SELECT is_agent FROM landlords WHERE phone = ?;";

    if (sqlite3_prepare_v2(sqlConnecter->getHandle(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, phone.c_str(), -1, SQLITE_STATIC);

    bool agent = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        agent = (sqlite3_column_int(stmt, 0) == 1);
    }

    sqlite3_finalize(stmt);
    return agent;
}

MainDBSQLite::~MainDBSQLite(){
    if (sqlConnecter) {
        sqlConnecter.reset();
    }
}
