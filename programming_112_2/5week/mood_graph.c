/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<stdio.h>
#define int long long

int dpnum[1005][11];
int dpsum[1005];
int arr[1005];

signed main(){
  int n;
  scanf("%lld", &n);
  for(int i = 1; i <= n; i++){
    scanf("%lld", &arr[i]);
  }
  int ans = -1e9, ansidx;
  for(int i = 1; i <= n; i++){
    // i 為峰值狀態
    int M = arr[i], sum = arr[i];
    for(int j = i - 1; j >= 1; j--)
    {
      if(arr[j] > M) sum += M;
      else{
        M = arr[j];
        sum += M;
      }
    }
    M = arr[i];
    for(int j = i + 1; j <= n; j++)
    {
      if(arr[j] > M) sum += M;
      else{
        M = arr[j];
        sum += M;
      }
    }
    if(sum > ans){
      ans = sum;
      ansidx = i;
    }
  }
  printf("%lld\n", ans);
  int M = arr[ansidx];
  for(int j = ansidx - 1; j >= 1; j--)
  {
    if(arr[j] <= M) M = arr[j];
    arr[j] = M;
  }
  M = arr[ansidx];
  for(int j = ansidx + 1; j <= n; j++)
  {
    if(arr[j] <= M) M = arr[j];
    arr[j] = M;
  }
  for(int i = 1; i <= n; i++){
    printf("%lld ", arr[i]);
  }
  printf("\n");
}