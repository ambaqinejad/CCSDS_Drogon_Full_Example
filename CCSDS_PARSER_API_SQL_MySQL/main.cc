#include <drogon/drogon.h>
#include "User.h"

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
        std::string connectionString = "host=host.docker.internal port=3306 dbname=drogondb user=root password=Mbam475275$";
        auto dbClient = drogon::orm::DbClient::newMssqlClient(connectionString, 1);

        if (!dbClient) {
            std::cout << "Not Connected!" << std::endl;
        } else {
            std::cout << "Database Connected!" << std::endl;
            User::createTable(dbClient);
            auto result = dbClient->execSqlSync("SELECT * FROM users;");

            // Print the query result
            for (auto row : result) {
                std::cout << "ID: " << row["id"].as<int>() << ", Name: " << row["name"].as<std::string>() << std::endl;
            }
        }
    });

    // Start the Drogon app
    drogon::app().run();
    return 0;
}
