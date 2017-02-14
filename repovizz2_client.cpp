// Modified version of Microsoft's OAuth2Client.cpp
// Retrieved on 14/2/2017 from https://github.com/Microsoft/cpprestsdk/tree/master/Release/samples/Oauth2Client
// Requires the cpprestsdk

#include "repovizz2_client.h"

//
// A simple listener class to capture OAuth 2.0 HTTP redirect to localhost.
// The listener captures redirected URI and obtains the token.
//

repovizz2_code_listener::repovizz2_code_listener(uri listen_uri, oauth2_config& config) :
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

repovizz2_code_listener::~repovizz2_code_listener()
{
    m_listener->close().wait();
}


//
// Base class for repovizz2 OAuth 2.0 sessions.
//
repovizz2_client::repovizz2_client(utility::string_t client_id,
    utility::string_t client_secret,
    utility::string_t redirect_uri) :
        m_oauth2_config(client_id,
            client_secret,
            U("http://repovizz2.upf.edu/oauth/authorize"),
            U("http://repovizz2.upf.edu/oauth/token"),
            redirect_uri),
        m_name(U("repovizz2")),
        m_listener(new repovizz2_code_listener(redirect_uri, m_oauth2_config)),
        api(U("http://repovizz2.upf.edu"))
        {
            m_oauth2_config.set_scope(U("basic"));
        }

void repovizz2_client::authorize()
{
    if (is_enabled())
    {
        ucout << "Running " << m_name.c_str() << " session..." << std::endl;

        if (!m_oauth2_config.token().is_valid_access_token())
        {
            if (authorization_code_flow().get())
            {
                m_http_config.set_oauth2(m_oauth2_config);
                api = http_client(U("http://repovizz2.upf.edu"), m_http_config);
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

void repovizz2_client::get(utility::string_t query)
{
    ucout << "Information: " << api.request(methods::GET, query).get().extract_json().get() << std::endl;
}

void repovizz2_client::post(utility::string_t query)
{
    ucout << "Yeah, not ready yet." << std::endl;
}


utility::string_t m_name;
std::unique_ptr<repovizz2_code_listener> m_listener;

bool repovizz2_client::is_enabled() const
{
    return !m_oauth2_config.client_key().empty() && !m_oauth2_config.client_secret().empty();
}

void repovizz2_client::open_browser_auth()
{
    auto auth_uri(m_oauth2_config.build_authorization_uri(true));
    ucout << "Opening browser in URI:" << std::endl;
    ucout << auth_uri << std::endl;
    open_browser(auth_uri);
}

