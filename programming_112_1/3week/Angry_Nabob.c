#include<stdio.h>
#include<stdlib.h>
#define int long long

signed main(){
  int n, m, count = 0, num = 5;
  scanf("%lld%lld", &n, &m);
  while(num <= n){
    count += n / num;
    num *= 5;
  }
  if(count >= m) printf("NO\n");
  else printf("YES\n");
  return 0;
}