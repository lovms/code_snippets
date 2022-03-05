/**
 * 计算一个数组有多少逆序对,最快是O(nlogn)，和排序是一样的，因为要比较两两个pair.
 * 本题要求[1,..n]数组，有k个逆序对的排列数，显然不能产生所有排列数，然后一个个去数逆序对。
 *
 * 所以直觉告诉我，应该从“构建”逆序对的角度去思考解题方法。
 *
 * 如果知道[1,2,3] 所有的k个逆序对的情形下，能否快速算出[1,2,3,4]所有k个逆序对的数目呢？检查发现是可以的 TODO 展开
 *
 * 本题非常符合DP，和斐波那契数的计算很相似，但更复杂些，有两个技巧需要特别注意：
 *
 * 1)
 * 其中，计算mat[n][k]需要将 mat[n-1][0] + mat[n-1][1] + ... + mat[n-1][k]，因此有非常多的共享子结构，这里为了避免
 * 重复的求和运算, 其实使用了类似于前缀和的技巧！！
 *
 * 2)
 * 另外，由于本题的和会非常大，即便用unsigned long long保存都会溢出，所以结果要取模数。但本题中使用的前缀和引入了一个未遇到过的问题：
 * 之前遇到过，并且模数的加法和乘法运算遵循FOIL method (分配律），但减法并不是，需要特别注意，这也是我在解题中遇到负数情况的原因！
 *
 * (a-b) % m != a%m - b%m
 *
 * if a <=m and b <=m
 *    if a < b
 *       (a-b) %m = a+m-b
 **/

/*
629. K Inverse Pairs Array
For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].

Given two integers n and k, return the number of different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.

 

Example 1:

Input: n = 3, k = 0
Output: 1
Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
Example 2:

Input: n = 3, k = 1
Output: 2
Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
 

Constraints:

1 <= n <= 1000
0 <= k <= 1000
*/
#include <iostream>
#include <vector>

using std::vector;
class Solution {
public:
    int kInversePairs(int n, int k) {
        const unsigned long  modulus = 1e+9 + 7;
        vector<vector<int>> mat(n+1, vector<int>(k+1, 0));
        for (int i = 1; i<=n; ++i) {
            mat[i][0] = 1;
            int j = 1;
            
            if (i==n) { //减少运算的处理，不需要求mat[n][k-1] ...
                if (k==0) {
                    break;
                }
                j = k;
            }
            
            for (;j<=k; ++j) {
                /* 
                for (int p=j; p+(i-1)>=j && p>=0; --p) {
                    unsigned long t = mat[i][j] + mat[i-1][p];
                    mat[i][j] = t % modulus;
                }*/
                int p = j-(i-1); 
                int  t = mat[i][j-1]; // + (p<=0? mat[i-1][j]:(mat[i-1][j]-mat[i-1][p-1]));
				if (p<=0) {
					t += mat[i-1][j];  //前缀和，避免重复求和
				} else {
					if (mat[i-1][j] < mat[i-1][p-1]) {
						t += mat[i-1][j] + modulus - mat[i-1][p-1];  // 对模数减法的特殊处理
					} else {
						t += mat[i-1][j] - mat[i-1][p-1];
					}
				}
                mat[i][j] = t % modulus;
            }
        }
        
		/*
        for (int i=1; i<=n; ++i) {
            for (int j=0; j<=k; ++j) {
                std::cout << i << "," << j << "|" << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
		*/
        
        return (k==0? 1:(mat[n][k]-mat[n][k-1]));
     }
};

int main() {
	Solution sol;
	int n = 1000;
	int k = 1000;
	// 663677020
	std::cout << sol.kInversePairs(n, k) << std::endl;
    return 0;
}
