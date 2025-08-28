#include <algorithm>
#include <cmath>

class Solution {
    int sqr(int x) {
        return x * x;
    }

  public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        auto xNew = x1 + x2;
        auto yNew = y1 + y2;
        auto xCenterNew = abs(2 * xCenter - xNew);
        auto yCenterNew = abs(2 * yCenter - yNew);

        auto cornerX = abs(x1 - x2);
        auto cornerY = abs(y2 - y1);

        auto closestX = std::min(cornerX, xCenterNew);
        auto closestY = std::min(cornerY, yCenterNew);

        auto dist = sqr(closestX - xCenterNew) + sqr(closestY - yCenterNew);
        return dist <= sqr(2 * radius);
    }
};
