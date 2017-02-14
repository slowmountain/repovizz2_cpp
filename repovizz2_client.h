// Created by Panos Papiotis on 14/2/2017

#if defined(_WIN32) && !defined(__cplusplus_winrt)
// Extra includes for Windows desktop.
#include <windows.h>
#include <Shellapi.h>
#endif

#include "cpprest/http_listener.h"
#include "cpprest/http_client.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::oauth2::experimental;
using namespace web::http::experimental::listener;

//
// Utility method to open browser on Windows, OS X and Linux systems.
//
static void open_browser(utility::string_t auth_uri)
{
#if defined(_WIN32) && !defined(__cplusplus_winrt)
    // NOTE: Windows desktop only.
    auto r = ShellExecuteA(NULL, "open", conversions::utf16_to_utf8(auth_uri).c_str(), NULL, NULL, SW_SHOWNORMAL);
#elif defined(__APPLE__)
    // NOTE: OS X only.
    string_t browser_cmd(U("open \"") + auth_uri + U("\""));
    system(browser_cmd.c_str());
#else
    // NOTE: Linux/X11 only.
    string_t browser_cmd(U("xdg-open \"") + auth_uri + U("\""));
    system(browser_cmd.c_str());
#endif
}

//
// A simple listener class to capture OAuth 2.0 HTTP redirect to localhost.
// The listener captures redirected URI and obtains the token.
//
class repovizz2_code_listener
{
    public:
        repovizz2_code_listener(uri listen_uri, oauth2_config& config);
        ~repovizz2_code_listener();
        pplx::task<bool> listen_for_code()
        {
            return pplx::create_task(m_tce);
        }

    private:
        std::unique_ptr<http_listener> m_listener;
        pplx::task_completion_event<bool> m_tce;
        oauth2_config& m_config;
        std::mutex m_resplock;
};

//
// Base class for repovizz2 OAuth 2.0 sessions.
//
class repovizz2_client
{
public:
    repovizz2_client(utility::string_t client_id, utility::string_t client_secret, utility::string_t redirect_uri = U("http://localhost:5001"));
    void authorize();
    void get(utility::string_t query);
    void post(utility::string_t query);

protected:
    http_client_config m_http_config;
    http_client api;
    oauth2_config m_oauth2_config;
    pplx::task<bool> authorization_code_flow()
    {
        open_browser_auth();
        return m_listener->listen_for_code();
    };

private:
    utility::string_t m_name;
    std::unique_ptr<repovizz2_code_listener> m_listener;
    bool is_enabled() const;
    void open_browser_auth();
};
