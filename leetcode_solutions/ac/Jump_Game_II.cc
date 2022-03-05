#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int jump(vector<int>& nums) {
		int sz = nums.size();
		if (sz == 0) return 0;
		//vector<int> nextHub(sz, -1);
		vector<int> steps(sz, sz+1);
		steps[sz-1] = 0;
		for (int i = sz-2; i >=0; --i) {
			for (int j = 1; j <= nums[i]; ++j) {
				if (i+j<sz && 1+steps[i+j] < steps[i]) {
					steps[i] = 1+steps[i+j];
					//nextHub[i] = i+j;
				}
			}
		}

		return steps[0];
    }
};

int main() {
    Solution sol;
	//Input: nums = [2,3,1,1,4]
	//Output: 2
	//vector<int> nums = {2,3,1,1,4};

	//Input: nums = [2,3,0,1,4]
	//Output: 2
	vector<int> nums = {2,3,0,1,4};
	
	std::cout << sol.jump(nums) << std::endl;
	return 0;
}
