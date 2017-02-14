#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>

using namespace std;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::oauth2::experimental;
using namespace utility;

int main() {
    string_t redirect_uri(U("http://localhost:5001"));
    string_t authorization_endpoint(U("http://repovizz2.upf.edu/oauth/authorize"));
    string_t token_endpoint(U("http://repovizz2.upf.edu/oauth/token"));
    string_t client_scope(U("basic"));


    oauth2_config oauth2_config(U("43e7a909-6011-47e2-b58e-200e72bd8b06"), /* CLIENT ID*/
                                U("33d728c7-a5ab-4406-86e6-9702c6546a5e"), /* CLIENT SECRET*/
                                authorization_endpoint, token_endpoint, redirect_uri, client_scope);

    string_t auth_uri = oauth2_config.build_authorization_uri(false);

    cout<<auth_uri<<endl;
}



