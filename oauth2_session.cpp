// Modified version of Microsoft's OAuth2Client.cpp
// Retrieved on 14/2/2017 from https://github.com/Microsoft/cpprestsdk/tree/master/Release/samples/Oauth2Client
// Requires the cpprestsdk
// Created by Panos Papiotis on 16/2/2017

#include "oauth2_session.h"

/************ OAUTH2_CODE_LISTENER declarations  ************/

oauth2_code_listener::oauth2_code_listener(uri listen_uri, oauth2_config& config) :
    m_listener(new http_listener(listen_uri)),
    m_config(config)
    {
        m_listener->support([this](http::http_request request) -> void
        {
            if (request.request_uri().path() == U("/") && request.request_uri().query() != U(""))
            {
                m_resplock.lock();

                m_config.token_from_redirected_uri(request.request_uri()).then([this,request](pplx::task<void> token_task) -> void
                {
                   try
                   {
                       token_task.wait();
                       m_tce.set(true);
                   }
                   catch (const oauth2_exception& e)
                   {
                       ucout << "Error: " << e.what() << std::endl;
                       m_tce.set(false);
                   }
                });

                request.reply(status_codes::OK, U("Ok."));

                m_resplock.unlock();
            }
            else
            {
                request.reply(status_codes::NotFound, U("Not found."));
            }
        });

        m_listener->open().wait();
    }

oauth2_code_listener::~oauth2_code_listener()
{
    m_listener->close().wait();
}

pplx::task<bool> oauth2_code_listener::listen_for_code()
{
    return pplx::create_task(m_tce);
}

/************ OAUTH2_SESSION declarations  ************/

oauth2_session::oauth2_session(utility::string_t name,
                               utility::string_t base_url,
                               utility::string_t client_key,
                               utility::string_t client_secret,
                               utility::string_t auth_endpoint,
                               utility::string_t token_endpoint,
                               utility::string_t redirect_uri) :
    m_oauth2_config(client_key,
                    client_secret,
                    auth_endpoint,
                    token_endpoint,
                    redirect_uri),
    m_name(name),
    m_listener(new oauth2_code_listener(redirect_uri, m_oauth2_config)),
    api(base_url){}

pplx::task<bool> oauth2_session::authorization_code_flow()
{
    open_browser_auth();
    return m_listener->listen_for_code();
}

bool oauth2_session::is_enabled() const
{
    return !m_oauth2_config.client_key().empty() && !m_oauth2_config.client_secret().empty();
}

void oauth2_session::open_browser_auth()
{
    auto auth_uri(m_oauth2_config.build_authorization_uri(true));
    ucout << "Opening browser in URI:" << std::endl;
    ucout << auth_uri << std::endl;
    open_browser(auth_uri);
}

void oauth2_session::authorize()
{
    if (is_enabled())
    {
        ucout << "Running " << m_name.c_str() << " session..." << std::endl;

        if (!m_oauth2_config.token().is_valid_access_token())
        {
            if (authorization_code_flow().get())
            {
                m_http_config.set_oauth2(m_oauth2_config);
                api = http_client(api.base_uri(), m_http_config);
            }
            else
            {
                ucout << "Authorization failed for " << m_name.c_str() << "." << std::endl;
            }
        }
    }
    else
    {
        ucout << "Skipped " << m_name.c_str() << " session sample because app key or secret is empty. Please see instructions." << std::endl;
    }
}

