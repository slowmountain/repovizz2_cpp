#include "repovizz2_client.h"

using namespace std;

int main() {
    json::value about_me, datapack, datapack_structure, response;

    // Create a repovizz2_client object
    // You must provide the client id, secret, and redirect URL
    repovizz2_client my_client(U("1045f1ec-da70-46d6-ab79-db94d21044d2"), U("141c1fab-38a8-46e2-8011-10cbe14dd93b"), U("http://localhost:5001"));

    // Authorize client
    my_client.authorize();

    // Get info about the current user
    about_me = my_client.get_myself().extract_json().get();

    // Print the name of each of the user's uploaded datapacks
    if (about_me["datapacks"].size()>0) cout<<"Your uploaded datapacks are the following:"<<endl;
    for (int i=0; i<about_me["datapacks"].size(); i++)
        {
        datapack = my_client.get_datapack(about_me["datapacks"][i].as_string()).extract_json().get();
        cout<<" - "<<datapack["name"].as_string()<<endl;
    }

    // Upload a new datapack structure
    response = my_client.upload_datapack(read_JSON("../test_datapack.json")).extract_json().get();
    string_t datapack_id;

    if (response.has_field("error")){
        cout<<"HTTP error "<< response["error_code"].as_integer() << " uploading datapack:\n";
        string error = response["error"].as_string();
        cout<<error<<endl;
        datapack_id = error.substr(error.size()-36);
    }
    else {
        cout<<"Datapack uploaded OK"<<endl;
        datapack_id = response["item"]["id"].as_string();
    }

    // Upload the files referenced inside a datapack
    my_client.upload_datapack_files(datapack_id);

    return 0;
}



