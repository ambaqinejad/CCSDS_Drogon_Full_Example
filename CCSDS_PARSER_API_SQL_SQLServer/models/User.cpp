#include "User.h"
#include <iostream>

void User::createTable(const DbClientPtr &client) {
//    client->execSqlAsync(
//    "CREATE TABLE Employees ("
//    "EmployeeID INT IDENTITY(1,1) PRIMARY KEY,"
//    "FirstName NVARCHAR(50),"
//    "LastName NVARCHAR(50),"
//    "Age INT,"
//    "Department NVARCHAR(50)"
//    ");",
//            [](const Result &r) {
//                std::cout << "Table checked/created successfully.\n";
//
//            },
//            [](const DrogonDbException &e) {
//                std::cerr << "Error creating table: " << e.base().what() << std::endl;
//            });
    client->execSqlSync("CREATE TABLE Employees ("
    "EmployeeID INT IDENTITY(1,1) PRIMARY KEY,"
    "FirstName NVARCHAR(50),"
    "LastName NVARCHAR(50),"
    "Age INT,"
    "Department NVARCHAR(50)"
    ");");
    client->execSqlSync("INSERT INTO Employees (FirstName, LastName, Age, Department)"
                "VALUES"
                "('John', 'Doe', 30, 'HR'),"
                "('Jane', 'Smith', 28, 'IT'),"
                "('Michael', 'Johnson', 35, 'Finance'),"
                "('Emily', 'Davis', 25, 'Marketing'),"
                "('David', 'Wilson', 40, 'Sales');");
}
