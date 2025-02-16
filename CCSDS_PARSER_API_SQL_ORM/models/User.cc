//
// Created by Chromium on 16/02/2025.
//
#include "User.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Criteria.h>
#include <drogon/drogon.h>
#include <trantor/utils/Date.h>

using namespace drogon;
using namespace drogon::orm;

void drogon_model::sqlite::User::save(const int &dbClient) {
    Mapper<User> userMapper(dbClient);
    userMapper.insert(*this);
}

static std::optional<User> drogon_model::sqlite::User::findById(const int &dbClient, int userId) {
    Mapper<User> userMapper(dbClient);
    try {
        return userMapper.findByPrimaryKey(userId);
    } catch (const DrogonDbException& e) {
        LOG_ERROR << e.base().what();
        return std::nullopt;
    }
}

static std::vector<User> drogon_model::sqlite::User::getAll(const int &dbClient) {
    Mapper<User> userMapper(dbClient);
    return userMapper.findAll();
}