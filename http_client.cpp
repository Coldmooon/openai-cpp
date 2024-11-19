#include "http_client.h"


size_t HttpClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

HttpClient::HttpResponse HttpClient::post_json(
    const std::string& url,
    const std::string& api_key,
    const nlohmann::json& payload,
    bool debug
) {
    CURL* curl = curl_easy_init();
    HttpResponse response;
    std::string response_string;

    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json; charset=utf-8");
    headers = curl_slist_append(headers, "Accept: application/json");
    std::string auth_header = "Authorization: Bearer " + api_key;
    headers = curl_slist_append(headers, auth_header.c_str());

    std::string payload_str = payload.dump();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    if (debug) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
    response.body = response_string;

    // Parse response
    try {
        response.json = nlohmann::json::parse(response.body);
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("Failed to parse API response: " + std::string(e.what()));
    }

    // Check for API errors
    if (response.status_code != 200) {
        std::string error_message = response.json.contains("error") ? 
            response.json["error"]["message"].get<std::string>() : 
            "Unknown API error";
        throw std::runtime_error("API request failed with code " + 
            std::to_string(response.status_code) + ": " + error_message);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return response;
} 