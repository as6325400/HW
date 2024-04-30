#include<stdio.h>
#include<stdlib.h>
#define int long long

int *arr;

int num(int n){
  int ans = 1;
  ans <<= n;
  return ans - 1;
}

int max(int a, int b){
  return a > b ? a : b;
}

int dfs(int root, int bound){
  if(root > bound) return 0;
  return max(arr[root], dfs(root * 2 + 1, bound) + dfs(root * 2 + 2, bound));
}

signed main(){
  int n;
  scanf("%lld", &n);
  n = num(n);
  arr = (int*)malloc(sizeof(int)*n);
  for(int i = 0; i < n; i++){
    scanf("%lld", &arr[i]);
  }
  printf("%lld", dfs(0, n - 1));
}