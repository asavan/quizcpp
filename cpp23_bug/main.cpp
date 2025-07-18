// https://habr.com/ru/companies/yandex/articles/920470/

#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <iterator>

int main() {
    std::vector<std::string> coll1{"Amsterdam", "Berlin", "Cologne", "LA"};
    // Перемещаем длинные строки в обратном порядке в другой контейнер
    auto large = [](const auto& s) { return s.size() > 5; };
    
    auto sub = coll1 | std::views::filter(large)
                   | std::views::reverse
                   | std::views::as_rvalue
                   | std::ranges::to<std::vector>();
                   
    for (const auto& s : sub) {
        std::cout << s << " ";
    }
    return 0;
}
