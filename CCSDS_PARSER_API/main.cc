#include <drogon/drogon.h>
#include <iostream>
int main() {
    // Load config file
    drogon::app().loadConfigFile("../config.json");

    // Initialize the application (without blocking)
    drogon::app().getLoop()->runAfter(0, []() {
        auto dbClient = drogon::app().getDbClient("sqlite_db");
        if (!dbClient) {
            std::cout << "Not Connected!" << std::endl;
        } else {
            std::cout << "Database Connected!" << std::endl;
        }

        dbClient->execSqlSync("CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT);");

        // Insert sample data
        dbClient->execSqlSync("INSERT INTO test (name) VALUES ('Drogon SQLite');");

        // Query data
        auto result = dbClient->execSqlSync("SELECT * FROM users;");

        // Print the query result
        for (auto row : result) {
            std::cout << "ID: " << row["id"].as<int>() << ", Name: " << row["name"].as<std::string>() << std::endl;
        }
    });

    // Run the event loop
    drogon::app().run();
    return 0;
}
