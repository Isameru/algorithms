//
// https://leetcode.com/problems/regular-expression-matching/
//

class Solution {
public:
    bool isMatch(string s, string p) {
        function<bool(int, int)> is_match;
        function<bool(int, int)> is_match_cached;

        int8_t cache[32][32] = {};

        is_match = [&](int si, int pi) {
            if (s[si] == '\0' && p[pi] == '\0') {
                return true;
            }
            else if (s[si] == '\0' && p[pi] != '\0') {
                if (p[pi+1] == '*') {
                    return is_match_cached(si, pi+2);
                }
                else {
                    return false;
                }
            }
            else if (s[si] != '\0' && p[pi] == '\0') {
                return false;
            }
            else {
                if (s[si] == p[pi] || p[pi] == '.') {
                    if (p[pi+1] == '*') {
                        return is_match_cached(si+1, pi) || is_match_cached(si, pi+2);
                    }
                    else {
                        return is_match_cached(si+1, pi+1);
                    }
                }
                else {
                    if (p[pi+1] == '*') {
                        return is_match_cached(si, pi+2);
                    }
                    else {
                        return false;
                    }
                }
            }
        };

        is_match_cached = [&](int si, int pi) {
            auto& cached_value = cache[si][pi];
            if (cached_value) {
                return cached_value > 0;
            }
            else {
                const auto is_match_value = is_match(si, pi);
                cached_value = is_match_value ? 1 : -1;
                return is_match_value;
            }
        };
        
        return is_match(0, 0);
    }
};
