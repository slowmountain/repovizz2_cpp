//
// Created by Panos Papiotis on 16/02/17.
//

#include "repovizz2_client.h"

repovizz2_client::repovizz2_client(utility::string_t client_id, utility::string_t client_secret, utility::string_t redirect_uri = U("localhost:50009")) :
        oauth2_session(U("repovizz2"),
        U("http://repovizz2.upf.edu"),
        client_id,
        client_secret,
        U("http://repovizz2.upf.edu/oauth/authorize"),
        U("http://repovizz2.upf.edu/oauth/token"),
        redirect_uri)
        {
            m_oauth2_config.set_scope(U("basic"));
        }

value repovizz2_client::get(utility::string_t query)
{
    return api.request(methods::GET, query).get().extract_json().get();
}

value repovizz2_client::get_myself()
{
    return get(U("/api/v1.0/user"));
}

value repovizz2_client::get_datapack(utility::string_t datapack_id)
{
    return get(U("/api/v1.0/datapacks/")+datapack_id);
}

void repovizz2_client::post(utility::string_t query)
{
    ucout << "Yeah, not ready yet." << std::endl;
}

//TODO: add and test POST requests