#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

char word[1000005];
char word1[1000005];

int check(){
  
  int len = strlen(word), count = 0, index = 0;
  word1[0] = word[0];

  for(int i = 1; i < len; i++){
    // printf("%d %d %s %s", i, index, word, word1);
    if(!isalpha(word[i]) && !isalpha(word1[index])){
      // printf("flag\n");
      if(word[i] == '\'' && word1[index] == '\'') word1[index] = '&';
    }
    else{
      word1[++index] = word[i];
      // printf("\n");
    }
  }

  if(word1[0] == '\'') word1[0] = '&';
  if(word1[index] == '\'') word1[index] = '&';

  for(int i = 1; i <= index; i++){
    if(!isalpha(word1[i]) && isalpha(word1[i - 1]) && word1[i] != '\'') count++;
  }
  count += isalpha(word1[index]) ? 1 : 0; 
  // printf("%s %d\n", word1, count);
  return count;
}

signed main(){
  int count = 0;
  while(scanf("%s", word) != EOF){
    count += check();
  }
  printf("%d\n", count);
}