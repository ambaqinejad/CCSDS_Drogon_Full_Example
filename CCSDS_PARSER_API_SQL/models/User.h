#pragma once
#include <drogon/orm/Mapper.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Result.h>
#include <memory>
#include <string>

using namespace drogon::orm;

class User {
public:
    int id;
    std::string name;
    std::string email;

    User(int id, const std::string &name, const std::string &email)
            : id(id), name(name), email(email) {}

    static void createTable(const DbClientPtr &client);
};

//using UserMapper = Mapper<User>