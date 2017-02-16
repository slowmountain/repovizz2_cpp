//
// Created by Panos Papiotis on 16/02/17.
//

#include "oauth2_session.h"

#ifndef REPOVIZZ2_CLIENT_REPOVIZZ2_CLIENT_H
#define REPOVIZZ2_CLIENT_REPOVIZZ2_CLIENT_H

#endif //REPOVIZZ2_CLIENT_REPOVIZZ2_CLIENT_H

using namespace web::json;

class repovizz2_client : public oauth2_session
{
    public:
        repovizz2_client(utility::string_t client_id, utility::string_t client_secret, utility::string_t redirect_uri);
        value get_myself();
        value get_datapack(utility::string_t datapack_id);
        void post(utility::string_t query);

    private:
        value get(utility::string_t query);
};