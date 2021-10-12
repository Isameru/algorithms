//
// https://leetcode.com/problems/add-strings/
//

class Solution
{
public:
    string addStrings(string num1, string num2)
    {
        int num1_len = (int)num1.size();
        int num2_len = (int)num2.size();
        
        if (num1_len < num2_len) {
            swap(num1, num2);
            swap(num1_len, num2_len);
        }

        int sum = 0;
        
        for (int i = 0; i < num1_len; ++i)
        {
            sum += num1[num1_len - 1 - i] - '0';

            if (i < num2_len) {
                sum += num2[num2_len - 1 - i] - '0';
            }
            
            num1[num1_len - 1 - i] = '0' + sum % 10;
            
            sum /= 10;
        }
        
        if (sum > 0) {
            num1.insert(begin(num1), '0' + sum);
        }
        
        return num1;
    }
};
