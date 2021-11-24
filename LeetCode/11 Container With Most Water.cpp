//
// https://leetcode.com/problems/container-with-most-water/
//

#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(const vector<int>& height) {
        const int* hl = &height[0];
        const int* hr = &height[height.size() - 1];
        int S_max = 0;

        while (hl < hr) {
            const auto hlv = *hl;
            const auto hrv = *hr;
            
            //cout << "L[" << distance(&height[0], hl) << "]:" << hlv << "   " << "R[" << distance(&height[0], hr) << "]:" << hrv << endl;

            S_max = max(S_max, (int)distance(hl, hr) * min(hlv, hrv));
            
            if (hlv <= hrv) {
                while (++hl < hr && *hl <= hlv) {}
            }
            
            if (hrv <= hlv) {
                while (--hr > hl && *hr <= hrv) {}
            }
        }
        
        return S_max;
    }
};
