#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


char graph[2005][2005];
char graph1[2005][2005];
char graph2[2005][2005];
char graph4[2005][2005];

void swap(char *a, char *b){
  char temp = *a;
  *a = *b;
  *b = temp;
}

signed main(){

  memset(graph, '#', sizeof(graph));
  memset(graph1, '#', sizeof(graph1));
  memset(graph4, '#', sizeof(graph4));
  
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      scanf(" %c", &graph[i][j]);
    }
  }

  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      int count = 0;
      if(graph[i][j] == '0'){
        if(graph[i - 1][j] == '*') count++;
        if(graph[i + 1][j] == '*') count++;
        if(graph[i][j - 1] == '*') count++;
        if(graph[i][j + 1] == '*') count++;
        if(graph[i - 1][j - 1] == '*') count++;
        if(graph[i + 1][j + 1] == '*') count++;
        if(graph[i + 1][j - 1] == '*') count++;
        if(graph[i - 1][j + 1] == '*') count++;
        graph1[i][j] = (int)'0' + count;
      }
      else{
        graph1[i][j] = graph[i][j];
      }
    }
  }

  for(int i = 1; i <= n; i++){
    for(int j = 1;j <= n; j++){
      printf("%c ", graph1[i][j]);
      graph2[i][j] = graph1[i][j];
    }
    printf("\n");
  }

  printf("\n");

  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      if(graph2[i][j] == '@'){
        swap(&graph2[i - 1][j], &graph2[i][j - 1]);
        swap(&graph2[i - 1][j + 1], &graph2[i + 1][j - 1]);
        swap(&graph2[i + 1][j], &graph2[i][j + 1]);
      }
    }
  }


  for(int i = 1; i <= n; i++){
    for(int j = 1;j <= n; j++){
      printf("%c ", graph2[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      if(isdigit(graph2[i][j])){
        int count = 0;
        if(graph2[i - 1][j] == '*') count++;
        if(graph2[i + 1][j] == '*') count++;
        if(graph2[i][j - 1] == '*') count++;
        if(graph2[i][j + 1] == '*') count++;
        if(graph2[i - 1][j - 1] == '*') count++;
        if(graph2[i + 1][j + 1] == '*') count++;
        if(graph2[i + 1][j - 1] == '*') count++;
        if(graph2[i - 1][j + 1] == '*') count++;
        if((int)'0' + count != (int)graph2[i][j]){
          printf("Wrong\n");
          return 0;
        }
      }
    }
  }

  printf("Correct\n");
  return 0;
}

