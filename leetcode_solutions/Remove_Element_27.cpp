#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0; // index to the left-most element = `val` 
        int j = 0;  // index to the left-most element != `val` in the remain lists on the right of i, so j must be bigger than i.

        while (j < nums.size() && i < nums.size()) {
            if (nums[i]!=val) {
                i++;
                continue;
            }
            if (j<=i || nums[j] == val) {
                if (j <= i) { 
                    j = i; // j must be bigger than i (after j++)
                }
                j++;
                continue;
            }
            nums[i] = nums[j];
            nums[j] = val;
        }
		return i;  // #elements != `val`
    }
};

int main() {
	Solution sol;
	//std::vector<int> nums = {0,1,2,2,3,0,4,2};
	//std::vector<int> nums = {3,2,2,3};
	std::vector<int> nums = {4,5};


	int result = sol.removeElement(nums, 4);

	for (auto& x: nums) {
		std::cout << x << " ";
	}
	std::cout << std::endl << result << std::endl;
	return 0;
}
