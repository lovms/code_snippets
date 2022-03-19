#include <iostream>
#include <unordered_map>
#include <vector>

/*
 *  target的每一个位置上有2中状态：是否清空，长度最大15，所以2^15就可以表达所有状态。
 *  DFS过程中，保存target的每个状态，以提升性能。
 */

using std::unordered_map;
using std::vector;
using std::string;

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int sz = stickers.size();
        vector<unordered_map<char, int>> stickerCharsCount;
        stickerCharsCount.reserve(sz);

        unordered_map<char, bool> targetChars;
        for (auto& ch : target) {
            targetChars[ch] = true;
        }

        bool canBeDisgarded = true;
        int hit = 0;
        for (int i = 0; i < stickers.size(); ++i) {
            hit = 0;
            canBeDisgarded = true;
            unordered_map<char, int> cmap;
            for (auto& ch : stickers[i]) {
                if (targetChars.find(ch) != targetChars.end()) {
                    canBeDisgarded = false;
                    if (cmap.find(ch) == cmap.end()) {
                        ++hit;
                    }
                }
                cmap[ch]++;
            }
            if (canBeDisgarded) {
                continue;
            }

            cmap['#'] = hit;

            stickerCharsCount.emplace_back(cmap);
        }

        struct {
            bool operator() (unordered_map<char, int>& a, unordered_map<char, int>& b) const { return a['#'] > b['#']; }
        } hitMore;
        std::sort(stickerCharsCount.begin(), stickerCharsCount.end(), hitMore);
        /*
        std::sort(stickerCharsCount.begin(), stickerCharsCount.end(), 
                [](unordered_map<char, int>& a, unordered_map<char, int>& b) {
                    return a['#'] > b['#'];
                });
                */

        /*
        for (auto& x : stickerCharsCount) {
            for (auto& p : x) {
                std::cout << p.first << "|" << p.second << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        */

        done_ = string(target.size(), '-');
        int res = dfs(target, 0, stickerCharsCount);
        return (res>target.size() ? -1 : res);
    }

private:
    int dfs(string& target, int ind,
            vector<unordered_map<char, int>>& stickerCharsCount) {
        auto iter = status_.find(target);
        if (iter != status_.end()) {
            return iter->second;
        }
        if (target == done_) {
            //std::cout << "YES" << std::endl;
            return 0;
        }
        //std::cout << "Debug0: target: " << target << "|ind: " << ind << std::endl;
        string curStr = target;
        int count = target.size() + 1; // initialize MIN as target.size()+1 because the amount of stickers to clear target would be no more than target.size()
        for (int i = ind; i < stickerCharsCount.size(); ++i) {
            /*
            if (ind == 0) {
                std::cout << i << " XXXXXXX: ";
                for (auto& p : stickerCharsCount[i]) {
                    std::cout << p.first << "|" << p.second << ", ";
                }
                std::cout << std::endl;
            }
            */
            auto tmap = stickerCharsCount[i]; // copy is quite time-consuming
            bool changed = false;
            for (int j = 0; j < curStr.size(); ++j) {
                if (curStr[j] == '-') continue;
                auto itr = tmap.find(curStr[j]);
                if (itr != tmap.end() && itr->second > 0) {
                    //std::cout << "X__X " << curStr[j] << "|" << tmap[curStr[j]] << std::endl;
                    curStr[j] = '-';
                    itr->second -= 1;
                    changed = true;
                }
            }
            if (!changed) continue;
            //std::cout << "Mark0: count: " << count << "|curStr: " << curStr << std::endl;
            count = std::min(count, 1+dfs(curStr, i, stickerCharsCount));
            //std::cout << "Mark1: count: " << count << "|target: " << target << std::endl;
            curStr = target;
        }
        status_.emplace(target, count);
        //std::cout << "Debug1: target: " << target << "|count: " << count << std::endl;
        return count;
    }

    unordered_map<string, int> status_;
    string done_;
};

int main() {
    Solution sol;
   
    /*
    vector<string> stickers = {"with","example","science"};
    string target = "thehat";
    */
    
    /*
    vector<string> stickers = {"notice","possible"};
    string target = "basicbasic";
    */

    /*
    vector<string> stickers = {"represent","all","set","show","there","modern","sing","seem","saw","cotton","sell","scale","from","no","sun","create","sentence","sail","wood","black","take","caught","cause","match","gave","division","pose","run","neighbor","food","rise","chart","plan","vowel","atom","cook","such","bit","with","wait","bat","piece","cover","up","allow","twenty","stone","arrive","root","example"};
    string target = "drydry";
    */

    /*
    vector<string> stickers = {"indicate","why","finger","star","unit","board","sister","danger","deal","bit","phrase","caught","if","other","water","huge","general","read","gold","shall","master","men","lay","party","grow","view","if","pull","together","head","thank","street","natural","pull","raise","cost","spoke","race","new","race","liquid","me","please","clear","could","reply","often","huge","old","nor"};
    string target = "fhhfiyfdcwbycma";
    */

    vector<string> stickers = {"letter","gold","give","fish","them","system","four","say","sudden","laugh","dear","still","boat","apple","thought","horse","from","prepare","how","provide","pay","people","three","to","hot","card","above","save","division","notice","complete","rain","band","game","mouth","decide","segment","him","bank","cool","term","life","against","motion","edge","nose","clean","enter","operate","where"};
    string target = "lessremember";

    std::cout << sol.minStickers(stickers, target) << std::endl;
    return 0;
}
