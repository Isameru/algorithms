//
// https://leetcode.com/problems/longest-palindromic-substring/
//

constexpr bool VERBOSE = false;

class Solution {
public:
    string longestPalindrome(string s)
    {
        const int s_size = (int)s.size();

        constexpr int max_pivots = 2000;
        int pivots[max_pivots];
        int pivot_s = 0;
        int pivot_e = 0;

        int best_s = 0;
        int best_len = 0;

        for (int i = 0; i <= s_size; ++i)
        {
            if (VERBOSE) {
                if (i == s_size) {
                    cout << "after" << endl;
                }
                else {
                    cout << s[i] << endl;
                }
            }

            const int pivot_e_copy = pivot_e;
            for (int j = pivot_s; j != pivot_e_copy; j = (j + 1) % max_pivots)
            {
                const int k = pivots[j] - i;

                if (VERBOSE) {
                    cout << "  Checking counter-char : " << k << endl;
                }
                
                if (k < 0 || i == s_size || s[i] != s[k]) {
                    int len = i - k - 1;

                    if (VERBOSE) {
                        cout << "    Breaking palindrome : " << s.substr(k + 1, len) << endl;
                    }

                    if (len > best_len) {
                        best_s = k + 1;
                        best_len = len;

                        if (VERBOSE) {
                            cout << "    New best : " << s.substr(best_s, best_len) << endl;
                        }
                    }
                }
                else {
                    pivots[pivot_e] = pivots[pivot_s];

                    pivot_e = (pivot_e + 1) % max_pivots;
                }

                pivot_s = (pivot_s + 1) % max_pivots;
            }

            pivots[pivot_e] = 2 * i;
            pivot_e = (pivot_e + 1) % max_pivots;
            pivots[pivot_e] = 2 * i + 1;
            pivot_e = (pivot_e + 1) % max_pivots;
        }

        return s.substr(best_s, best_len);
    }
};
