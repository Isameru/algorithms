//
// https://leetcode.com/problems/integer-to-roman/
//

#include <string_view>

using namespace std;

static const string_view decimal_to_roman_enc[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM", "?" , "?", "?" , "?"  , "?"   , "?" }
};

template<int base, int base_log10>
int convert_decimal(string& enc_to_append, int num) {
    if (num < base) return num;
    const int q = num / base;
    enc_to_append.append(decimal_to_roman_enc[base_log10][q]);
    return num - q * base;
}

void convert_decimal_e0(string& enc_to_append, int num) {
    enc_to_append.append(decimal_to_roman_enc[0][num]);
}

class Solution {
public:
    string intToRoman(int num) {
        string num_enc_roman;

        num = convert_decimal<1000, 3>(num_enc_roman, num);
        num = convert_decimal<100, 2>(num_enc_roman, num);
        num = convert_decimal<10, 1>(num_enc_roman, num);
        convert_decimal_e0(num_enc_roman, num);
        
        return num_enc_roman;
    }
};
