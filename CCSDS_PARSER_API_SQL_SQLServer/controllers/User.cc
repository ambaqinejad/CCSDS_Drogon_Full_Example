#include "User.h"
#include <drogon/drogon.h>

void User::getUsers(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    drogon::app().getLoop()->runAfter(0, [callback = std::move(callback)]() mutable {
        auto dbClient = drogon::app().getDbClient("sqlite_db");
        if (!dbClient) {
            std::cout << "Not Connected!" << std::endl;
        } else {
            std::cout << "Database Connected!" << std::endl;
            dbClient->execSqlAsync(
                    "SELECT id, name, email FROM users;",
                    [callback](const Result &result) {
                        Json::Value json;
                        for (const auto &row: result) {
                            Json::Value user;
                            user["id"] = row["id"].as<int>();
                            user["name"] = row["name"].as<std::string>();
                            user["email"] = row["email"].as<std::string>();
                            json.append(user);
                        }
                        auto resp = HttpResponse::newHttpJsonResponse(json);
                        callback(resp);
                    },
                    [callback](const DrogonDbException &e) {
                        auto resp = HttpResponse::newHttpResponse();
                        resp->setStatusCode(HttpStatusCode::k500InternalServerError);
                        resp->setBody("Database error: " + std::string(e.base().what()));
                        callback(resp);
                    });
        }
    });


}

void User::addUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();
    if (!json || !json->isMember("name") || !json->isMember("email")) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
        resp->setBody("Missing name or email");
        callback(resp);
        return;
    }

    std::string name = (*json)["name"].asString();
    std::string email = (*json)["email"].asString();
//    auto client = app().getDbClient();
    drogon::app().getLoop()->runAfter(0, [callback = std::move(callback), name = std::move(name), email = std::move(
            email)]() mutable {
        auto dbClient = drogon::app().getDbClient("sqlite_db");
        if (!dbClient) {
            std::cout << "Not Connected!" << std::endl;
        } else {
            std::cout << "Database Connected!" << std::endl;
            dbClient->execSqlAsync(
                    "INSERT INTO users (name, email) VALUES (?, ?);",
                    [callback](const Result &r) {
                        auto resp = HttpResponse::newHttpResponse();
                        resp->setStatusCode(HttpStatusCode::k201Created);
                        resp->setBody("User added successfully");
                        callback(resp);
                    },
                    [callback](const DrogonDbException &e) {
                        auto resp = HttpResponse::newHttpResponse();
                        resp->setStatusCode(HttpStatusCode::k500InternalServerError);
                        resp->setBody("Database error: " + std::string(e.base().what()));
                        callback(resp);
                    },
                    name, email);
        }

    });
}
