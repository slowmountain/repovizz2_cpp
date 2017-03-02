//
// Created by Panos Papiotis on 16/02/17.
//

#include "repovizz2_client.h"

repovizz2_client::repovizz2_client(utility::string_t client_id, utility::string_t client_secret, utility::string_t redirect_uri = U("localhost:50009")) :
        oauth2_session(U("repovizz2"),
        U("http://localhost:8080/"),
        client_id,
        client_secret,
        U("http://localhost:8080/oauth/authorize"),
        U("http://localhost:8080/oauth/token"),
        redirect_uri)
        {
            m_oauth2_config.set_scope(U("basic"));
        }

http_response repovizz2_client::get(utility::string_t query)
{
    return api.request(methods::GET, query).get();
}

http_response repovizz2_client::get_myself()
{
    return get(U("/api/v1.0/user"));
}

http_response repovizz2_client::get_datapack(utility::string_t datapack_id)
{
    return get(U("/api/v1.0/datapacks/")+datapack_id);
}

http_response repovizz2_client::upload_datapack(json::value datapack_structure)
{
    json::value datapack_json;
    datapack_json[U("structure")] = datapack_structure;
    datapack_json[U("name")] = datapack_structure["info"]["name"];
    datapack_json[U("owner")] = get(U("/api/v1.0/user")).extract_json().get()[U("id")];

    http_response response = api.request(methods::POST, U("/api/v1.0/datapacks"), datapack_json.serialize(), U("application/json")).get();

    return response;
}

void repovizz2_client::upload_datapack_files(utility::string_t datapack_id)
{
    // Get the datapack JSON structure
    json::value datapack_json = get_datapack(datapack_id).extract_json().get()["structure"]["children"];

    if (datapack_json.has_field("error")){
        ucout << datapack_json.serialize();
    }
    else{
        // Loop over each element inside the datapack.
        std::vector<string_t> file_links = search_datapack(datapack_json, "link");
        for (int i=0;i<file_links.size();i++)
        {
            std::cout<<"../" + file_links[i]<<std::endl;
            upload_file(datapack_id, file_links[i], "../" + file_links[i]);
        }
    }
}

http_response repovizz2_client::upload_file(utility::string_t datapack_id, utility::string_t file_id, utility::string_t file_path) {

    std::cout << "Uploading file " << file_id << " to datapack " << datapack_id << " ...\n" ;
    basic_istream<uint8_t> fileStream = file_stream<uint8_t>::open_istream(file_path).get();
    // We have to go through this hassle because CPPRESTSDK doesn't support multipart/form-data out of the box
    // Kudos to http://stackoverflow.com/questions/27718955/sending-a-http-post-request-for-updating-file-contents-using-c-rest-sdk-casabl
    concurrency::streams::stringstreambuf streamBuffer;
    fileStream.read_to_end(streamBuffer).get();
    std::string textFile = move(streamBuffer.collection());
    fileStream.close();
    streamBuffer.close();
    std::string textBoundary = "--FORMBOUNDARY--";
    std::string textBody = "";
    textBody += "--" + textBoundary + "\r\n";
    textBody += "Content-Disposition:form-data;name=";
    textBody += file_id;
    textBody += ";filename=";
    textBody += file_path;
    textBody += "\r\n";
    textBody += "Content-Type: application/octet-stream\r\n\r\n";
    textBody +=textFile+"\r\n";
    textBody += "--" + textBoundary + "--\r\n";
    http_request req;
    req.set_method(methods::POST);
    req.headers().set_content_type("multipart/form-data;boundary=--FORMBOUNDARY--");
    req.headers().set_content_length(textBody.length());
    req.set_body(textBody);
    req.set_request_uri(U("/api/v1.0/datapacks/") + datapack_id + U("/content/") + file_id);
    http_response response = api.request(req).get();

    // Perform actions here to inspect the HTTP response…
    //if(response.status_code() == status_codes::OK)
    auto body = response.extract_string();
    std::wcout << body.get().c_str();

    return response;
}

//
// Reads a JSON file from disk and returns it as a json::value
//
json::value read_JSON(string_t path) {
    std::ifstream in(path);
    stringstream_t buffer;
    buffer << in.rdbuf();
    in.close();
    return json::value::parse(buffer);
}

//
// Recursively searches a datapack structure and returns a vector with copies of the nodes whose types matches a string
//
std::vector<string_t> search_datapack(json::value root_node, string_t key_type){
    std::vector<string_t> occurences;

    if (root_node.is_object()) {
        for (auto iter = root_node.as_object().cbegin(); iter != root_node.as_object().cend(); ++iter) {
            const utility::string_t &key = iter->first;
            const json::value &val = iter->second;

            if (key == U("children")) {
                std::vector<string_t> sub_occurences;
                sub_occurences = search_datapack(val, key_type);
                for (int i = 0; i < sub_occurences.size(); i++) {
                    occurences.push_back(sub_occurences[i]);
                }
            } else if (key == key_type) {
                occurences.push_back(val.as_string());
            }
        }
    }
    else if (root_node.is_array()) {
        for (int i=0;i<root_node.size();i++) {
            if (root_node[i].has_field(key_type)) {
                occurences.push_back(root_node[i][key_type].as_string());
            }
            else {
                std::vector<string_t> sub_occurences;
                sub_occurences = search_datapack(root_node[i], key_type);
                for (int i = 0; i < sub_occurences.size(); i++) {
                    occurences.push_back(sub_occurences[i]);
                }
            }
        }
    }

    return occurences;
}

//TODO: test POST requests