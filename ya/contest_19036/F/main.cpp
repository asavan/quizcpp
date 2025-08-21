#include <curl/curl.h>  
#include "json.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

class Scraper {
public:
    Scraper() {
        curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("curl error");
        }
    }
    ~Scraper() {
        curl_easy_cleanup(curl);
        curl = NULL;
    }
    std::string request(const std::string& url) {
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_perform(curl);
        return response_string;
    }

private:
    static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
        data->append((char*)ptr, size * nmemb);
        return size * nmemb;
    }
    CURL* curl;
};

int main(int argc, char** argv) {
    Scraper s;
    std::string url;
    int port, a, b;
    std::cin >> url;
    std::cin >> port;
    std::cin >> a;
    std::cin >> b;

    std::string request = url + ":" + std::to_string(port) + "?a=" + std::to_string(a) + "&b=" + std::to_string(b);
    std::string response_string = s.request(request);
    auto resp_json = nlohmann::json::parse(response_string);
    std::vector<int32_t> res;
    for (const auto& o : resp_json) {
        res.push_back(o.get<int32_t>());
    }
    long long result = std::accumulate(res.begin(), res.end(), 0L);
    std::cout << result << std::endl;
    return 0;
}
