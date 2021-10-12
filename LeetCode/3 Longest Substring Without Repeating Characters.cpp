//
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
//

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        bool counts[128] = {};

        int best_length = 0;
        int section_length = 0;
        int section_start = 0;
        
        for (char c : s) {
            while (counts[c]) {
                counts[s[section_start++]] = false;
                --section_length;
            }

            counts[c] = true;
            ++section_length;
            best_length = max(best_length, section_length);
        }
        
        return best_length;
    }
};
