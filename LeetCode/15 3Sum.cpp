//
// https://leetcode.com/problems/3sum/
//

class Solution {
private:
    template<int step>
    bool advance(int& i, int end, vector<int>& nums) {
        while (true) {
            i += step;
            if (i == end) {
                return true;
            }
            if (nums[i] != nums[i-step]) {
                return false;
            }
        }
    }

public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};

        vector<vector<int>> out;
        out.reserve(32);

        sort(begin(nums), end(nums));
        int num_count = (int)nums.size();

        int n_prev = nums[0];
        char n_count = 1;
        int oi = 1;
        int i = 1;

        while (true) {
            const int n = nums[i];
            if (n == n_prev) {
                ++n_count;
                if (n_count <= 2 || (n == 0 && n_count <= 3)) {
                    if (oi != i) {
                        nums[oi] = nums[i];
                    }
                    ++oi;
                }
            }
            else {
                n_count = 1;
                if (oi != i) {
                    nums[oi] = nums[i];
                }
                ++oi;
            }
            if (++i == num_count) break;
            n_prev = n;
        }
        num_count = oi;
        nums.resize(num_count);

        if (num_count < 3) return {};

        int a = 0;
        while (true) {
            const int n_a = nums[a];
            int b = a + 1;

            if (n_a + nums[b] > 0) {
                break;
            }

            int c;
            auto c_iter = lower_bound(begin(nums) + b + 1, end(nums), -(n_a + nums[b]));
            if (c_iter == end(nums)) {
                c = num_count - 1;

                auto b_iter = lower_bound(begin(nums) + b, end(nums), -(n_a + nums[c]));
                b = distance(begin(nums), b_iter);
            }
            else {
                c = distance(begin(nums), c_iter);
            }

            if (b < c) {
                while (true) {
                    const int n_b = nums[b];
                    const int n_c = nums[c];

                    const int sum = n_a + n_b + n_c;
                    if (sum == 0) {
                        out.push_back({n_a, n_b, n_c});
                        if (advance<+1>(b, c, nums)) break;
                        if (advance<-1>(c, b, nums)) break;
                    }
                    else if (sum > 0) {
                        if (advance<-1>(c, b, nums)) break;
                    }
                    else {
                        // sum < 0
                        if (advance<+1>(b, c, nums)) break;
                    }
                }
            }

            if (advance<+1>(a, num_count - 2, nums)) break;
        }

        return out;
    }
};
