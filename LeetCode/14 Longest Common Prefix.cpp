//
// https://leetcode.com/problems/longest-common-prefix/
//

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        string lcp = strs[0];
        if (strs.size() == 1) return lcp;
        for (int i = 1; i < (int)strs.size(); ++i) {
            const string& str_i = strs[i];
            int j = 0;
            do  {
                if (str_i[j] == '\0' || str_i[j] != lcp[j]) {
                    break;
                }
            } while(++j < (int)lcp.size());

            if (j == 0) return "";
            lcp.resize(j);
        }
        return lcp;
    }
};
