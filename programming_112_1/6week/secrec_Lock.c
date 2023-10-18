#include<stdio.h>
#include<stdlib.h>
#define int long long

int num(int n){
  if(n == 1) return 1;
  return 2 * num(n - 1) + 1;
}

signed main(){
  int n;
  scanf("%lld", &n);
  printf("Moved : %lld\n", num(n));
  return 0;
}