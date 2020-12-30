#include <iostream>
#include <vector>

using std::vector;

void debugPrint(vector<int>& array) {
	for (auto v : array) {
		std::cout << v << " ";
	}
	std::cout << std::endl;
}
void swap(vector<int>& array, int i, int j) {
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

// siftDown 操作是针对已经建立好的"大头堆"或者"小头堆"的，
// 整个堆中，唯一违反规则的就是这里传入的root节点！！！
// 
// 在heap sort一开始的建堆操作中，需要从最后一个parent节点开始，
// 依次遍历相近的parent节点，使用siftDown操作，直至第0个元素，
// 从而建立"大头堆"或者"小头堆"。
//
// 所以，可以不是单凭一次siftDown的调整来建堆的。理解这一点很重要。
//
// 注意点：
// 一般用数组来表示(完全)二叉树，如果节点从1开始，那么i 个节点的
// 左孩子是2*i,右孩子是2*i+1；
// 但如果节点从0开始, 那么第i个节点的左孩子是2*i+1,右孩子是2*i+2
void siftDown(vector<int>& array, int root, int end) {
	int target = root;
	while (root < end) {
		int leftChild = 2*root+1;
		if (leftChild <= end && array[root] < array[leftChild]) {
			swap(array, root, leftChild);
			target = leftChild;
		}
		if (leftChild+1 <= end && array[root] < array[leftChild+1]) {
			swap(array, root, leftChild+1);
			if (target == root) {
				target = leftChild+1;
			}
		}
		std::cout << "debug: in siftDow: root, target: " << root << ", " << target << std::endl;
		if (root == target) {return;}
		root = target;
	}
}

void hsBuild(vector<int>& array) {
	int parent = (array.size()-1)/2 - 1;  // find the last parent
	while (parent >= 0) {
		std::cout << "tmp parent: " << parent << std::endl;
		siftDown(array, parent, array.size()-1);
		parent--;
	}
}

void hsMain(vector<int>& array) {
	hsBuild(array);
	std::cout << "mark 1\n";
	debugPrint(array);

	int end = array.size() - 1;
	swap(array, 0, end);

	end--;

	while (end > 0) {
		siftDown(array, 0, end);
		swap(array, 0, end);
		end--;
	}

}



int main() {
	vector<int> input = {7, 14, 22, 1, 789, 33, 45, 40, 6};

	hsMain(input);

	debugPrint(input);
	return 0;
}
