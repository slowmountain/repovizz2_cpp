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

void repovizz2_client::get(utility::string_t query)
{
    ucout << "Information: " << api.request(methods::GET, query).get().extract_json().get() << std::endl;
}

void repovizz2_client::post(utility::string_t query)
{
    ucout << "Yeah, not ready yet." << std::endl;
}