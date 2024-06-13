#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
/**
 * OD
 * 手机号归属地查询
 * 根据 号段以及归属地映射
 * 找出电话号码的归属地
 *
 * 比如：
 * 139：属于A
 * 13912：属于B
 * 180：属于C
 * 那么
 * 13900001111：A
 * 13912001111：B
 * 18012345678：C
 */

/**
 * 法1：正向思维 O(n * m) n为 map 长度，m为 map 中key 最长的字符串长度
 */
string checkPhone(string phone, unordered_map<string, string> map) {
    string matched;
    int maxMatchedLength = 0;
    // 遍历每个号段，逐个与号码前面匹配，找出匹配最长的
    for (auto &[k, v] : map) {
        int i = 0;
        while (i < k.length() && i < phone.length()) {
            if (k[i] == phone[i])
                i++;
            else
                break;
        }
        // 完整匹配 key，且找出匹配结果最长的 key
        if (i == k.length() && i > maxMatchedLength) {
            maxMatchedLength = i;
            matched = k;
        }
    }
    return map[matched];
}

/**
 * 逆向思维：逐个从号码末端删除一个字符，在map里查找。
 * O(n) n 为手机号长度
 */
string checkPhone2(string phone, unordered_map<string, string> map) {
    int n = phone.length();
    for (int i = n - 1; i > 0; i--) {
        string sub = phone.substr(0, i);
        if (map.find(sub) != map.end()) {
            return map[sub];
        }
    }
    return "";
}

int main() {
    vector<string> array = {"13912341234", "13911231234", "18012345677"};
    unordered_map<string, string> map = {
        {"139", "A"}, {"13912", "B"}, {"180", "C"}};

    for (auto &s : array) {
        auto ans = checkPhone2(s, map);
        cout << ans << endl;
    }
}
