#include <drogon/drogon.h>
#include "User.h"
#include <nanodbc/nanodbc.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/odbc/connection.h>

SQLPP_ALIAS_PROVIDER(users);
struct Users {
    struct Id {
        struct _alias_t {
            static constexpr const char _literal[] = "id";
        };
    };
    struct Name {
        struct _alias_t {
            static constexpr const char _literal[] = "name";
        };
    };
};

int main() {
    // Load the configuration file
    drogon::app().loadConfigFile("../config.json");

//    // Get the database client
//    auto dbClient = drogon::app().getDbClient("sqlite_db");
//
//    // Ensure the users table exists
//    User::createTable(dbClient);
    drogon::app().getLoop()->runAfter(0, []() {
        // first method
        // auto dbClient = drogon::app().getDbClient("mysql_db");

        // second method
        std::string connectionString = "Driver={ODBC Driver 17 for SQL Server};"
                                       "Server=tcp:192.168.41.233,1433;"
                                       "Database=tes;"
                                       "UID=sa;"
                                       "PWD=mobin@mobin;";
//        std::string connectionString = "host=host.docker.internal port=3306 dbname=drogondb user=root password=Mbam475275$";
        auto dbClient = drogon::orm::DbClient::newSqlite3Client(connectionString, 1);

        if (!dbClient) {
            std::cout << "Not Connected!" << std::endl;
        } else {
            std::cout << "Database Connected!" << std::endl;
//            User::createTable(dbClient);
            auto result = dbClient->execSqlSync("SELECT * FROM Employees;");

            for (auto row : result) {
                std::cout << "FirstName: " << row["FirstName"].as<std::string>() << ", LastName: " << row["LastName"].as<std::string>() << std::endl;
            }
        }
    });

    // Start the Drogon app
    drogon::app().run();
    return 0;
}
