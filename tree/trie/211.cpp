#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * 211: 添加与搜索单词 - 数据结构设计
 *
 * 请你设计一个数据结构，支持 添加新单词 和
 * 查找字符串是否与任何先前添加的字符串匹配 。
 *
 * 实现词典类 WordDictionary ：
 *
 * WordDictionary() 初始化词典对象
 * void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
 *
 * bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true
 * ；否则，返回  false 。word 中可能包含一些 '.' ，每个 .
 * 都可以表示任何一个字母。
 *
 * https://leetcode.cn/problems/design-add-and-search-words-data-structure/description
 */

/**
 * 字典树 结点
 */
struct TrieNode {
    vector<TrieNode*> children;
    bool isEnd;
    TrieNode() : children(26), isEnd(false) {}
    ~TrieNode() {
        for (TrieNode* p : children) {
            delete p;
        }
    }
};

class WordDictionary {
   private:
    TrieNode* root = new TrieNode();

   public:
    WordDictionary() {}
    ~WordDictionary() { delete root; }
    void addWord(string word) {
        TrieNode* p = root;
        for (char c : word) {
            int index = c - 'a';
            if (p->children[index] == nullptr) {
                p->children[index] = new TrieNode();
            }
            p = p->children[index];
        }
        p->isEnd = true;
    }

    bool search(string word) {
        TrieNode* p = root;
        return searchForIndex(p, 0, word);
    }

    /**
     * dfs 搜索
     * 从字符串 index 处搜索
     *
     * @return 表示 word[index] 能否在当前的 p 数组里找到
     */
    bool searchForIndex(TrieNode* p, int index, string& word) {
        if (index == word.length()) {
            return p->isEnd;
        }
        char c = word[index];
        if (c == '.') {
            // 如果是. 遍历当前的每个字母
            for (int i = 0; i < p->children.size(); i++) {
                TrieNode* next = p->children[i];
                // next 存在字母，且下一个能找到，返回 true
                if (next && searchForIndex(next, index + 1, word)) {
                    return true;
                }
                // 不存在字母，或下一个找不到，继续下一轮循环
            }
        } else {
            TrieNode* next = p->children[c - 'a'];
            if (next) {
                return searchForIndex(next, index + 1, word);
            }
            return false;
        }
        return false;
    }
};

int main() {
    WordDictionary* dic = new WordDictionary();
    dic->addWord("bad");
    dic->addWord("dad");
    dic->addWord("mad");
    dic->addWord("aadc");
    cout << dic->search("pad") << endl;
    cout << dic->search("bad") << endl;
    cout << dic->search(".ad") << endl;
    cout << dic->search("b..") << endl;
    cout << dic->search(".ad.") << endl;
}