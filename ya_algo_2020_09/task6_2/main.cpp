// problems/F/
// syzygymsu solution https://github.com/syzygymsu/quizcpp/blob/master/ya_algo_2020_09/task6_2/main.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <utility>

#include <assert.h>


// using namespace std;

void print(const std::vector<int>& row) {
    std::cout << "[";
    for (int v : row) {
        std::cout << v << " ";
    }
    std::cout << "]" << std::endl;
}

void print(const std::vector<std::vector<int>>& rows) {
    std::cout << "[";
    for (const auto& row : rows) {
        print(row);
    }
    std::cout << "]" << std::endl;
}

int func_good(std::istream& f, std::ostream& out) {
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> rows(m, { n + 1 });
    std::vector<int> cols(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int x, y;
        f >> x;
        f >> y;
        int temp = n - 1 - x;
        rows[y].push_back(temp);
        ++cols[temp];
    }
    int fisrtNonZeroCol = 0;
    for (auto& row : rows) {
        std::sort(row.begin(), row.end(), std::greater<int>());
    }

    bool color = rows[0].back() == 0;
    int full_rows = 0;
    std::vector<int> positions(m + 1, 0);
    positions[0] = n + 1;
    int iteration = 0;
    int iterCount = 0;
    while (full_rows < m) {
        for (int i = fisrtNonZeroCol; i < n; ++i) {
            if (cols[i] > 0) {
                fisrtNonZeroCol = i;
                break;
                // ++iterCount;
            }
        }
        int localNonZero = cols[fisrtNonZeroCol];
        for (int j = full_rows; j < m; ++j) {
            auto& row = rows[j];
            if (color) {
                while (std::max(positions[j + 1], fisrtNonZeroCol) == row.back() && row.back() < positions[j]) {
                    positions[j + 1] = row.back() + 1;
                    --cols[row.back()];
                    if (row.back() == fisrtNonZeroCol) {
                        --localNonZero;
                    }
                    // cout << "in color " << iterCount << endl;
                    row.pop_back();
                    ++iterCount;
                }
                ++iterCount;
                if (localNonZero == 0) {
                    break;
                }
                // cout << "skip color " << iterCount << endl;
            }
            else {
                ++iterCount;
                if (row.back() > positions[j]) {
                    // std::cout << "more " << iterCount << " " << " localNonZero " << localNonZero << " " << fisrtNonZeroCol << std::endl;
                    positions[j + 1] = positions[j];
                }
                else {
                    if (row.back() > fisrtNonZeroCol) {
                        // std::cout << "less1 " << iterCount <<" " << localNonZero << std::endl;

                        positions[j + 1] = row.back();
                    }
                    else if (row.back() == fisrtNonZeroCol) {
                        // std::cout << "less2 " << iterCount  << " " << localNonZero <<std::endl;

                        --localNonZero;
                        if (localNonZero == 0) {
                            positions[j + 1] = fisrtNonZeroCol;
                            break;
                        }
                        positions[j + 1] = fisrtNonZeroCol;
                    }
                }
            }
            if (positions[j + 1] == n + 1) {
                full_rows = j + 1;
            }
            else if (positions[j + 1] == fisrtNonZeroCol) {
                break;
            }
        }

        color = !color;
        ++iteration;
    }
    if (color) {
        --iteration;
    }
    // std::cout << "iterCount " << iterCount << " iteration " << iteration << std::endl;
    // out << iteration << std::endl;
    return iteration;
}


int func(std::istream& f, std::ostream& out) {
    // ==== Loading ====
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return 0;
    }
    // std::cout << n << " " << m << " " << k << std::endl;
    std::vector< std::vector<int> > cols(n);
    for (int i = 0; i < k; ++i) {
        int x, y;
        f >> x;
        f >> y;
        cols.at(x).push_back(y);
    }
    for (auto& col : cols) {
        std::sort(col.begin(), col.end());
    }

    // ==== Init ====
    using Segment = std::pair<int, int>;
    std::vector<Segment> segments(k, Segment{0,0});
    std::unordered_set<Segment*> unclosed; // segments to be closed
    auto find_segment = [&](int target) {
        Segment seg{target + 1, target + 1};
        auto pp = std::lower_bound(segments.begin(), segments.end(), seg);
        assert(pp != segments.begin());
        --pp;
        return pp;
    };

    // ==== Process ====
    for (auto& col :cols) {
        std::unordered_set<Segment*> unclosed_next;
        for (int point_idx = col.size() - 1; point_idx >= 0; --point_idx) {
            int top_y = col[point_idx];
            auto s = find_segment(top_y);

            // merge consequent points
            int bottom_y = top_y;
            while (point_idx > 0 
                    && col[point_idx-1] >= s->first
                    && col[point_idx-1] == bottom_y-1) {
                --point_idx;
                bottom_y = col[point_idx];
            }

            s->first = bottom_y;
            s->second = top_y + 1;
            unclosed.erase(&*s);
            unclosed_next.insert(&*s);
        }

        // close unclosed segments
        for(Segment* s : unclosed) {
            s->first = s->second;
        }
        unclosed = std::move(unclosed_next);
    }

    int res = 0;
    for (Segment& s : segments) {
        if (s.first) ++res;
        if (s.second) ++res;
    }
    out << res << std::endl;
    return res;
}


#include <chrono> 

void test(const std::string& filename, int expected) {
    std::ifstream f(filename);
    // std::ofstream out("output.txt");
    auto start = std::chrono::high_resolution_clock::now();

    int res = func(f, std::cout);
    auto finish = std::chrono::high_resolution_clock::now();
    if (res != expected) {
        std::cout << "!!!!ERROR in test " + filename << " " << res << " expected " << expected << std::endl;
    }
    else {
        std::cout << filename << " OK " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    }
}

int main() {

    test("input1.txt", 1);
    test("input1dot.txt", 2);
    test("input1dot2.txt", 1);
    test("input2.txt", 2);
    test("input3.txt", 3);
    test("input30x30.txt", 57);
    test("input30x30p.txt", 57);
    test("input30.txt", 56);
    test("input10.txt", 19);
    test("inputdotslongdots.txt", 11);
    test("inputdots.txt", 10);
    test("inputdots2.txt", 10);
    test("input10kx10k.txt", 19997);
    test("input100kx100k.txt", 199997);
    test("input250kx250k.txt", 499997);
    return 0;
}
