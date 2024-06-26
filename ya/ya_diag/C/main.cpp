#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

#include "json.hpp"

struct Offer {
    std::string offer_id;
    int32_t market_sku;
    int32_t price;
};

int main()
{
    int n;
    std::cin >> n;
    std::string line;
    std::getline(std::cin, line);
    std::vector<Offer> offer_vec;
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        auto offer_json = nlohmann::json::parse(line);
        for (const auto& o : offer_json["offers"]) {
            Offer offer{o["offer_id"].get<std::string>(), o["market_sku"].get<int32_t>(),
                        o["price"].get<int32_t>()};
            offer_vec.push_back(offer);
        }
    }
    std::sort(offer_vec.begin(), offer_vec.end(), [](const Offer& lhs, const Offer& rhs) {
        return std::tie(lhs.price, lhs.offer_id) < std::tie(rhs.price, rhs.offer_id);
    });
    nlohmann::json output_json;
    for (auto x : offer_vec) {
        nlohmann::json elem;
        elem["offer_id"] = x.offer_id;
        elem["market_sku"] = x.market_sku;
        elem["price"] = x.price;
        output_json["offers"].push_back(elem);
    }
    std::cout << output_json.dump() << std::endl;
    return 0;
}
