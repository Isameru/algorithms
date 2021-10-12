//
// https://leetcode.com/problems/string-to-integer-atoi/
//

class Solution
{
    constexpr static int int_max = numeric_limits<int>::max();
    constexpr static int int_max_div10 = int_max / 10;
    constexpr static int int_min = numeric_limits<int>::min();
    constexpr static int int_min_div10 = int_min / 10;

public:
    int myAtoi(string str) {
        const int s_len = (int)str.size();
        int i = 0;
        
        if (s_len == 0)
            return 0;
        
        while (str[i] == ' ') {
            if (++i == s_len)
                return 0;
        }
        
        bool positive = true;
        
        if (str[i] == '-') {
            positive = false;
            if (++i == s_len)
                return 0;
        }
        else if (str[i] == '+') {
            if (++i == s_len)
                return 0;
        }

        int i0 = i;
        int s_len_fast = i0 + 9;
        
        int x = 0;

        if (positive)
        {
            for (; i < s_len_fast; ++i)
            {
                const char c = str[i];

                if (c < '0' || c > '9')
                    return x;

                x = 10 * x + (c - '0');
            }
            
            for (; i < s_len; ++i)
            {
                const char c = str[i];

                if (c < '0' || c > '9')
                    return x;

                if (x > int_max_div10)
                    return int_max;
                
                x *= 10;

                int y = c - '0';

                if (int_max - x < y)
                    return int_max;
                
                x += y;
            }
        }
        else
        {
            for (; i < s_len_fast; ++i)
            {
                const char c = str[i];

                if (c < '0' || c > '9')
                    return x;

                x = 10 * x - (c - '0');
            }
            
            for (; i < s_len; ++i)
            {
                const char c = str[i];

                if (c < '0' || c > '9')
                    return x;

                if (x < int_min_div10)
                    return int_min;
                
                x *= 10;

                int y = c - '0';

                if (x + int_max < y)
                    return int_min;
                
                x -= y;
            }
        }

        return x;
    }
};
