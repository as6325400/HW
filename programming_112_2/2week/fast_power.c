#include<stdio.h>
#define int long long
#define mod 1000000007

int fp(int x, int y, int p){
  int res = 1;
  while(y != 0){
    if(y % 2 == 1){
      res *= x;
      res %= p;
    }
    x *= x;
    y /= 2;
    x %= p;
  }
  return res;
}

signed main(){
  int n, m;
  while(scanf("%lld%lld", &n, &m) != EOF){
    printf("%lld\n", fp(n, m, mod));
  }
}