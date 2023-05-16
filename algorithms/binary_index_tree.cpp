/* Binary Index Tree (BIT) 树状数组，又称为Fenwick Tree （Fenwick最早发明的）
 * 它是针对需要动态维护的前缀和设计出来的，可以将静态前缀和的修改复杂度从O(n)
 * 降低到O(logn)，当然查询的时间复杂度也从O(1)增加到O(logn)。
 *
 * 但总体上Fenwick Tree可以在O(logn)时间内完成一次查询、修改前缀和的操作。
 */

#include <iostream>
#include <vector>

using std::vector;


class BIT {
public:
    BIT() {}

    void init(vector<int>& array) {
        buffer.resize(array.size());
        for (int i = 0; i < buffer.size(); ++i) {
            buffer[i] = 0;
        }

        buffer[0] = array[0];
        for (int i = 1; i < array.size(); ++i) {
            update(i, array[i]);
        }
    }

    int lowbit(int x) {
        return x&(-x);
    }

    // 查询前缀和：Sigma(array[0...i])
    // 使用buffer[x - lowbit(x)]来找到上一个区间段
    // 最后累加到buffer[0]
    int query(int i) {
        int sum = 0;

        while (i > 0) {  // 不能将条件变成 i >= 0，否则 i-lowbit(i)最终会变成0从而陷入死循环
            sum += buffer[i];
            i = i - lowbit(i);
        }

        if (i == 0) {
            sum += buffer[0];
        }
        return sum;
    }

    // 原数组array中第i位元素的值变化了val_dif
    // 按照buffer[x+lowbit(x)]来更新BIT
    void update(int i, int val_dif) {
        if (i == 0) {   // i=0单独处理，0+lowbit(0)依然等于0，陷入死循环
            buffer[0] += val_dif;
            return;
        }
        while (i < buffer.size()) {
            buffer[i] += val_dif;
            i += lowbit(i);
        }
    }

    void print() {
        std::cout << "Binary Index Tree's buffer: " << std::endl;
        for (auto i : buffer) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }
private:
    vector<int> buffer;
};

/*
int main() {
    vector<int> array = {1,2,3,4,5,6,7,8,9};

    BIT fenwick;

    fenwick.init(array);

    fenwick.print();

    return 0;
};

*/
