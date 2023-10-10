#include<stdio.h>
#include<stdlib.h>
#define int long long

signed main(){
  int concert, stay, ah, am, lh, lm;
  scanf("%lld%lld%lld%lld%lld%lld", &concert, &stay, &ah, &am, &lh, &lm);
  int start = ah * 60 + am;
  int end = lh * 60 + lm;
  int ans = 0;
  if(end <= start){
    end += 1440;
    ans += stay;
  }
  int dis = (end - start) / 30;
  if(dis <= 4) ans += 30 * dis;
  else if(dis > 4 && dis <= 8) ans += (120 + (dis - 4) * 40);
  else ans += (280 + (dis - 8) * 60);
  printf("%lld\n", ans + concert);
  return 0;
}