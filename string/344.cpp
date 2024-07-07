#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 344：反转字符串
 * 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s
 * 的形式给出。 不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用
 * O(1) 的额外空间解决这一问题。
 *
 * https://leetcode.cn/problems/reverse-string/description/
 */

class Solution {
   public:
    /**
     * 双指针首尾交换
     */
    void reverseString(vector<char>& s) {
        int i = 0;
        int j = s.size() - 1;
        while (i < j) {
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            i++;
            j--;
        }
    }
};

int main() {
    Solution* solution = new Solution();
    vector<vector<char>> arr = {{'h', 'e', 'l', 'l', 'o'},
                                {'H', 'a', 'n', 'n', 'a', 'h'}};
    for (auto chars : arr) {
        solution->reverseString(chars);
        for (auto c : chars) {
            cout << c;
        }
        cout << endl;
    }
    return 0;
}