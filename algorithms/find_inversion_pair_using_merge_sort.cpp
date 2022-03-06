#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


int mergeSort(vector<float>& nums) {
	//[start, end]
	if (nums.size() <= 1) {
		return 0;
	}

	int halfSize = ceil(nums.size() / 2.0);

	//std::cout << "Debug1: " << halfSize << std::endl;
	vector<float> half1(halfSize, 0);
	vector<float> half2(nums.size()-halfSize, 0);


	int p1 = 0;
	int p2 = 0;
	for (int i = 0; i < nums.size(); ++i) {
		if (i < halfSize) {
			half1[p1++] = nums[i];
		} else {
			half2[p2++] = nums[i];
		}
	}

	int rn1 = mergeSort(half1);
	int rn2 = mergeSort(half2);

	p1 = 0;
	p2 = 0;
	int  p = 0;

	int reverseNum = rn1 + rn2;
	while (p1 < half1.size() && p2 < half2.size()) {
		if (half1[p1] > half2[p2]) {
			nums[p++] = half2[p2++];
			reverseNum++;
			//std::cout << "R: <" << half1[p1] << "," << half2[p2] << ">" << std::endl;
		} else {
			nums[p++] = half1[p1++];
		}
	}

	// If half1 is not empty, then remain nums in half1
	// are all reversed to nums in half2!
	// We should note that the p1'th num in half1 has been dealed with,
	// so it shouldn't be dealed with again in the loop below.
	bool repeat = true;
	while (p1 < half1.size()) { 
		nums[p++] = half1[p1];
		if (!repeat) {
			for (auto v : half2) {
				//std::cout << "R: <" << half1[p1] << "," << v << ">" << std::endl;
				reverseNum++;
			}
		}
		repeat = false;
		++p1;
	}

	while (p2 < half2.size()) {
		nums[p++] = half2[p2++];
	}

	return reverseNum;
	
}

int main() {
	//vector<float> nums = {3, 5, 7, 1,2,0};
	vector<float> nums = {};
	std::cout << "#Reverse pair is: " << mergeSort(nums) << std::endl;

	for (auto v : nums) {
		std::cout << v << "\t";
	}

	std::cout << std::endl;
	return 0;
}
