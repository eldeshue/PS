class Solution {
public:
    bool checkPowersOfThree(int n) {
        int i = 1;
        while (i <= n)
            i *= 3;
        i /= 3;

        while (i > 0)
        {
            if (n >= i)
            {
                n -= i;
                if (n >= i)
                    return false;
            }
            i /= 3;
        }
        return true;
    }
};
