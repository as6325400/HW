#include<stdio.h>
#include<stdlib.h>
#define int long long

char s[7];

signed main(){
  int num = 0;
  for(int i = 0; i < 5; i++){
    scanf("%c", &s[i]);
  }
  scanf("%lld", &num);
  num = num % 26;
  for(int i = 0; i < 5; i++){
    s[i] = ((s[i] - 'A' + num) % 26 + 'A'); 
  }
  printf("%s\n", s);
  return 0;
}
