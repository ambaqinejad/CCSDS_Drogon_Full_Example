#pragma once
#include <drogon/HttpController.h>
#include "../models/User.h"

using namespace drogon;
using namespace drogon_model::sqlite;

class UserController : public HttpController<UserController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::createUser, "/user/create", Post);
    ADD_METHOD_TO(UserController::getUsers, "/users", Get);
    ADD_METHOD_TO(UserController::getUserById, "/user/{1}", Get);
    METHOD_LIST_END

    void createUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);
    void getUsers(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);
    void getUserById(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId);
}