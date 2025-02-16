#include "User.h"
#include <iostream>

void User::createTable(const DbClientPtr &client) {
    client->execSqlAsync(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT NOT NULL, "
            "email TEXT UNIQUE NOT NULL);",
            [](const Result &r) {
                std::cout << "Table checked/created successfully.\n";
            },
            [](const DrogonDbException &e) {
                std::cerr << "Error creating table: " << e.base().what() << std::endl;
            });
}
