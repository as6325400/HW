#include<stdio.h>
#include<string.h>
#define int long long

char s1[100005];
char s2[100005];
char table[26][26];

void createTable(){
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      table[i][j] = ((i + j) % 26) + 'a';
    }
  }
}

char transform(char a, char b){
  if(b < 'a') b += 32;
  if(a >= 'a') return table[a - 'a'][b - 'a'];
  return table[a + 32 - 'a'][b - 'a'] - 32;
}

signed main(){
  scanf("%s %s", s1, s2);
  int len1 = strlen(s1), len2 = strlen(s2);
  createTable();
  for(int i = 0; i < len1; i++){
    printf("%c", transform(s1[i], s2[i % len2]));
  }
  printf("\n");
}