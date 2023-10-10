#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define int long long

bool judge(int num){
  int arr[10000] = {0};
  int temp = num;
  while(1){
    int nt = 0;
    arr[temp]++;
    if(arr[temp] > 1) return false;
    while(temp != 0){
      nt += (temp % 10) * (temp % 10);
      temp /= 10;
    }
    temp = nt;
    if(temp == 1) return true;
    if(temp == num) return false;
  }
}

signed main(){
  int h, m;
  scanf("%lld%lld", &h, &m);
  if(judge(h) && judge(m)) printf("Happy Birthday!\n");
  else printf("Not now\n");
  return 0;
}