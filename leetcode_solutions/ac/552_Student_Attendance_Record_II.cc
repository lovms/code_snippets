#include <iostream>
#include <vector>

#define DEBUG false
#define debug_print(j,k) \
	if (DEBUG) { \
	    std::cout << i << "_" << j << "_" << k << ": " << dp[i][j][k] << std::endl; \
	} \

/*
 *x[I][j][k]

k==0 
If j == 0 &&   x[I] == ‘Present’
x[I][0][0] = x[I-1][0][0] + x[i-1][0][1] + x[I-1][0][2]

If j==1
x[I][1][0] = x[I][0][0] // x[I]  == ‘Absent’
x[I][1][0] = x[I][1][0] + x[i-1][1][1] + x[I-1][1][2].   // x[I]  == ‘Present’

k==1.   // x[I] = ‘Late’ && x[i-1] !=‘Late’
If j==0 
x[I][0][1] = x[i-1][0][0]

If j==1
x[I][1][1] = x[I-1][1][0]

k==2   // x[I] = x[I-1] = ‘Late’

If j==0

x[I][0][2] = x[I-1][0][1]

If j==1

x[I][1][2] = x[i-1][1][1]
 */
class Solution {
public:
    int checkRecord(int n) {
		if (n==0) {
			return 0;
		}
		//int dp[n][2][3];
		unsigned long long (*dp)[2][3] = new unsigned long long[n+1][2][3];
		//std::cout << (n+1)*2*3 << std::endl;
		memset(dp, 0, (n+1)*2*3);
		dp[1][0][0] = 1; //Present
		dp[1][0][1] = 1; //Late
		dp[1][1][0] = 1; //Absence
		if (n == 1) {
			return 3;
		}

		dp[2][0][0] = 2; // PP, LP
		dp[2][0][1] = 1;  // PL
		dp[2][0][2] = 1;  // LL
		dp[2][1][0] = 3;  // AP; PA; LA
		dp[2][1][1] = 1;   // AL
		dp[2][1][2] = 0;  // xx
		if (n==2) {
			return 8;
		}

		const int modulus = 1e+9 + 7;
		unsigned long long sum = 0;
		for (int i = 3; i <= n; ++i) {
			//k == 0
			//// j == 0
			sum = dp[i-1][0][0] + dp[i-1][0][1] + dp[i-1][0][2];
			dp[i][0][0] = sum % modulus;
			debug_print(0,0);
			//// j == 1
			sum = dp[i-1][0][0] + dp[i-1][0][1] + dp[i-1][0][2] + 
						  dp[i-1][1][0] + dp[i-1][1][1] + dp[i-1][1][2];
			dp[i][1][0] = sum % modulus;
			debug_print(1,0);
			// k==1
			//// j==0 
			dp[i][0][1] = dp[i-1][0][0];
			debug_print(0,1);
			//// j==1
			dp[i][1][1] = dp[i-1][1][0];
			debug_print(1,1);

			// k==2
			//// j==0
			dp[i][0][2] = dp[i-1][0][1];
			debug_print(0,2);
			//// j==1
			dp[i][1][2] = dp[i-1][1][1];
			debug_print(1,2);
		}

		sum = dp[n][0][0] + dp[n][0][1] + dp[n][0][2] +
					 dp[n][1][0] + dp[n][1][1] + dp[n][1][2];
		int  result = sum % modulus;
		delete[] dp;

		return result;
    }
};

int main() {
	Solution sol;
	int n = 3; 
	std::cout << sol.checkRecord(n) << std::endl;
	return 0;
}
