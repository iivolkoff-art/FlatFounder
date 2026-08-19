#pragma once
#include "DB/IMainSql.h"
#include "DB/SQLite/ConnecterDBSQLite.h"
#include <memory>

class MainDBSQLite : public IMainSql
{
private:
    std::string dbPath;
    std::unique_ptr<ConnecterDBSQLite> sqlConnecter;
public:
    MainDBSQLite(std::string dbPath);

    bool connectToDb() override;

    bool saveProperty(const Result& res) override;
    bool clearOldHistory(int daysToKeep) override;

    bool isUrlExists(const std::string& url) override;
    bool isBan(const std::string& phone) override;
    bool isAgent(const std::string& phone) override;

    ~MainDBSQLite();
};

