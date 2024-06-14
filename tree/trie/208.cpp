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
 * 208：实现 Trie（前缀树）
 *
 * Trie（发音类似 "try"）或者说 前缀树
 * 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
 *
 * 请你实现 Trie 类：
 * Trie() 初始化前缀树对象。
 * 向前缀树中插入字符串 word 。
 * - void insert(String word)
 *
 * 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回
 * false 。
 * - boolean search(String word)
 *
 * 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回
 * false 。
 * - boolean startsWith(String prefix)
 *
 * https://leetcode.cn/problems/implement-trie-prefix-tree/description/
 */

/**
 * map 实现
 */
class Trie {
   private:
    unordered_map<char, Trie*> children;
    bool isEnd;
    string value;

    Trie(string parent, char c) : Trie() { this->value = parent + c; }

   public:
    Trie() { this->isEnd = false; }

    /**
     * 迭代插入
     * 遍历字符串 逐个字符插入
     * 如果存在则，下个结点，
     * 不存在，插入，下个结点
     */
    void insert(string word) {
        Trie* p = this;
        for (char c : word) {
            if (p->children.count(c) == 0) {
                // 不存在 插入
                p->children[c] = new Trie(p->value, c);
            }
            p = p->children[c];
        }
        // 单词插入完成
        p->isEnd = true;
    }

    /**
     * 搜索完整单词， isEnd = true
     * 逐个结点搜索 直到搜完整个字符串
     */
    bool search(string word) {
        Trie* p = this;
        int i = 0;
        for (; i < word.length(); i++) {
            char c = word[i];
            // 存在，下个结点
            if (p->children.count(c) > 0) {
                p = p->children[c];
            }
        }
        // return i == word.length() && p->isEnd;
        return p->value == word && p->isEnd;
    }

    /**
     * 搜索前缀，
     * 逐个结点搜索， 直到搜完整个前缀
     */
    bool startsWith(string prefix) {
        int n = prefix.length();
        Trie* p = this;
        int i = 0;
        for (; i < n; i++) {
            char c = prefix[i];
            if (p->children.count(c) > 0) {
                p = p->children[c];
            }
        }
        // return i == n;
        return p->value == prefix;
    }
};

/**
 * 字符集较小情况下，使用数组存储 更好
 * 数组实现, 每个结点可以不存储前缀
 */
class Trie2 {
   private:
    // 每个结点的子树
    vector<Trie2*> children;
    // 当前是否是单词结尾
    bool isEnd;
    /**
     * 通用搜索结点
     */
    Trie2* searchPrefix(string prefix) {
        Trie2* p = this;
        for (char c : prefix) {
            int i = c - 'a';
            if (p->children[i] == nullptr) {
                return nullptr;
            }
            p = p->children[i];
        }
        return p;
    }

   public:
    Trie2() : children(26), isEnd(false) {}

    /**
     * 插入结点
     */
    void insert(string word) {
        Trie2* p = this;
        for (char c : word) {
            int i = c - 'a'; // 对应 index
            if (p->children[i] == nullptr) {
                // 为空 创建结点
                p->children[i] = new Trie2();
            }
            // 指针下移
            p = p->children[i];
        }
        // 插入完成，当前 isEnd 设为 true
        p->isEnd = true;
    }

    /**
     * 搜索单词
     */
    bool search(string word) {
        Trie2* p = searchPrefix(word);
        // 单词 isEnd  必须为 true
        return p && p->isEnd;
    }

    bool startsWith(string prefix) { return searchPrefix(prefix); }
};

typedef Trie2 TestTrie;

int main() {
    TestTrie* trie = new TestTrie();
    trie->insert("apple");
    cout << trie->search("apple") << endl;
    cout << trie->search("app") << endl;
    cout << trie->startsWith("app") << endl;
    trie->insert("app");
    cout << trie->search("app") << endl;
}