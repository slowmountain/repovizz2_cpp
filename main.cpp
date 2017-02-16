#include "repovizz2_client.h"

using namespace std;

int main() {
    json::value about_me, datapack;

    // Create a repovizz2_client object
    // You must provide the client id, secret, and redirect URL
    repovizz2_client my_client(U("43e7a909-6011-47e2-b58e-200e72bd8b06"), U("33d728c7-a5ab-4406-86e6-9702c6546a5e"), U("http://localhost:5001"));

    // Authorize client
    my_client.authorize();

    // Get info about the current user
    about_me = my_client.get_myself();

    //Print the name of each of the user's uploaded datapacks
    cout<<"Your uploaded datapacks are the following:"<<endl;
    for (int i=0; i<about_me["datapacks"].size(); i++)
    {
        datapack = my_client.get_datapack(about_me["datapacks"][i].as_string());
        cout<<" - "<<datapack["name"].as_string()<<endl;
    }

    return 0;
}



