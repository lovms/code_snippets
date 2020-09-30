//Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
//
//Note:
//
//The solution set must not contain duplicate triplets.
//
//Example:
//
//Given array nums = [-1, 0, 1, 2, -1, -4],
//
//A solution set is:
//[
//  [-1, 0, 1],
//  [-1, -1, 2]
//]
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/3sum
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <set>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::stringstream;
using std::set;
using std::string;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> zeroSumTriplets;
        if (nums.size() < 3) {
            return zeroSumTriplets;
        }
            
        vector<int> positives;
        vector<int> negatives;
        int zeros = 0;
        std::unordered_map<int, int> numCounts;
        for (auto n : nums) {
            if (numCounts.find(n) == numCounts.end()) {
                numCounts.insert({n, 0});
			}
            numCounts[n] += 1;
			//cout << "n: " << n << "|" << numCounts[n] << endl;
            if (n > 0) {
                positives.push_back(n);
            } else if (n < 0) {
                negatives.push_back(n);
            } else {
                zeros++;
            }
		}
        
        if (zeros >= 3) {
            zeroSumTriplets.push_back(vector<int>({0, 0, 0}));
        }
        if (positives.size() == 0 || negatives.size() == 0) {
            return zeroSumTriplets;
		}

		int count = 0;
		string str;
	    stringstream ssm;
		set<string> uniq;
        for (auto p : positives)
            for (auto n : negatives) {
                int third = p + n;
				count = 0;
                if (1 == numCounts.count(-third)) {
					count = numCounts[-third];
				}
				
				//cout << "mark: " << -third << "|" << count << endl;
                if ((p == -third && count >= 2) || (n == -third && count >= 2) || (p!=(-third) && n!=(-third) && count > 0)) {
					//cout << "p:" << p << "|n:" << n << "|third:" << -third << "|count: " << count << endl;
					ssm.clear();
					if (-third > p) {
						ssm << -third << p << n;
					} else if (-third < n) {
						ssm << p << n << -third;
					} else {
						ssm << p << -third << n;
					}
					ssm >> str;
					//cout << "mark2: " << str << endl;
					if (uniq.find(str) == uniq.end()) {
						zeroSumTriplets.push_back(vector<int>({p, n, -third}));
						uniq.insert(str);
					} 
				}
			}
        return zeroSumTriplets;
    }
};


int main() {
	Solution sol;
	vector<int> nums = {-1, 0, 1, 2, -1, -4};
	vector<vector<int>> result = sol.threeSum(nums);
	for(auto v : result) {
		for (auto n : v) {
			cout << n << " ";
		}
		cout << endl;
	}
    return 0;
}
