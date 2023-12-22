#include <algorithm>
#include <iostream>
#include <string>

/*
2.给定一个只包含’{’和’}’的字符串，找出最长有效（格式正确且连续）花括号字串的长度（20分）
示例：
输入：str = “}}{}}{}{}” 输出：4，解释：最长子串是{}{}
    }      }      {      }      }     {     }      {        }
l   0      0      1      1      0     1     1      2       2
r   0      0      0      1      0     0     1      1        2
res 0      0      0      2       2    2     2     2         4
*/

int slove(std::string s) {
    int l { 0 };
    int r { 0 };

    int res {};

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '{') {
            ++l;
        }
        if (s[i] == '}') {
            ++r;
        }
        if (l < r) {
            l = r = 0;
        }
        if (l == r) {
            res = std::max(l * 2, res);
        }
    }

    std::reverse(std::begin(s), std::end(s));

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '{') {
            ++l;
        }
        if (s[i] == '}') {
            ++r;
        }
        if (l < r) {
            l = r = 0;
        }
        if (l == r) {
            res = std::max(l * 2, res);
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    std::string input { "{}{}{}{}{}{}" };
    std::cout << slove(input) << std::endl;
    return 0;
}
