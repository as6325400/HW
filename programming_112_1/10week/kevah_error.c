#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

signed main(){
  int idx = 0;
  char word[105][25];

  while(scanf("%s", word[idx++]) != EOF){}

  idx--;

  for(int i = 0; i < idx - 2; i++){
    if(strcmp(word[i], word[idx - 2]) == 0) printf("%s ", word[idx - 1]);
    else printf("%s ", word[i]);
  }

  printf("\n");
  return 0;
}