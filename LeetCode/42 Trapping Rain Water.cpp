//
// https://leetcode.com/problems/trapping-rain-water/
//

struct vec2i {
    int x;
    int y;
};

class Solution {
public:
    int trap(vector<int>& height) {
        stack<vec2i> drops{};
        int W = 0;
        
        for (int x = 1; x < (int)height.size(); ++x) {
            auto y_prev = height[x-1];
            const auto y = height[x];
            if (y < y_prev) {
                drops.push(vec2i{x, y_prev});
            }
            else {
                while (y > y_prev && !drops.empty()) {
                    auto& t = drops.top();
                    const auto y2 = min(y, t.y);
                    W += (y2 - y_prev) * (x - t.x);
                    y_prev = t.y;
                    if (y2 == t.y) {
                        drops.pop();
                    }
                }
            }
        }
        
        return W;
    }
};
