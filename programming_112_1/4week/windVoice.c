#include <stdio.h>
#define int long long


int max(int a, int b){
  return a > b ? a : b;
}

int choose(int num, int win, int loss){
  int temp = max(win, loss);
  int ans = 1;
  for(int i = num; i > temp; i--){
    ans *= i;
  }
  for(int i = 2; i <= num - temp; i++){
    ans /= i;
  }
  return ans;
}

signed main()
{
  int num, player, win, loss;
  scanf("%lld%lld%lld%lld", &num, &player, &win, &loss);
  int mom = 1, child = 1;
  if(player == 1 || player == 2){
    for(int i = 0; i < num; i++){
      if(i < win) child *= 3;
      else child *= 4;
      mom *= 7;
    }
  }
  else{
    for(int i = 0; i < num; i++){
      if(i < win) child *= 1;
      else child *= 6;
      mom *= 7;
    }
  }
  child *= choose(num, win, loss);
  while(child % 7 == 0 && mom % 7 == 0){
    child /= 7;
    mom /= 7;
  }
  printf("%lld/%lld\n", child, mom);
}