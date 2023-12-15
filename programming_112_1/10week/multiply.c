#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

char word[105];

char *rowAns(){
  int flag = 0, flag2 = 0, len = strlen(word), ans = 1;
  for(int i = 0; i <= len; i++){
    if(word[i] == 'x' || i == len){
      int num = 0, p = 1;
      for(int j = flag2 - 1; j >= flag; j--){
        num += ((word[j] - '0') * p);
        p *= 10;
      }
      ans *= num;
      flag = i + 1;
    }
    flag2++;
  }
  char *strans = malloc(sizeof(char) * 1005);
  sprintf(strans, "%lld", ans);
  // printf("str %s\n", strans);
  return strans;
}

void swap(char *a, char *b){
  char temp = *a;
  *a = *b;
  *b = temp;
}

char *add(char *s1, char *s2){
  char *ans = (char*)malloc(sizeof(char) * 1005);
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  // printf("%lld %lld\n", len1, len2);
  for(int i = len1; i < 1005; i++){
    s1[i] = '0';
  }
  for(int i = len2; i < 1005; i++){
    s2[i] = '0';
  }
  for(int i = 0; i < len1 / 2; i++){
    swap(&s1[i], &s1[len1 - i - 1]);
  }
  for(int i = 0; i < len2 / 2; i++){
    swap(&s2[i], &s2[len2 - i - 1]);
  }

  int carry = 0, len3 = 1;
  for(int i = 0; i < 1005; i++){
    int num1 = s1[i] - '0';
    int num2 = s2[i] - '0';
    ans[i] = (char)(((num1 + num2 + carry) % 10) + (int)'0');
    if(ans[i] != '0') len3 = i + 1;
    carry = (num1 + num2 + carry) / 10;
  }
  for(int i = 0; i < len3 / 2; i++){
    swap(&ans[i], &ans[len3 - i - 1]);
  }
  for(int i = len3; i < 1005; i++){
    ans[i] = '\0';
  }
  // printf("%s\n", ans);
  return ans;
}


signed main(){
  char *ans = (char*)calloc(1005, sizeof(char));
  ans[0] = '0';
  while(scanf("%s", word) != EOF){
    ans = add(ans, rowAns());
  }
  printf("%s\n", ans);
  return 0;
}