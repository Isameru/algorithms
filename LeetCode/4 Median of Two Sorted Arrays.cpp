//
// https://leetcode.com/problems/median-of-two-sorted-arrays/
//

constexpr bool VERBOSE = false;

class Solution {

    struct Range {
        vector<int> nums;
        int lo, hi;
    };

    double brute(vector<int>& nums1, vector<int>& nums2) {
        nums1.reserve(nums1.size() + nums2.size());
        nums1.insert(end(nums1), begin(nums2), end(nums2));
        sort(begin(nums1), end(nums1));
        
        int s = (int)nums1.size();
        if (s % 2 == 0) {
            --s;
            return 0.5 * (nums1[s / 2] + nums1[s / 2 + 1]);
        }
        else {
            return nums1[s / 2];
        }
    }
    
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int median_x2 = (int)nums1.size() + (int)nums2.size() - 1;

        // if (median_x2 < 4) {
        //     return brute(nums1, nums2);
        // }
        
        if (VERBOSE) cout << "median_x2 : " << median_x2 << endl;

        int lo_1 = 0;
        int hi_1 = (int)nums1.size();

        int lo_2 = 0;

        int lo_2b = 0;
        int hi_2b = (int)nums2.size();
        
        if (VERBOSE) cout << "nums1" << endl;

        while (hi_1 - lo_1 > 0) {
            int mid_1 = (lo_1 + hi_1 + 1) / 2;
            
            int mid_1_val = (mid_1 - 1 >= 0) ? nums1[mid_1 - 1] : numeric_limits<int>::min();

            lo_2 = (int)distance(begin(nums2), lower_bound(begin(nums2) + lo_2b, begin(nums2) + hi_2b, mid_1_val));

            if (VERBOSE) cout << "  " << lo_1 << ".." << mid_1 << ".." << hi_1 << " -> " << lo_2 << endl;

            if (2 * (mid_1 + lo_2) <= median_x2) {
                lo_1 = mid_1;
                lo_2b = lo_2;
            }
            else {
                hi_1 = mid_1 - 1;
                hi_2b = min(hi_2b, lo_2);
            }
        }

        if (VERBOSE) cout << "  " << lo_1 << ".." << hi_1 << endl;

        if (VERBOSE) cout << "nums2" << endl;

        lo_2 = median_x2 / 2 - lo_1;
        cout << "  lo_2 : " << lo_2 << endl;

        array<int, 4> pack;
        int pack_size = 0;
        
        if (lo_1 < (int)nums1.size()) {
            pack[pack_size++] = nums1[lo_1];
        }

        if ((lo_1 + 1) < (int) nums1.size()) {
            pack[pack_size++] = nums1[(lo_1 + 1)];
        }

        if (lo_2 < (int)nums2.size()) {
            pack[pack_size++] = nums2[lo_2];
        }

        if ((lo_2 + 1) < (int) nums2.size()) {
            pack[pack_size++] = nums2[(lo_2 + 1)];
        }
        
        sort(begin(pack), begin(pack) + pack_size);
        
        if (VERBOSE) {
            cout << "pack" << endl;
            cout << "  ";
            for (auto v : pack) {
                cout << v << ' ';
            }
            cout << endl;
        }

        int i = median_x2 - 2 * (lo_1 + lo_2);
        if (i % 2 == 0) {
            return pack[i / 2];
        }
        else {
            return 0.5 * (pack[i / 2] + pack[(i / 2) + 1]);
        }
        
        return 0;        
    }
};
