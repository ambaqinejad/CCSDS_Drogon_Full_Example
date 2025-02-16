#pragma once
#include <drogon/HttpController.h>
#include "../models/User.h"
#include "UserController.h"

void UserController::createUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
    auto json = req->getJsonObject();
    if (!json || !json->isMember("name") || !json->isMember("email")) {
        auto res = HttpResponse::newHttpJsonResponse({{"error", "Missing parameters"}});
        res->setStatusCode(HttpStatusCode::k400BadRequest);
        return callback(res);
    }

    auto dbClient = app().getDbClient("sqlite_db");

    User user(0, (*json)["name"].asString(), (*json)["email"].asString(), trantor::Date::now());
    user.save(dbClient);

    auto res = HttpResponse::newHttpJsonResponse({{"message", "User created successfully"}});
    return callback(res);
}

void UserController::getUsers(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
    auto dbClient = app().getDbClient("sqlite_db");

    auto users = User::getAll(dbClient);
    Json::Value result(Json::arrayValue);
    for (const auto& user : users) {
        Json::Value jsonUser;
        jsonUser["id"] = user.id;
        jsonUser["name"] = user.name;
        jsonUser["email"] = user.email;
        jsonUser["created_at"] = user.created_at.toDbStringLocal();
        result.append(jsonUser);
    }

    auto res = HttpResponse::newHttpJsonResponse(result);
    callback(res);
}


void UserController::getUserById(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId) {
    auto dbClient = app().getDbClient("sqlite_db");

    auto user = User::findById(dbClient, userId);
    if (!user) {
        auto res = HttpResponse::newHttpJsonResponse({{"error", "User not found"}});
        res->setStatusCode(HttpStatusCode::k404NotFound);
        return callback(res);
    }

    Json::Value jsonUser;
    jsonUser["id"] = user->id;
    jsonUser["name"] = user->name;
    jsonUser["email"] = user->email;
    jsonUser["created_at"] = user->created_at.toDbStringLocal();

    auto res = HttpResponse::newHttpJsonResponse(jsonUser);
    callback(res);
}