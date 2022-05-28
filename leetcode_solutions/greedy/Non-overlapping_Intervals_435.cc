#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

		std::sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
				    if (a[0] < b[0]) {
					    return true;
					} else if (a[0] == b[0]) {
					    return a[1] < b[1];
					} 
					return false;
				});

		/*
		for (auto & vec : intervals) {
			std::cout << "[" << vec[0] << "," << vec[1] << "]\t";
		}
		std::cout << std::endl;
		*/

		/*
		vector<vector<int>>::iterator iter = intervals.begin() + 1;
		int count = 0;
		for ( ; iter != intervals.end(); ) {
			auto pre = iter - 1;
			if ((*iter)[0] < (*pre)[1]) {
				iter = intervals.erase(iter);
				++count;
			} else {
				++iter;
			}
		}
		*/
		int pre = 0;
		int next = 1;
		int count = 0;
	    while (next < intervals.size()) {
			if (intervals[pre][1] > intervals[next][0]) { // intersect or overlap
				++count;
				if (intervals[pre][1] > intervals[next][1]) {
					pre = next;
				}
			} else {
				pre = next;
			}
			++next;
		}

		return count;
    }
};

int main() {
	Solution sol;
	//vector<vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
	vector<vector<int>> intervals = {{1,2},{1,2},{1,2}};
	//vector<vector<int>> intervals = {{-52,31},{-73,-26},{82,97},{-65,-11},{-62,-49},{95,99},{58,95},{-31,49},{66,98},{-63,2},{30,47},{-40,-26}};
	std::cout << sol.eraseOverlapIntervals(intervals) << std::endl;
	return 0;
}
