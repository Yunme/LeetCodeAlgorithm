#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 949:给定数字能组成的最大时间
 * 给定4个数字，输出能组成的最大的24小时制时间
 * https://leetcode.cn/problems/largest-time-for-given-digits/description/
 */
class Solution {
   public:
    /**
     * 00:00 ~ 23:59
     */
    string largestTimeFromDigits(vector<int>& arr) {
        int count = arr.size();
        int maxMin = -1;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (i != j) {
                    for (int k = 0; k < count; k++) {
                        if (k != i && k != j) {
                            // 0+1+2+3 = 6;
                            int l = 6 - i - j - k;
                            // cout << arr[i] << " " << arr[j] << ":" << arr[k]
                            //      << " " << arr[l] << endl;
                            // 小时位：
                            int hour = 10 * arr[i] + arr[j];
                            int min = 10 * arr[k] + arr[l];
                            if (hour < 24 && min < 60) {
                                maxMin = max(maxMin, hour * 60 + min);
                            }
                        }
                    }
                }
            }
        }
        if (maxMin < 0) return "";
        ostringstream oss;
        oss << std::setw(2) << setfill('0') << maxMin / 60 << ":"
            << std::setw(2) << setfill('0') << maxMin % 60;
        return oss.str();
    }
};

int main() {
    Solution* s = new Solution();
    vector<vector<int>> arr = {
        {1, 2, 3, 4}, {0, 0, 0, 0}, {5, 5, 5, 5}, {2, 0, 6, 6}};

    for (auto& i : arr) {
        cout << s->largestTimeFromDigits(i) << endl;
    }
}