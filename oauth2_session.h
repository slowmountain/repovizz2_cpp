// Modified version of Microsoft's OAuth2Client.cpp
// Retrieved on 14/2/2017 from https://github.com/Microsoft/cpprestsdk/tree/master/Release/samples/Oauth2Client
// Requires the cpprestsdk
// Created by Panos Papiotis on 16/2/2017

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
// This type of listener can be implemented in the back-end to capture and store tokens.
//
class oauth2_code_listener
{
    public:
        oauth2_code_listener(uri listen_uri, oauth2_config& config);
        ~oauth2_code_listener();
        pplx::task<bool> listen_for_code();

    private:
        std::unique_ptr<http_listener> m_listener;
        pplx::task_completion_event<bool> m_tce;
        oauth2_config& m_config;
        std::mutex m_resplock;
};

//
// Base class for OAuth 2.0 sessions.
//
class oauth2_session
{
    public:
        oauth2_session(utility::string_t name,
                       utility::string_t base_url,
                       utility::string_t client_key,
                       utility::string_t client_secret,
                       utility::string_t auth_endpoint,
                       utility::string_t token_endpoint,
                       utility::string_t redirect_uri);
        void authorize();

    protected:
        pplx::task<bool> authorization_code_flow();

        http_client_config m_http_config;
        http_client api;
        oauth2_config m_oauth2_config;

    private:
        bool is_enabled() const;
        void open_browser_auth();

        utility::string_t m_name;
        std::unique_ptr<oauth2_code_listener> m_listener;
};
