#include <drogon/drogon.h>
//#include "User.h"

int main() {
    // Load the configuration file
    drogon::app().loadConfigFile("../config.json");

    drogon::app().getLoop()->runAfter(0, []() {
        auto dbClient = drogon::app().getDbClient("sqlite_db");
        if (!dbClient) {
            std::cout << "Not Connected!" << std::endl;
        } else {
            std::cout << "Database Connected!" << "fdfdfdfdf" <<std::endl;
//            User::createTable(dbClient);
        }
    });

    // Start the Drogon app
    drogon::app().run();
    return 0;
}
