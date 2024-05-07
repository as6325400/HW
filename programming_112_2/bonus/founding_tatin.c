#include <stdio.h>

#define MAX_NODES 105

int reachable[MAX_NODES][MAX_NODES];

void floydWarshall(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (reachable[i][k] && reachable[k][j]) {
                    reachable[i][j] = 1;
                }
            }
        }
    }
}

int main() {
    int n, e, q;
    int u, v;

    // 輸入點的數量和邊的數量
    scanf("%d %d %d", &n, &e, &q);

    // 初始化 reachable 矩陣
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            reachable[i][j] = (i == j);  // 每個點到自己是可達的
        }
    }

    // 讀取邊並更新矩陣
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        reachable[u][v] = 1;
    }

    // 執行 Floyd-Warshall 算法
    floydWarshall(n);

    // 輸出結果
    for (int i = 0; i < q; i++) {
        int qry;
        scanf("%d", &qry);
        for (int j = 0; j < n; j++) {
            if (reachable[qry][j] && reachable[j][qry]) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }

    return 0;
}
