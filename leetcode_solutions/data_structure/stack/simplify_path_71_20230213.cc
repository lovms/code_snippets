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
