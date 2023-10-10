#include<stdio.h>
#include<stdbool.h>
#define int unsigned long long

int reverse(int num){
  int ans = 0;
  while(num > 0){
    ans *= 10;
    ans += (num % 10);
    num /= 10;
  }
  return ans;
}

signed main(){
  int num, count = 0;
  scanf("%llu", &num);
  while(num != reverse(num)){
    count++;
    num += reverse(num);
    if(num > 9223372036854775807){
      printf("Lycherl\n");
      return 0;
    }
  }
  printf("%llu\n", count);
}