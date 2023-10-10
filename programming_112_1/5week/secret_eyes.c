#include<stdio.h>
#define int long long

void solve(){
  int num;
  scanf("%lld", &num);
  if(num == 1){
    printf("NO\n");
    return;
  }
  for(int i = 2; i * i <= num; i++){
    if(num % i == 0){
      printf("NO\n");
      return;
    }
  }
  printf("YES\n");
}

signed main(){
  int tt;
  scanf("%lld", &tt);
  while(tt--){
    solve();
  }
}