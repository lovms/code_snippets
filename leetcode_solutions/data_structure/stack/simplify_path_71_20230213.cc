/**
 * 这道题并不难，因为需要判断的状况并不是很多。
 * 我设定了在每次遇到'/'时对状态进行判断再进行相应的处理。
 *
 * 有2点关键处：
 * 1）因为 '/..' 需要回退，自然而然的使用堆栈是合适的；
 * 2）为了避免在循环处理完，还有剩余的状态没有判断，所以
 *    我特地的在原始目录字符串的结尾添加了'/'，从而使得
 *    在循环结束时一定判断完当时的状态。
 *    但相应的，我们需要对结尾的'/'作处理，按照题目要求标准
 *    的路径结尾是不包含'/'的；
 * 3）一定要注意第一位的'/'是永远不能删除的！！！
 **/
/*
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')
Return the simplified canonical path.

*/

#include <iostream>
#include <string>
#include <stack>

using std::string;
using std::stack;

class Solution {
public:
    string simplifyPath(string path) {
		stack<char> p;
		int consecutive_dots = 0;
		int non_dots = 0;  // non-dots chars number

		path = path + "/";  // convenient for loop
	    

		for (int i = 0; i < path.size(); ++i) {
			if (path[i] == '/') {
				// check status and handle previous segmental directory
				if (!p.empty()) {
					if (p.top() == '/') {  //  '//'
						continue;
					}
					if (consecutive_dots == 1 and non_dots == 0) {
						// '/./'
						p.pop();
				        consecutive_dots = 0;
				        non_dots = 0;
						continue;
					} else if (consecutive_dots == 2 and non_dots == 0) {
						// '/../'
						p.pop(); // .
						p.pop(); // .
					    if (p.size() > 1) {
							// particularly, the first '/' could never be deleted !
						    p.pop(); // '/'
						}
				        consecutive_dots = 0;
				        non_dots = 0;
						while (!p.empty() && p.top() != '/') {
							p.pop();
						}
						continue;
					}
				}
				consecutive_dots = 0;
				non_dots = 0;
			} else if (path[i] == '.') {
			    consecutive_dots++;
			} else {
				non_dots++;
			}

			p.push(path[i]);
		}

		if (p.size() == 1 && p.top() == '/') {
			return "/";
		}
		p.pop();  // discard '/' of the end
		string qualified_unix_path(p.size(), '\0');

		for (int i = qualified_unix_path.size()-1; i >= 0; i--) {
			qualified_unix_path[i] = p.top();
			p.pop();
		}
		return qualified_unix_path;
    }
};

int main() {
	Solution sol;
	//string path ="/home/foo/dir1/dir2/./../.../x";
	//string path ="/home//foo/";
	string path ="/a/../../b/../c//.//";
	std::cout << sol.simplifyPath(path) << std::endl;

	return 0;
}
