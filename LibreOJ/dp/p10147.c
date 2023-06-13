//
// Created by fade on 2023/6/13.
//
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a>b)?(a):(b))
#define min(a,b) ((a>b)?(b):(a))
int main(void)
{
    // n堆石子
    int n;
    scanf("%d", &n);
    // 石子 第i堆和第i+n堆相等
    int * stones = (int *) malloc(2 * n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", stones + i);
        *(stones + i + n) = *(stones + i);
    }
    // 最大得分
    int (* max)[2 * n] = (int (*) [2 * n]) malloc(4 * n * n * sizeof(int));
    // 最小得分
    int (* min)[2 * n] = (int (*) [2 * n]) malloc(4 * n * n * sizeof(int));
    // 初始化dp
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            *(*(max + i) + j) = 0;
            *(*(min + i) + j) = i == j ? 0 : 0x7fffffff;
        }
    }
    // 前缀和数组
    int sums[2 * n];
    // 初始化sums
    for (int i = 0; i < 2 * n; ++i) {
        sums[i] = 0;
    }
    for (int i = 0; i < 2 * n; ++i) {
        if (!i) {
            sums[i] = stones[i];
        } else {
            sums[i] = sums[i - 1] + stones[i];
        }
    }
    // 枚举长度
    for (int i = 1; i <= 2 * n; ++i) {
        // 枚举区间左端点
        for (int j = 0; j <= 2 * n - i; ++j) {
            // 区间右端点
            int right = j + i - 1;
            // 枚举合并点
            // dp[j][k] + dp[k + 1][right]
            for (int k = j; k < right; ++k) {
                max[j][right] = max(max[j][right], max[j][k] + max[k + 1][right] + sums[right] - (j ? sums[j - 1] : 0));
                min[j][right] = min(min[j][right], min[j][k] + min[k + 1][right] + sums[right] - (j ? sums[j - 1] : 0));
            }
        }
    }
    int mi = 0x7fffffff, ma = 0;
    for (int i = 0; i < n; ++i) {
        if (max[i][i + n - 1] > ma) {
            ma = max[i][i + n - 1];
        }
        if (min[i][i + n - 1] < mi) {
            mi = min[i][i + n - 1];
        }
    }
    printf("%d\n", mi);
    printf("%d\n", ma);
    free(min);
    free(max);
    free(stones);
    return 0;
}