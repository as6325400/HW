#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

int len;

void swap(char *a, char *b){
  char temp = *a;
  *a = *b;
  *b = temp;
}

void dfs(char *word, int n, char *ans){
  if(n == len){
    printf("%s\n", ans);
    return;
  }
  for(int i = 0; i < len; i++){
    if(word[i] != '.'){
      char temp = word[i];
      ans[n] = temp;
      word[i] = '.';
      dfs(word, n + 1, ans);
      word[i] = temp;
    }
  }
  return;
}

signed main(){

  char *word = (char*)calloc(11, sizeof(char));
  char *ans = (char*)calloc(11, sizeof(char));

  scanf("%s", word);
  len = strlen(word);

  for(int i = 0; i < len; i++){
    for(int j = 0; j < len - i - 1; j++){
      if(word[j] > word[j + 1]) swap(&word[j], &word[j + 1]);
    }
  }


  dfs(word, 0, ans);

  return 0;
}