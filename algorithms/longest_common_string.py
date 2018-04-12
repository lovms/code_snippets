import sys
import numpy as np


'''
(1)
对于字符串z 和 y，index i, j分别从0开始指示z和y的字符，lcs(i, j)表示 z(i, ... len(z)和y(j, ..., len(j))的最长公共子串,
存在如下递归计算式：

如果 z(i) == y(j)，那么lcs(i, j) = z(i) + lcs(i+1, j+1);
否则，即z(i) != y(j), 那么lcs(i, j) = max(lcs(i, j+1), lcs(i+1, j))

(2)
注意到，lcs(i, j+1) 和lcs(i+1, j)的子调用中存在大量重复的计算，因此，符合动态规划的子问题分解和共享的特点

同时，如果存在lcs(i, j+1) == lcs(i+1, j)的情况，说明z和y的lcs不止一种

(3)
下面的实现中，其实是用了查表的实现方式，即先查表，如果计算过了，则直接返回结果

(4)
因此，lcs的时间复杂度其实是O(mn), m,n 分别是两个字符串的长度,因为每个字符串中的一个字符，都和另一个字符串中的每个字符必须且仅比较一次

(5)
打印出lcs，打印出lcs是逆向算法过程。依照lcs(i, j）最大的子问题 max(lcs(i+1, j), lcs(i, j+1))，逆向找；

当lcs(i, j) > max(lcs(i+1, j), lcs(i, j+1))时，说明z(i) = y(j)是lcs的一个字符
'''

class Alg_Lcs(object):
    def __init__(self):
        self.MAX_STR_SIZE = 1000
        self.record = np.zeros((1000, 1000)) - 1
        self.s_lcs = ""

    def lcs(self, str1, str2, i, j):
        if len(str1) > self.MAX_STR_SIZE or len(str2) > self.MAX_STR_SIZE:
            sys.stderr.write("Input String Size is Over MAX_STR_SIZE, %s" % (self.MAX_STR_SIZE))
            return -1
        if i < 0 or j < 0:
            sys.stderr.write("Index Out of Range {:d}, {:d}".format(i, j))
            return 0
        if i >= len(str1) or j >= len(str2):
            return 0

        if self.record[i, j] != -1:
            return self.record[i, j]

        if str1[i] == str2[j]:
            self.record[i, j] = 1 + self.lcs(str1, str2, i+1, j+1);

        else:
            self.record[i, j] = max(self.lcs(str1, str2, i, j+1), self.lcs(str1, str2, i+1, j))
        return self.record[i, j]

    def get_lcs(self, str1, str2):
        self.lcs(str1, str2, 0, 0)
        i = 0
        j = 0
        while i < len(str1) and j < len(str2) and self.record[i, j] > 0:
            if self.record[i, j] > max(self.record[i+1, j], self.record[i, j+1]):
                self.s_lcs += str1[i]
                i += 1
                j += 1
            elif self.record[i, j] == self.record[i+1, j]:
                i += 1
            elif self.record[i, j] == self.record[i, j+1]:
                j += 1
        print("The Longest Common String {:s} and {:s} is ###{:s}### with length {:f}".format(str1, str2, self.s_lcs, self.record[0, 0]))


if __name__ == '__main__':
    ins = Alg_Lcs()
    #string1 = "abcdsgshhdfghgdfjjl;jdlgj;dfjhj;jfdj"
    #string2 = "becfdsgrgjsjhlasjgglkfsk'hfdglkfjgfdgfsj"
    string1 = "abcdds"
    string2 = "acf"
    ins.get_lcs(string1, string2)

