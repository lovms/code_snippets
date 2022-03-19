/*
 * 注意代码实现中两处 基于模数的减法，会存在小于0的情况：(a-b) % m != a%m - b%m，如果a<b，则 (a-b) %m = a+m -b !!! 千万要注意！！！
 */
/*
730. Count Different Palindromic Subsequences
难度
困难

155

收藏

分享
切换为中文
接收动态
反馈
Given a string s, return the number of different non-empty palindromic subsequences in s. Since the answer may be very large, return it modulo 10^9 + 7.

A subsequence of a string is obtained by deleting zero or more characters from the string.

A sequence is palindromic if it is equal to the sequence reversed.

Two sequences a1, a2, ... and b1, b2, ... are different if there is some i for which ai != bi.

 

Example 1:

Input: s = "bccb"
Output: 6
Explanation: The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.
Example 2:

Input: s = "a bcdabcdabcdabcdabcdabcdab cdabcddcbadc badcbadcbadcbadcbadcbadcb a"
Output: 104860361
Explanation: There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.
 

Constraints:

1 <= s.length <= 1000
s[i] is either 'a', 'b', 'c', or 'd'.

*/

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    int countPalindromicSubsequences(string s) {
        vector<int> nextMe(s.size(), 0);
        vector<int> preMe(s.size(), 0);

        vector<int> preCh(4, -1);
        for (int i = 0; i < s.size(); ++i) {
            int ch = s[i] - 'a';
            preMe[i] = preCh[ch];
            if (preCh[ch] != -1) {
                nextMe[preCh[ch]] = i;
            }
            preCh[ch] = i;
        }

        //vector<vector<int> > dp(s.size(), vector<int>(s.size(), -1));
        vector<vector<unsigned int> > dp(s.size(), vector<unsigned int>(s.size(), 0));

        find(s, dp, preMe, nextMe, 0, s.size()-1);

        /*
        for(int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < s.size(); ++j) {
                std::cout << dp[i][j] << " ";
            }
            std::cout << std::endl;
        }
        */
        return dp[0][s.size()-1];
    }

    unsigned int find(string& s, vector<vector<unsigned int> >& dp,
             vector<int>& preMe, vector<int>& nextMe,
             int i, int j) {
        if (j < i) {return 0;}
        else if (j==i) {dp[i][j]=1; return 1;}
        
        if (dp[i][j] != 0) {
            return dp[i][j];
        }
        if (s[i] != s[j]) {
            dp[i][j] = find(s, dp, preMe, nextMe, i+1, j)
                + find(s, dp, preMe, nextMe, i, j-1) - find(s, dp, preMe, nextMe, i+1, j-1);
            unsigned long t = find(s, dp, preMe, nextMe, i+1, j)
                + find(s, dp, preMe, nextMe, i, j-1);
            if  (t < find(s, dp, preMe, nextMe, i+1, j-1)) {
                dp[i][j] = t+_modulus - find(s, dp, preMe, nextMe, i+1, j-1);
            }
        } else {
            int l = nextMe[i];
            int r = preMe[j];
            if (l==r) {
                // i+1..j-1中只有存在一个字符和s[i]相同
                dp[i][j] = 2*find(s, dp, preMe, nextMe, i+1, j-1) + 1;
            } else if (l > r) {
                // i+1..j-1中不存在和s[i]相同的字符
                dp[i][j] = 2*find(s, dp, preMe, nextMe, i+1, j-1) +2;
            } else {
                // i+1..j-1中存在至少2个和s[i]相同的字符
                dp[i][j] = 2*find(s, dp, preMe, nextMe, i+1, j-1) - find(s, dp, preMe, nextMe, l+1, r-1);
                if (2*dp[i+1][j-1] < dp[l+1][r-1]) {
                    dp[i][j] = 2*dp[i+1][j-1] + _modulus - dp[l+1][r-1];
                }
            }
        }
        dp[i][j] %= _modulus;
        return dp[i][j];
    }

private:
    const int _modulus = 1e9 + 7;


};

int main() {
    Solution sol;
    //string s = "bccb";
    //string s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba";
    string s = "bcbacbabdcbcbdcbddcaaccdcbbcdbcabbcdddadaadddbdbbbdacbabaabdddcaccccdccdbabcddbdcccabccbbcdbcdbdaada";  //output:117990582
    std::cout << sol.countPalindromicSubsequences(s) << std::endl;
    return 0;
}
