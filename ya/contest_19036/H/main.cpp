#include "httplib.h"
#include "json.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::string> PHONE_CODES = {"982", "986", "912", "934"};

bool is_code_allowed(const std::string& code) {
    for (auto c : PHONE_CODES) {
        if (c == code) {
            return true;
        }
    }
    return false;
}

std::vector<std::regex> REGEXPS = {
    std::regex("^\\+7 (\\d{3}) (\\d{3}) (\\d{2})(\\d{2})$"),
    std::regex("^\\+7 (\\d{3}) (\\d{3}) (\\d{2}) (\\d{2})$"),
    std::regex("^\\+7 \\((\\d{3})\\) (\\d{3})-(\\d{2})(\\d{2})$"),
    std::regex("^\\+7(\\d{3})(\\d{3})(\\d{2})(\\d{2})$"),
    std::regex("^8 (\\d{3}) (\\d{3}) (\\d{2})(\\d{2})$"),
    std::regex("'^8 (\\d{3}) (\\d{3}) (\\d{2}) (\\d{2})$"),
    std::regex("^8 \\((\\d{3})\\) (\\d{3})-(\\d{2})(\\d{2})$"),
    std::regex("^8(\\d{3})(\\d{3})(\\d{2})(\\d{2})$")
};

std::string parse_phone(const std::string& text) {
    for (auto re : REGEXPS) {
        std::smatch matches;
        if (std::regex_search(text, matches, re)) {
            auto code = matches[1].str();
            if (!is_code_allowed(code)) {
                return "";
            }
            return "+7-" + code + "-" + matches[2].str() + "-" + matches[3].str() + matches[4].str();
        }
    }
    return "";
}

int main1() {
    std::cout << parse_phone("89820000000") << std::endl;
}

int main(int argc, char** argv) {
    // using namespace httplib;
    httplib::Server svr;

    svr.Get("/ping", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("pong", "text/plain");
    });

    svr.Get("/shutdown", [&](const httplib::Request& req, httplib::Response& res) {
        svr.stop();
    });

    svr.Get("/validatePhoneNumber", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("phone_number")) {
            std::string phone_number_str = req.get_param_value("phone_number");
            std::string normalized = parse_phone(phone_number_str);
            nlohmann::json j;
            if (normalized.empty()) {
                j["status"] = false;
            } else {
                j["status"] = true;
                j["normalized"] = normalized;
            }
            res.set_content(j.dump(), "application/json");
        } else {
            res.status = 400;
        }
    });

    svr.listen("127.0.0.1", 7777);
    return 0;
}
