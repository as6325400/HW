#include<stdio.h>
#define int long long

int graph[1005][1005];
int kernal[1005][1005];

signed main(){
  int n, m;
  scanf("%lld %lld", &n, &m);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf("%lld", &graph[i][j]);
    }
  }

  for(int i = 0; i < m; i++){
    for(int j = 0; j < m; j++){
      scanf("%lld", &kernal[i][j]);
    }
  }

  for(int i = 0; i + m <= n; i++){
    for(int j = 0; j + m <= n; j++){
      int num = 0;
      for(int k = 0; k < m; k++){
        for(int q = 0; q < m; q++){
          num += kernal[k][q] * graph[i + k][j + q];
        }
      }
      printf("%lld ", num);
    }
    printf("\n");
  }
}