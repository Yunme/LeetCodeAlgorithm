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
 * hj18 识别有效的IP地址和掩码并进行分类统计
 * 请解析IP地址和对应的掩码，进行分类识别。要求按照A/B/C/D/E类地址归类，不合法的地址和掩码单独归类。
 * 所有的IP地址划分为 A,B,C,D,E五类
 * A类地址从1.0.0.0到126.255.255.255;
 * B类地址从128.0.0.0到191.255.255.255;
 * C类地址从192.0.0.0到223.255.255.255;
 * D类地址从224.0.0.0到239.255.255.255；
 * E类地址从240.0.0.0到255.255.255.255
 *
 * 私网IP范围是：
 * 从10.0.0.0到10.255.255.255
 * 从172.16.0.0到172.31.255.255
 * 从192.168.0.0到192.168.255.255
 * 子网掩码为二进制下前面是连续的1，然后全是0。（例如：255.255.255.32就是一个非法的掩码）
 * （注意二进制下全是1或者全是0均为非法子网掩码）
 *
 * 输入：多行字符串。每行一个IP地址和掩码，用~隔开。
 * 输出：统计A、B、C、D、E、错误IP地址或错误掩码、私有IP的个数，之间以空格隔开。
 * https://www.nowcoder.com/practice/de538edd6f7e4bc3a5689723a7435682
 */

/**
 * 字符串按字符分割
 */
vector<string> splitString(string s, char delimiter) {
    vector<string> result;
    int start = 0;
    for (int i = 0; i < s.length(); i++) {
        char a = s[i];
        if (a == delimiter) {
            result.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    result.push_back(s.substr(start, s.length() - start));
    return result;
}
/**
 * 正整数字符串转int，转化失败返回 -1；
 */
int string2int(string &s) {
    if (s.length() == 0) {
        return -1;
    }

    int k = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            k = k * 10 + s[i] - '0';
        } else {
            return -1;
        }
    }
    return k;
}

/**
 * 解析 ip 返回其类型
 * 非法ip. 返回 -1；
 * 0.*.*.* 或 本机地址 127. 忽略；返回0；
 * A类地址从1.0.0.0到126.255.255.255; 返回1；
 * B类地址从128.0.0.0到191.255.255.255; 返回2；
 * C类地址从192.0.0.0到223.255.255.255; 返回3；
 * D类地址从224.0.0.0到239.255.255.255；返回4；
 * E类地址从240.0.0.0到255.255.255.255 返回5；
 *
 * 私网IP范围是：
 * 从10.0.0.0到10.255.255.255  返回10；
 * 从172.16.0.0到172.31.255.255 返回20；
 * 从192.168.0.0到192.168.255.255 返回30；
 *
 * 私有IP地址和A,B,C,D,E类地址是不冲突的 都计数
 */
int validIP(string ip) {
    vector<string> ipPhrase = splitString(ip, '.');
    if (ipPhrase.size() != 4) {
        return -1;
    }
    int type = 0;
    for (int i = 0; i < ipPhrase.size(); i++) {
        string p = ipPhrase[i];
        int phrase = string2int(p);
        if (phrase > 255 || phrase < 0) return -1;
        if (i == 0) {
            if (phrase == 0 || phrase == 127) {
                return 0;
            } else if (phrase > 0 && phrase < 127) {
                type = phrase == 10 ? 10 : 1;
            } else if (phrase >= 128 && phrase < 192) {
                type = 2;
            } else if (phrase >= 192 && phrase < 224) {
                type = 3;
            } else if (phrase >= 224 && phrase < 240) {
                type = 4;
            } else if (phrase >= 240 && phrase < 256) {
                type = 5;
            }
        }
        if (i == 1 && string2int(ipPhrase[i - 1]) == 172) {
            if (phrase >= 16 && phrase < 32) {
                type = 20;
            }
        }
        if (i == 1 && string2int(ipPhrase[i - 1]) == 192) {
            if (phrase == 168) {
                type = 30;
            }
        }
    }
    return type;
}

/**
 * 解析子网掩码，检测是否合法
 * 子网掩码为二进制下前面是连续的1，然后全是0。（例如：255.255.255.32就是一个非法的掩码）
 * （注意二进制下全是1或者全是0均为非法子网掩码）
 * @return 0 非法，1：合法
 */
int validMask(string mask) {
    vector<string> maskPhrase = splitString(mask, '.');
    if (maskPhrase.size() != 4) {
        return -1;
    }
    bool hasAllOne = false;
    bool lastZero = false;
    for (int i = 0; i < maskPhrase.size(); i++) {
        string p = maskPhrase[i];
        int phrase = string2int(p);
        if (phrase < 0 || phrase > 255) {
            return 0;
        }

        // 每段要么是0 要么是全1.
        bool one = (phrase | 255) == phrase;
        if (phrase > 0 && !one) {
            return 0;
        }
        // 最后一段如果还是全1，非法
        if (i == maskPhrase.size() - 1 && one) {
            return 0;
        }

        // 前面无1，当前为0，非法
        if (!hasAllOne && phrase == 0) {
            return 0;
        }
        // 前面是 0，当前为1，非法
        if (lastZero && one) {
            return 0;
        }
        lastZero = phrase == 0;

        if (one) hasAllOne = one;
    }
    // 全1也非法
    return 1;
}

int main() {
    vector<string> ips;
    string s;
    ifstream file("hj18.txt");
    while (getline(file, s)) {
        ips.push_back(s);
    }
    file.close();

    // while (cin >> s) {
    //     ips.push_back(s);
    // }
    //
    // ips.push_back("10.70.44.68~255.254.255.0");
    // ips.push_back("1.0.0.1~255.0.0.0");
    // ips.push_back("192.168.0.2~255.255.255.0");
    // ips.push_back("19..0.~255.255.255.0");
    // ips.push_back("1.0.0.0~255.255.0.0");

    // ips.push_back("0.201.56.50~255.255.111.255");
    // ips.push_back("127.201.56.50~255.255.111.255");

    int aCount = 0, bCount = 0, cCount = 0, dCount = 0, eCount = 0;
    int errorCount = 0, privateCount = 0;
    for (string &s : ips) {
        vector<string> ips = splitString(s, '~');
        string ip = ips[0];
        string mask = ips[1];

        int ipType = validIP(ip);

        int vm = validMask(mask);
        cout << ip << ":" << ipType << "~" << mask << ":" << vm << endl;
        if (ipType == 0) continue;
        if (!vm || ipType == -1) {
            errorCount++;
            continue;
        }
        switch (ipType) {
            case -1:
                break;
            case 1:
                aCount++;
                break;
            case 10:
                aCount++;
                privateCount++;
                break;
            case 2:
                bCount++;
                break;
            case 20:
                bCount++;
                privateCount++;
                break;
            case 3:
                cCount++;
                break;
            case 30:
                cCount++;
                privateCount++;
                break;
            case 4:
                dCount++;
                break;
            case 5:
                eCount++;
                break;
            default:
                break;
        }
    }
    cout << aCount << " " << bCount << " " << cCount << " " << dCount << " "
         << eCount << " " << errorCount << " " << privateCount << endl;
    return 0;
}