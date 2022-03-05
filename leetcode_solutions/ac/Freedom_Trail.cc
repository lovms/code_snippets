/*
In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.

Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character key[i]:

You can rotate the ring clockwise or anticlockwise by one place, which counts as one step. The final purpose of the rotation is to align one of ring's characters at the "12:00" direction, where this character must equal key[i].
If the character key[i] has been aligned at the "12:00" direction, press the center button to spell, which also counts as one step. After the pressing, you could begin to spell the next character in the key (next stage). Otherwise, you have finished all the spelling.
 

Example 1:


Input: ring = "godding", key = "gd"
Output: 4
Explanation:
For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
Also, we need 1 more step for spelling.
So the final output is 4.
Example 2:

Input: ring = "godding", key = "godding"
Output: 13
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

class Solution {
public:
    int findRotateSteps(string ring, string key) {
		unordered_map<char, vector<int> > char_pos_map; 
		for (int i = 0; i < ring.size(); i++) {
			char ch = ring[i];
			auto itr = char_pos_map.find(ch);
			if (itr == char_pos_map.end()) {
				auto res = char_pos_map.insert( {ch, vector<int>() });
				if (res.second) {
					itr = res.first;
				}
			}
			itr->second.emplace_back(i);
		}

		/*
		for(auto const& k : char_pos_map) {
			std::cout << k.first << " : ";
			for (auto& i : k.second) {
				std::cout << i << ", ";
			}
			std::cout << std::endl;
		}
		*/

		vector<int> steps = vector<int>(ring.size(), 0);

		stepForward(ring, key, char_pos_map, steps);

		return steps[0] + key.size();

	}

	void stepForward(string& ring, 
			        string& key, 
					unordered_map<char, vector<int>> & char_pos_map, 
					vector<int>& steps) {
		vector<int> from_pos;
		vector<int> to_pos;
		for (int index = key.size()-1; index >= 0; index--) {
			from_pos.clear();
			to_pos.clear();
			if (index == 0) {
				from_pos.push_back(0);
			} else {
    		    char from = key[index-1];
    		    from_pos = char_pos_map.find(from)->second; 
			}
    		char to = key[index];

    		to_pos = char_pos_map.find(to)->second;
    
    
    		for (auto i : from_pos) {
    		    int min = ring.size() * key.size() * 2;
    			for (auto j : to_pos) {
    				// clockwise i->j
    				int t = i < j ? (j-i) : (ring.size()-i+j); 
    				if (min > t+steps[j]) {
    					min = t+steps[j];
    				}
    
    				// anti clockwise i->j
    				t = i < j ? (ring.size()-j+i) : (i-j);
    				if (min > t + steps[j]) {
    					min = t + steps[j];
    				}
    			}
    			steps[i] = min;
    		}
		}
	}
};

int main() {
	Solution foo;
	string ring = "godding";
	string key = "godding";
	//string key = "gd";
	std::cout << foo.findRotateSteps(ring, key) << std::endl;
	return 0;
}

