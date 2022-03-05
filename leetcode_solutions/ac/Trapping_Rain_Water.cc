#include <iostream>
#include <vector>

using std::vector;
class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> volumn(height.size(), 0);
        // check height list from the left
		int highestPoint = 0;
        for (int i = 0; i < height.size(); ++i) {
            if (i == 0) {
				highestPoint = height[0];
				volumn[0] = 0;
            } else {
				if (height[i] > highestPoint) {
					highestPoint = height[i];
				}
				volumn[i] = highestPoint - height[i];
            }

        }

		// check height list from the right
		// notice: don't run loop for i == 0
		for (int i = height.size()-1; i > 0; --i) {
			if (i == height.size()-1) {
				highestPoint = height[i];
				volumn[i] = 0;
			} else {
				if (height[i] > highestPoint) {
					highestPoint = height[i];
				}

				int tmpV = highestPoint - height[i];
				if (tmpV < volumn[i]) {
					volumn[i] = tmpV;
				}
			}
		}

		int biggestTrapVolumn = 0;
		for (auto const& v : volumn) {
			biggestTrapVolumn += v;
		}
		return biggestTrapVolumn;
        
    }
};

int main () {
	Solution sol;
	//height = [0,1,0,2,1,0,1,3,2,1,2,1]
	//Output: 6
	//vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
	//Input: height = [4,2,0,3,2,5]
	//Output: 9
	vector<int> height = {4,2,0,3,2,5};
	std::cout << "result is: " << sol.trap(height) << std::endl;

    return 0;
}
