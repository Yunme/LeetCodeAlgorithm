#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

/**
 * 380: O(1) 时间插入、删除和获取随机元素
 * 实现RandomizedSet 类：
 * - RandomizedSet() 初始化 RandomizedSet 对象
 * - bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true
 * ；否则，返回 false 。
 * - bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true
 * ；否则，返回 false 。
 * - int getRandom()
 * 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有
 * 相同的概率 被返回。
 * - 你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。
 * https://leetcode.cn/problems/insert-delete-getrandom-o1/description/
 */
class RandomizedSet {
   private:
    // 用两个集合存储数据
    // 数组用来随机访问
    vector<int> array;
    // map 存储 key:值，value数组 index
    unordered_map<int, int> map;

   public:
    RandomizedSet() {}

    bool insert(int val) {
        if (map.find(val) == map.end()) {
            // 不存在 插入
            array.push_back(val);
            map[val] = array.size() - 1;
            return true;
        }
        // 已存在 返回false
        return false;
    }

    bool remove(int val) {
        if (map.find(val) != map.end()) {
            // 数组中删除，用数组最后一项与index处交换后 删除数组最后一位
            int index = map[val];
            // 交换当前要删除 和 数组最后一位
            swap(array[index], array[array.size() - 1]);
            // 更新map中最后一位的新index
            map[array[index]] = index;
            // 交换后数组删除最后一位
            array.pop_back();
            // map 移除
            map.erase(val);
            return true;
        }
        // 已存在 返回false
        return false;
    }

    int getRandom() {
        // // 在数组中随机找一位
        // random_device rd;
        // mt19937 gen(rd());
        // // 闭区间 [start, end]
        // uniform_int_distribution dis(0, (int)array.size() - 1);
        int random = rand() % array.size();
        // int random = dis(gen);
        return array[random];
    }
};

int main() {
    RandomizedSet* s = new RandomizedSet;
    // cout << s->insert(1) << endl;
    // cout << s->remove(2) << endl;
    // cout << s->insert(2) << endl;
    // cout << s->getRandom() << endl;
    // cout << s->remove(1) << endl;
    // cout << s->insert(2) << endl;
    // cout << s->getRandom() << endl;

    cout << s->insert(0) << endl;
    cout << s->insert(1) << endl;
    cout << s->remove(0) << endl;
    cout << s->insert(2) << endl;
    cout << s->remove(1) << endl;
    cout << s->getRandom() << endl;
}