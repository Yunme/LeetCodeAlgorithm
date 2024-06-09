#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 68: 文本左右对齐
 * 给定一个单词数组 words 和一个长度 maxWidth ，
 * 重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。
 *
 * 你应该使用 “贪心算法”
 * 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。 必要时可用空格 ' '
 * 填充，使得每行恰好有 maxWidth 个字符。
 *
 * 要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。
 * 文本的最后一行应为左对齐，且单词之间不插入额外的空格。
 *
 * https://leetcode.cn/problems/text-justification/description/
 */
class Solution {
   public:
   /**
    * 直接模拟：(自己实现）
    */
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        vector<string> ans;

        int i = 0, lineCharCount = 0;
        vector<string> lineArray;
        while (i < n) {
            string word = words[i];
            if (lineCharCount == 0 && word.length() == maxWidth) {
                // 正好等于行宽
                ans.push_back(word);
                i++;
            } else if (lineCharCount + word.length() + 1 >= maxWidth &&
                       lineArray.size() > 0) {
                // 下一个加起来大于行宽，停止，把当前行单词 加到结果中
                // + 1 单词间的空格
                // 等于的话，正好满一行，无多余空格
                if (lineCharCount + word.length() + 1 == maxWidth) {
                    lineArray.push_back(word);
                    lineCharCount += word.length() + 1;
                    i++;
                }
                // 剩余待分配空格数
                int totalSpace = maxWidth - lineCharCount;
                // 剩余空格分配给 size - 1个
                int tempSize = lineArray.size() - 1;
                string tempStr;
                // 0 这行只有一个单词
                if (tempSize == 0) {
                    for (int j = 0; j < lineArray.size(); j++) {
                        tempStr += lineArray[j] + ' ';
                    }
                    tempStr += string(maxWidth - tempStr.length(), ' ');
                } else {
                    // 一行大于1个单词
                    int base = totalSpace / tempSize;  // 每个至少分配的个数
                    int mod = totalSpace %
                              tempSize;  // 剩余的个数，1个1个从左到右分配
                    for (int j = 0; j < lineArray.size() - 1; j++) {
                        tempStr += lineArray[j];
                        int extra =
                            mod > 0 ? 1 : 0;  // 剩余的个数，1个1个从左到右分配
                        // 至少一个空格，和额外空格
                        tempStr += string(1 + base + extra, ' ');
                        mod--;
                    }
                    // 最后一个不需要拼空格
                    tempStr += lineArray[tempSize];
                }
                ans.push_back(tempStr);
                lineArray.clear();
                lineCharCount = 0;
            } else {
                if (lineCharCount > 0)
                    lineCharCount++;  // 每个单词前至少一个空格
                lineCharCount += word.length();
                lineArray.push_back(word);
                i++;
            }
        }
        // 最后一行 左对齐，后面补齐空格
        if (!lineArray.empty()) {
            string lastLine;
            for (int j = 0; j < lineArray.size(); j++) {
                lastLine += lineArray[j] + ' ';
            }
            lastLine += string(maxWidth - lastLine.length(), ' ');
            ans.push_back(lastLine);
        }
        return ans;
    }
};

int main() {
    string a(3, 'a');
    cout << a << endl;

    Solution* s = new Solution();
    vector<vector<string>> array = {
        {"This", "is", "an", "example", "of", "text", "justification."},
        {"What", "must", "be", "acknowledgment", "shall", "be"},
        {"Science", "is", "what", "we", "understand", "well", "enough", "to",
         "explain", "to", "a", "computer.", "Art", "is", "everything", "else",
         "we", "d"},
        {"Listen", "to", "many,", "speak", "to", "a", "few."},
        {"What", "must", "be", "shall", "be."}};
    vector<int> width = {16, 16, 20, 6, 5};

    for (int i = 0; i < array.size(); i++) {
        auto ans = s->fullJustify(array[i], width[i]);
        for (auto& s : ans) {
            cout << s.length() << ":" << s << endl;
        }
        cout << endl;
    }
}