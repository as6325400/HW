#include<stdio.h>
#include<string.h>
#define int long long

signed main(){
  char c;
  while(scanf("%c", &c) != EOF){
    if(c >= '0' && c <= '9') printf("%c", c);
  }
  printf("\n");
}