#include "User.h"
#include <iostream>

void User::createTable(const DbClientPtr &client) {
    client->execSqlAsync(
            "CREATE TABLE users ("
            "id INT AUTO_INCREMENT PRIMARY KEY,"
            "name VARCHAR(255) NOT NULL,"
            "email VARCHAR(255) UNIQUE NOT NULL"
            ");",
            [](const Result &r) {
                std::cout << "Table checked/created successfully.\n";
            },
            [](const DrogonDbException &e) {
                std::cerr << "Error creating table: " << e.base().what() << std::endl;
            });
}
