//
// https://leetcode.com/problems/roman-to-integer/
//

int roman_digit_to_int(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

class Solution {
public:
    int romanToInt(string s) {
        int num = 0;
        int d_prev = numeric_limits<int>::max();
        for (const char c : s) {
            const int d = roman_digit_to_int(c);
            num += d;
            if (d > d_prev) {
                num -= 2 * d_prev;
            }
            d_prev = d;
        }
        return num;
    }
};
