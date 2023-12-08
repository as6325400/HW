#include<stdio.h>
#define int long long

char word[1000000];



signed main(){
  int count = 0;
  while(scanf("%s", word) != EOF){
    count++;
  }
  printf("%lld\n", count);
}