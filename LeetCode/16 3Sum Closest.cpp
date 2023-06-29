//
// https://leetcode.com/problems/3sum-closest/
//

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        const int nums_size = (int)nums.size();

        if (nums_size == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        sort(begin(nums), end(nums));

        int best_sum = accumulate(begin(nums), begin(nums) + 3, 0);

        if (nums_size == 3 || best_sum >= target) {
            return best_sum;
        }

        auto propose_sum = [&best_sum, target](int sum) {
            if (abs(sum - target) < abs(best_sum - target)) {
                best_sum = sum;
            }
            return best_sum == target;
        };

        auto advance_index = [&nums, nums_size](int& i) {
            const int vi0 = nums[i];
            do {
                ++i;
            }
            while (i < nums_size && nums[i] == vi0);
        };

        auto retreat_index = [&nums, nums_size](int& i) {
            assert(i > 0);
            --i;
            const int vi = nums[i];
            while (i > 0 && nums[i-1] == nums[i]) {
                --i;
            }
        };

        int exp_v2 = target - nums[0] - nums[1];
        int i2 = distance(begin(nums), lower_bound(begin(nums) + 2, end(nums), exp_v2));
        i2 = min(i2, nums_size - 1);
        if (propose_sum(nums[0] + nums[1] + nums[i2])) {
            cout << "lowest sum: " << best_sum << endl;
            return best_sum;
        }

        int exp_v0 = target - nums[i2-1] - nums[i2];
        int i0 = distance(begin(nums), lower_bound(begin(nums), begin(nums) + i2 - 1, exp_v0));
        if (i0 > i2 - 2) {
            return nums[i2-2] + nums[i2-1] + nums[i2];
        }

        if (nums[i0] == exp_v0) {
            return nums[i0] + nums[i2-1] + nums[i2];
        }
        else if (i0 > 0) {
            retreat_index(i0);
        }

        while (true) {
            if (i0 + 2 > i2) {
                break;
            }
            if (i0 + 2 == i2) {
                propose_sum(nums[i0] + nums[i0+1] + nums[i2]);
                break;
            }

            int j1 = i0 + 1;
            int j2 = i2;
            bool j1_moved = false;

            while (j2 > j1) {
                int curr_sum = nums[i0] + nums[j1] + nums[j2];
                if (propose_sum(curr_sum))
                    return best_sum;

                if (curr_sum > target) {
                    --j2;
                    if (!j1_moved) {
                        --i2;
                    }
                }
                else {
                    assert(curr_sum < target);
                    ++j1;
                    j1_moved = true;
                }
            }

            advance_index(i0);
        }

        return best_sum;
    }
};
