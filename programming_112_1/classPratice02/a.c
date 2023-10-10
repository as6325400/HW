#include<stdio.h>
#define int long long

int grade[5] = { 0 };

signed main(){

  int g;
  while(1)
  {
    scanf("%lld", &g);
    if(g == -1) break;
    if(g < 60) grade[0]++;
    else if(g >= 60 && g < 70) grade[1]++;
    else if(g >= 70 && g < 80) grade[2]++;
    else if(g >= 80 && g < 90) grade[3]++;
    else if(g >= 90 && g <= 100) grade[4]++;
  }

  for(int i = 4; i >= 0; i--){
    printf("%d ", grade[i]);
  }
  printf("\n");
  
}