#include<stdio.h>
#include<stdlib.h>
#define int long long

signed main(){
  int n, ans = 0;
  scanf("%lld", &n);
  for(int i = 0; i < n; i++){
    int num;
    scanf("%lld", &num);
    ans ^= num;
  }
  printf("%lld\n", ans);
  return 0;
}