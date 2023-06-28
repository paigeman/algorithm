//
// Created by fade on 2023/6/25.
//
#include <iostream>
#include <vector>
#include "cstring"
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;
int dfs(const vector<vector<int>> &, int[][3], unsigned long, int, int);
int main()
{
    // 处理输入
    // 一共有几个case
    int cases = 0;
    // 有几种砖
    int nums = 0;
    // 存储砖数据的容器
    vector<vector<vector<int>>> container;
    while (cin >> nums) {
        // 如果输入0或者负数，退出循环
        if (!nums || nums < 0) {
            break;
        }
        ++cases;
        // 一个案例
        vector<vector<int>> ca;
        for (int i = 0; i < nums; ++i) {
            // dimensions
            vector<int> dimensions;
            for (int j = 0; j < 3; ++j) {
                int dimension;
                cin >> dimension;
                dimensions.push_back(dimension);
            }
            ca.push_back(dimensions);
        }
        container.push_back(ca);
    }
    for (int i = 0; i < cases; ++i) {
        const auto kinds = container[i].size();
        int dp[kinds][3];
        // 初始化dp
        memset(dp, -1, kinds * 3 * sizeof(int));
        int ans = dfs(container[i], dp, kinds, 0x7fffffff, 0x7fffffff);
        cout << "Case " << i + 1 << ": maximum height = " << ans << endl;
    }
    return 0;
}
int dfs(const vector<vector<int>> & ca, int dp[][3], unsigned long length, int x, int y) {
    int ans = 0;
    for (int i = 0; i < length; ++i) {
        if ((ca[i][0] < x && ca[i][1] < y) || (ca[i][0] < y && ca[i][1] < x)) {
            if (dp[i][0] == -1) {
                dp[i][0] = max(dp[i][0], dfs(ca, dp, length, ca[i][0], ca[i][1]) + ca[i][2]);
            }
            ans = max(ans, dp[i][0]);
        }
        if ((ca[i][0] < x && ca[i][2] < y) || (ca[i][0] < y && ca[i][2] < x)) {
            if (dp[i][1] == -1) {
                dp[i][1] = max(dp[i][1], dfs(ca, dp, length, ca[i][0], ca[i][2]) + ca[i][1]);
            }
            ans = max(ans, dp[i][1]);
        }
        if ((ca[i][1] < x && ca[i][2] < y) || (ca[i][1] < y && ca[i][2] < x)) {
            if (dp[i][2] == -1) {
                dp[i][2] = max(dp[i][2], dfs(ca, dp, length, ca[i][1], ca[i][2]) + ca[i][0]);
            }
            ans = max(ans, dp[i][2]);
        }
    }
    return ans;
}