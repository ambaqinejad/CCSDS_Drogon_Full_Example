#pragma once
#include <drogon/orm/Mapper.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Criteria.h>
#include <drogon/drogon.h>
#include <trantor/utils/Date.h>

using namespace drogon;
using namespace drogon::orm;

namespace drogon_model {
    namespace sqlite {

        class User : public drogon::orm::DrogonModel<User> {
        public:
            struct MetaData {
                static constexpr const char *tableName = "users";
                static constexpr const char *id = "id";
                static constexpr const char *name = "name";
                static constexpr const char *email = "email";
                static constexpr const char *created_at = "created_at";
            };

            // Fields
            int id;
            std::string name;
            std::string email;
            trantor::Date created_at;

            // Constructor
            User() = default;

            User(int userId, std::string userName, std::string userEmail, trantor::Date createdAt)
                    : id(userId), name(std::move(userName)), email(std::move(userEmail)), created_at(createdAt) {}

            // Save user using ORM
            void save(const std::shared_ptr <DbClient> &dbClient);

            static std::optional <User> findById(const std::shared_ptr <DbClient> &dbClient, int userId);

            static std::vector <User> getAll(const std::shared_ptr <DbClient> &dbClient);
        };
    }
}