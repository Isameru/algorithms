# LeetCode: 9. Palindrome Number

https://leetcode.com/problems/palindrome-number/

The input is an integer number.
As the natural representation of an `int` is not deciamal, but binary, we cannot directly access its digits to check for the palindrome pattern.
We can `mod 10` the number to extract its least significant digit.

```cpp
x = 12321;
while (x > 0) {
    cout << (x % 10) << endl;
    x /= 10;
}

/* out:
1
2
3
2
1
*/
```

The main idea behind this problem is to extract each least significant decimal digit one by one and build the second number from these digits in reverse order:

| Iteration | x     | y     |
|-----------|-------|-------|
| 0         | 12321 | 0     |
| 1         | 1232  | 1     |
| 2         | 123   | 12    |
| 3         | 12    | 123   |
| 4         | 1     | 1232  |
| 5         | 0     | 12321 |

As you can see, `x` after iteration 3 is the same as `y` after iteration 2.

Another example:

| Iteration | x     | y     |
|-----------|-------|-------|
| 0         | 1221  | 0     |
| 1         | 122   | 1     |
| 2         | 12    | 12    |
| 3         | 1     | 122   |
| 4         | 0     | 1221  |

As this palindrome has symmetry point between the central pair of digits (22), this time after iteration 2 both `x` and `y` has the same value.

We can use these conditions to write an effective algorithm solving the problem, yet it does not work for one-digit numbers as well for numbers ending with decimal digit 0.

Also, all negative numbers are not palindromes in their decimal representation.

Here is the complete code:

```cpp
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
```
