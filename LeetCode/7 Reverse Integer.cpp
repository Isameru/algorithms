//
// https://leetcode.com/problems/reverse-integer/
//

class Solution
{
    constexpr static int max_int = numeric_limits<int>::max();
    constexpr static int max_int_div10 = max_int / 10;

public:
    static bool safeM10A(int& y, int x)
    {
        if (y > max_int_div10)
            return false;
        
        y *= 10;
        
        if (x > max_int - y)
            return false;
        
        y += x;
        return true;
    }
    
    int reverse(int x)
    {
        int y = 0;
        
        bool negate = false;
        
        if (x < 0) {
            if (x < -max_int)
                return 0;
            
            x = -x;
            negate = true;
        }
        
        while (x > 0)
        {
            if (!safeM10A(y, x % 10))
                return 0;
            x /= 10;
        }
        
        if (negate) {
            if (y == max_int)
                return 0;
            return -y;
        }
        else {
            return y;
        }
    }
};
