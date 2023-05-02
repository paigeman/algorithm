#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    // the number of cases
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        // the number of bones
        int N;
        // the volume of the bag
        int V;
        // the K we need
        int K;
        scanf("%d %d %d", &N, &V, &K);
        // value of each bone
        int * value = (int *) malloc(N * sizeof(int));
        // volume of each bone
        int * volume = (int *) malloc(N * sizeof(int));
        // dp
        int (* dp) [K] = (int (*) [K]) malloc((V + 1) * K * sizeof(int));
        // 初始化dp
        for (int j = 0; j <= V; ++j) {
            for (int k = 0; k < K; ++k) {
                *(*(dp + j) + k) = 0;
            }
        }
        // 处理输入
        for (int j = 0; j < N; ++j) {
            scanf("%d", value + j);
        }
        for (int j = 0; j < N; ++j) {
            scanf("%d", volume + j);
        }
        for (int j = 0; j < N; ++j) {
            for (int k = V; k >= volume[j]; --k) {
                int * tnt = (int *) malloc(K * sizeof(int));
                memcpy(tnt, *(dp + k), K * sizeof(int));
                // 双指针合并
                int l = 0, m = 0, n = 0;
                while (l < K && m < K && n < K) {
                    int nt = *(tnt + l);
                    int t = *(*(dp + k - volume[j]) + m) + value[j];
                    if (nt > t) {
                        if (!n || nt != *(*(dp + k) + n - 1)) {
                            *(*(dp + k) + n++) = nt;
                        }
                        ++l;
                    } else {
                        if (!n || t != *(*(dp + k) + n - 1)) {
                            *(*(dp + k) + n++) = t;
                        }
                        ++m;
                    }
                }
                while (l < K && n < K) {
                    if (!n || *(tnt + l) != *(*(dp + k) + n - 1)) {
                        *(*(dp + k) + n++) = *(tnt + l);
                    }
                    ++l;
                }
                while (m < K && n < K) {
                    int t = *(*(dp + k - volume[j]) + m) + value[j];
                    if (!n || t != *(*(dp + k) + n - 1)) {
                        *(*(dp + k) + n++) = t;
                    }
                    ++m;
                }
                free(tnt);
            }
        }
        printf("%d\n", *(*(dp + V) + K - 1));
        free(dp);
        free(volume);
        free(value);
    }
}