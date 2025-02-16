#pragma once

#include <drogon/HttpController.h>
#include <drogon/orm/DbClient.h>
#include <json/json.h>

using namespace drogon;
using namespace drogon::orm;

class User : public drogon::HttpController<User> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(User::getUsers, "/users", Get);
    ADD_METHOD_TO(User::addUser, "/users", Post);
    METHOD_LIST_END

    void getUsers(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void addUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
