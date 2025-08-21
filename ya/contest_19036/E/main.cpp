// problems/E/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <queue>
#include <memory>

class Clusters {
public:
    Clusters(const std::unordered_map<int, std::unordered_set<int>>& g) {
        for (const auto& pair : g) {
            int n = pair.first;
            auto it = map.find(n);
            if (it == map.end()) {
                auto c = cluster(g, n);
                for (int subling : *c) {
                    map[subling] = c;
                }
            }
        }
    }
    
    bool sameClusters(int x, int y) const {
        auto it = map.find(x);
        if (it == map.end()) {
            // std::cerr << "NOT IN MAP" << std::endl;
            return false;
        }
        auto it2 = it->second->find(y);
        if (it2 == it->second->end()) {
            // std::cerr << "DIFF CLUSTERS" << std::endl;
            return false;
        }
        // std::cerr << "SAME CLUSTER" << std::endl;
        return true;
    }
private:
            std::shared_ptr<std::unordered_set<int>> cluster(
                const std::unordered_map<int, std::unordered_set<int>>& graph, int root) {
            auto visited = std::make_shared<std::unordered_set<int>>();
            std::queue<int> queue;
            queue.push(root);
            visited->insert(root);
            while (!queue.empty()) {
                int x = queue.front();
                queue.pop();
                auto it = graph.find(x);
                if (it == graph.end()) {
                    // std::cerr << "WHATT" << std::endl;
                    continue;
                }
                for (int y : it->second) {
                    if (visited->find(y) == visited->end()) {
                        queue.push(y);
                        visited->insert(y);
                    }
                }
            }
            // std::cerr << "size " << visited->size() << std::endl;
            return visited;
        }
    std::unordered_map<int, std::shared_ptr<std::unordered_set<int>>> map;
};

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

std::vector<int> readVec(int n) {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = readInt();
    }
    return a;
}

void print(const std::vector<int>& vec) {
    std::cout << vec.size();
    for (int v : vec) {
        std::cout << " " << v;
    }
    std::cout << std::endl;
}

std::unordered_map<int, std::unordered_set<int>> readGraph(int n) {
    std::unordered_map<int, std::unordered_set<int>> g;
    for (int i = 0; i < n; ++i) {
        int a = readInt();
        int b = readInt();
        g[a].insert(b);
        g[b].insert(a);
    }
    return g;
}

std::vector<int> request(const Clusters& c) {
    int x = readInt();
    int k = readInt();
    auto req = readVec(k);
    std::vector<int> res;
    for (int r: req) {
        if (c.sameClusters(x, r)) {
            res.push_back(r);
        }
    }
    return res;
}

void solve() {
    int n = readInt();
    auto g = readGraph(n);
    int q = readInt();
    Clusters c(g);
    for (int i = 0; i < q; ++i) {
        print(request(c));
    }
}

int main() {
    solve();
    return 0;
}
