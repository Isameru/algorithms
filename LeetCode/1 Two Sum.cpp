//
// https://leetcode.com/problems/two-sum/
//

class Solution
{
    struct IndexedNum
    {
        int num;
        int index;
    };
    
    vector<IndexedNum> makeIndexedNums(const vector<int>& nums)
    {
        auto indexed_nums = vector<IndexedNum>{};
        indexed_nums.reserve(nums.size());
        
        const auto nums_size = (int)nums.size();
        
        for (int num_index = 0; num_index < nums_size; ++num_index) {
            indexed_nums.push_back(IndexedNum{nums[num_index], num_index});
        }
        
        return indexed_nums;
    }
    
    void sortIndexedNums(vector<IndexedNum>& indexed_nums)
    {
        sort(begin(indexed_nums), end(indexed_nums), [](auto a, auto b) {
            return a.num < b.num;
        });
    }
    
    vector<int> solveUsingSorting(const vector<int>& nums, int target)
    {
        auto indexed_nums = makeIndexedNums(nums);
        sortIndexedNums(indexed_nums);
        
        int index_low   = 0;
        int index_high  = (int)nums.size() - 1;

        while (index_low < index_high)
        {
            auto current_sum = indexed_nums[index_low].num + indexed_nums[index_high].num;
            
            if (current_sum == target) {
                // The solution has been found.
                return {indexed_nums[index_low].index, indexed_nums[index_high].index};
            }
            else if (current_sum < target) {
                ++index_low;
            }
            else {
                --index_high;
            }
        }

        throw runtime_error{"There is no solution to the specified input data."};
    }

    vector<int> solveBrutally(const vector<int>& nums, int target)
    {
        const auto nums_size = (int)nums.size();
        
        for (int i1 = 0; i1 < nums_size; ++i1) {
            for (int i2 = i1 + 1; i2 < nums_size; ++i2) {
                if (nums[i1] + nums[i2] == target) {
                    return {i1, i2};
                }
            }
        }

        throw runtime_error{"There is no solution to the specified input data."};
    }
    
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        if (nums.size() <= 32)
            return solveBrutally(nums, target);
        else
            return solveUsingSorting(nums, target);
    }
};
