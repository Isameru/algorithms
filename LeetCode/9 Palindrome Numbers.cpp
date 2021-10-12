//
// https://leetcode.com/problems/palindrome-number/
//

class Solution
{
public:
    bool isPalindrome(int x)
    {
       
        if (x < 0)
            return false;
        
        if (x < 10)
            return true;
        
        if (x % 10 == 0)
            return false;

        int y = 0;
        int prev_y;

        while (x > y)
        {
            prev_y = y;            
            y = 10 * y + (x % 10);
            x /= 10;
        }

        if (x == y || x == prev_y)
            return true;

        return false;
    }
};
