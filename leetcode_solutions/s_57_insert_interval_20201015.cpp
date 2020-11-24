//Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
//
//You may assume that the intervals were initially sorted according to their start times.
//
// 
//
//Example 1:
//
//Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
//Output: [[1,5],[6,9]]
//Example 2:
//
//Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
//Output: [[1,2],[3,10],[12,16]]
//Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
//Example 3:
//
//Input: intervals = [], newInterval = [5,7]
//Output: [[5,7]]
//Example 4:
//
//Input: intervals = [[1,5]], newInterval = [2,3]
//Output: [[1,5]]
//Example 5:
//
//Input: intervals = [[1,5]], newInterval = [2,7]
//Output: [[1,7]]
// 
//
//Constraints:
//
//0 <= intervals.length <= 104
//intervals[i].length == 2
//0 <= intervals[i][0] <= intervals[i][1] <= 105
//intervals is sorted by intervals[i][0] in ascending order.
//newInterval.length == 2
//0 <= newInterval[0] <= newInterval[1] <= 105
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/insert-interval
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		if (intervals.size() == 0) {
			intervals.push_back(newInterval);
			return intervals;
		}
		int newIntr0At = -1;
		int newIntr1At = -1;
		string relation0 = "";
		string relation1 = "";
		int st = -1;
		int end = -1;
		for (int i = 0; i < intervals.size(); ++i) {
			if (newInterval[0] < intervals[i][0]) {
				if (relation0 == "") {
					newIntr0At = i;
					relation0 = "build_before";
					st = newInterval[0];
				}
			} else if (newInterval[0] <= intervals[i][1]) {
				if (relation0 == "") {
					newIntr0At = i;
					relation0 = "merge";
					st = intervals[i][0];
				}
			}

			if (newInterval[1] < intervals[i][0]) {
				if (relation1 == "") {
					newIntr1At = i-1;
					relation1 = "build_before";
					end = newInterval[1];
				}
			} else if (newInterval[1] <= intervals[i][1]) {
				if (relation1 == "") {
					newIntr1At = i;
					relation1 = "merge";
					end = intervals[i][1];
				}
			}
		}

		std::cout << newIntr0At << "," << relation0 << "|" 
			      << newIntr1At << "," << relation1 << std::endl;
		if (newInterval[0] > intervals[intervals.size()-1][1]) {
			newIntr0At = intervals.size();
			relation0 = "build_before";
			st = newInterval[0];
		}

		if (newInterval[1] > intervals[intervals.size()-1][1]) {
			newIntr1At = intervals.size();
			relation1 = "build_before";
			end = newInterval[1];
		}

		vector<int> tmp = {st, end};
		if (newIntr0At == newIntr1At-1 &&
			relation0 == "build_before" && relation1 == "build_before") {
			// insert before ith position [st, end];
			intervals.insert(intervals.begin()+newIntr0At, tmp);
		} else {
			// delete newIntr0At , newIntr1At
			if (newIntr1At != intervals.size()) {
			    intervals.erase(intervals.begin()+newIntr0At, intervals.begin()+newIntr1At+1);
			} else {
			    intervals.erase(intervals.begin()+newIntr0At, intervals.begin()+newIntr1At);
			}
			// insert before newIntr0At's positioin [st, end]
			intervals.insert(intervals.begin()+newIntr0At, tmp);
		}
		return intervals;
	}
};

int main() {
	Solution s;
	vector<vector<int>> intervals;
	/*
	intervals.push_back(vector<int>({1,2}));
	intervals.push_back(vector<int>({3,5}));
	intervals.push_back(vector<int>({6,7}));
	intervals.push_back(vector<int>({8,10}));
	intervals.push_back(vector<int>({12,16}));

	vector<int>newInterval({4,8});
	*/
	/*
	intervals.push_back(vector<int>({1,5}));
	vector<int>newInterval({0,6});
	*/

	intervals.push_back(vector<int>({1,4}));
	intervals.push_back(vector<int>({9,12}));
	intervals.push_back(vector<int>({19,22}));
	vector<int>newInterval({7,13});

	vector<vector<int>> newIntervals = s.insert(intervals, newInterval);

	for(auto it : newIntervals) {
		std::cout << "[" << it[0] << "," << it[1] << "]\t";
	}
	std::cout << std::endl;
	return 0;
}
