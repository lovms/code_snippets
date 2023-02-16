/**
 * 一开始是想到用最短路径来求解，这样将 0->n 以及n->0的路径的加和来表达耗时最短，同时计算整体value；
 *
 * 另一个就是时间有剩余的情况下，可以多次从0节点出发，想过是否不同的出发之间可以使用DP之类的解法；
 *
 * 但由于节点可以多次访问，但value计算只能记一次，所以上述想法的路径之间其实并不能完全独立，而是相互影响的，所以似乎都不太行得通。
 *
 *
 * 下面的实现方法就是 DFS + 回溯，需要维护几个变量：
 * 1）路径上访问过的节点visited_nodes，用于计算sum_value;
 * 2）当前节点；
 * 3）当前已经消耗的时间；
 * 4）当回到节点0时，录得的最大sum value，即 maxSum;
 *
 * 虽然由于可以多次访问相同节点，导致DFS的深度可以无限深，但是由于总耗时是有限的，
 * 所以本题都没有进行其他剪枝，就通过了，比较水！当然每个节点的度<=4可能也是复杂度不高的一个原因。
 *
 **/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <utility>

using std::vector;
using std::list;
using std::tuple;
using std::unordered_map;

class Solution {
public:
	Solution() : maxSum(0) {}

    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
		vector<list<tuple<int, int>>> u_edges(values.size(), list<tuple<int, int>>());

		for (auto& e : edges) {
			int u = e[0];
			int v = e[1];
			int t = e[2];
			u_edges[u].emplace_back(std::make_pair(v, t));
			u_edges[v].emplace_back(std::make_pair(u, t));
		}

		int cur_node = 0;

	    //unordered_set<int> visited_nodes;
	    unordered_map<int, int> visited_nodes;
		unsigned long long sum_value = values[0];
		visited_nodes.emplace(0, 1);
		maxSum = values[0];

        travel(visited_nodes,
			   u_edges,
			   sum_value,
			   values,
			   maxTime,
			   0,
			   0);

		return maxSum;
    }

	void travel(
			unordered_map<int, int>& visited_nodes,
            vector<list<tuple<int, int>>>& u_edges,
			unsigned long long sum_value,
			vector<int>& values,
			int maxTime,
			int current_node,
			int cost_time) {

		if (u_edges[current_node].size() == 0) {
			return;
		}

		unsigned long long sum = 0;
		for (auto nd : u_edges[current_node]) {
			int v = std::get<0>(nd);
			int t = std::get<1>(nd);
			//std::cout << "debug1: " << current_node << " -> " << v << " : " << t+cost_time << std::endl;
			if (t + cost_time > maxTime) {
				continue;
			}

			if (v == 0) {
				sum=sum_node_value(visited_nodes, values);
				//std::cout << "debug stop at 0: " << sum << std::endl;
				if (sum > maxSum) {
					maxSum = sum;
				}
			}
            
			if (t + cost_time == maxTime && v != 0) {
				continue;
			}

			auto itr = visited_nodes.find(v);
			if (itr == visited_nodes.end() || itr->second <= 0) {
				sum_value += values[v];
				visited_nodes[v] = 1;
				//std::cout << "debug exists: " << v << ", " << sum_value << std::endl;
			} else {
				visited_nodes[v] += 1;
			}

			travel(visited_nodes,
					u_edges,
					sum_value,
					values,
					maxTime,
					v,
					t+cost_time);

			if (visited_nodes[v] == 1) {
				sum_value -= values[v];
				//std::cout << "debug delete: " << v << ", " << sum_value << std::endl;
			}
			visited_nodes[v] -= 1;
		}

		return;
	}

	unsigned long long sum_node_value(unordered_map<int, int>& visited_nodes,
		vector<int>& values) {
	    unsigned long long sum = 0;
	    for (auto nd : visited_nodes) {
		   sum += nd.second > 0 ? values[nd.first] : 0;
		}
		return sum;
	}

	unsigned long long maxSum;
};

int main() {
	Solution sol;
	/* case1:
	vector<int> values = {0, 32, 10, 43};
	vector<vector<int>> edges;
	vector<int> ed1 = {0,1,10};
	vector<int> ed2 = {1,2,15};
	vector<int> ed3 = {0,3,10};
	*/
	vector<int> values = {1,2,3,4};
	vector<vector<int>> edges;
	vector<int> ed1 = {0,1,10};
	vector<int> ed2 = {1,2,11};
	vector<int> ed3 = {2,3,12};
	vector<int> ed4 = {1,3,13};
	edges.emplace_back(ed1);
	edges.emplace_back(ed2);
	edges.emplace_back(ed3);
	edges.emplace_back(ed4);
	int maxTime = 50;

	unsigned long long result = sol.maximalPathQuality(values, edges, maxTime); 
	std::cout << "result: " << result << std::endl;
	return 0;
}
