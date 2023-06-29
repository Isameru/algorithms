//
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
//

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> out_words;
        visitWords({}, digits, out_words);
        return out_words;
    }

private:
    void visitWords(vector<string> prefixes, string digits, vector<string>& out_words) {
        if (digits.empty())
            return;

        vector<string> digitChars;
        switch (digits[0]) {
            case '2': digitChars = {"a", "b", "c"}; break;
            case '3': digitChars = {"d", "e", "f"}; break;
            case '4': digitChars = {"g", "h", "i"}; break;
            case '5': digitChars = {"j", "k", "l"}; break;
            case '6': digitChars = {"m", "n", "o"}; break;
            case '7': digitChars = {"p", "q", "r", "s"}; break;
            case '8': digitChars = {"t", "u", "v"}; break;
            case '9': digitChars = {"w", "x", "y", "z"}; break;
            default: assert(false);
        }

        out_words.clear();
        if (!prefixes.empty()) {
            for (const string& prefix : prefixes) {
                for (const string& digitChar : digitChars) {
                    out_words.push_back(prefix + digitChar);
                }
            }
        }
        else {
            out_words = move(digitChars);
        }
        
        if (digits.size() > 1) {
            prefixes = move(out_words);
            visitWords(prefixes, digits.substr(1), out_words);
        }
    }
};
