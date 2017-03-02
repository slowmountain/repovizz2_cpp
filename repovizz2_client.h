//
// Created by Panos Papiotis on 16/02/17.
//

#include "oauth2_session.h"
#include "cpprest/filestream.h"

#ifndef REPOVIZZ2_CLIENT_REPOVIZZ2_CLIENT_H
#define REPOVIZZ2_CLIENT_REPOVIZZ2_CLIENT_H

#endif //REPOVIZZ2_CLIENT_REPOVIZZ2_CLIENT_H

using namespace web::json;
using namespace concurrency::streams;

class repovizz2_client : public oauth2_session
{
    public:
        repovizz2_client(utility::string_t client_id, utility::string_t client_secret, utility::string_t redirect_uri);
        http_response get_myself();
        http_response get_datapack(utility::string_t datapack_id);
        http_response upload_datapack(json::value datapack_structure);
        void upload_datapack_files(utility::string_t datapack_id);
        http_response upload_file(utility::string_t datapack_id, utility::string_t file_id, utility::string_t file_path);

    private:
        http_response get(utility::string_t query);
};

json::value read_JSON(string_t path);
std::vector<string_t> search_datapack(json::value datapack_structure, string_t node_type);