#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

char graph[1000][1000];

struct stack{ 
  int index;
  int arr[10000][2];
}typedef stack;

void init(stack *s){
  s -> index = 0;
}

void push(stack *s, int num1, int num2){
  s -> arr[s -> index][0] = num1;
  s -> arr[s -> index][1] = num2;
  s -> index++;
}

void pop(stack *s){
  s -> index--;
}

int topx(stack *s){
  return s -> arr[s -> index - 1][0];
}

int topy(stack *s){
  return s -> arr[s -> index - 1][1];
}

int size(stack *s){
  return s -> index;
}

signed main(){
  int n, m;
  int startx, starty;
  char path[10000];
  for(int i = 0; i < 1000; i++){
    for(int j = 0; j < 1000; j++){
      graph[i][j] = '1';
    }
  }
  scanf("%lld%lld", &n, &m);
  // printf("%d %d\n", n, m);
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      scanf(" %c", &graph[i][j]);
      // printf("%d %d\n", i, j);
      if(graph[i][j] == 'P'){
        startx = i;
        starty = j;
      }
    } 
  }
  scanf("%s", path);
  int num = strlen(path);
  stack s;
  init(&s);
  push(&s, startx, starty);
  for(int i = 0; i < num; i++){
    int nextx = startx, nexty = starty;
    if(path[i] == 'w' || path[i] == 'W') nextx = startx - 1;
    if(path[i] == 'a' || path[i] == 'A') nexty = starty - 1;
    if(path[i] == 's' || path[i] == 'S') nextx = startx + 1;
    if(path[i] == 'd' || path[i] == 'D') nexty = starty + 1;
    if(path[i] == 'b' || path[i] == 'B'){
      if(size(&s) == 0) continue;
      startx = topx(&s);
      starty = topy(&s);
      pop(&s);
      continue;
    }
    // printf("%d %d %d\n", i, nextx, nexty);
    if(graph[nextx][nexty] == 'E'){
      printf("Congratulations! You reached the endpoint.\n");
      return 0;
    }
    if(graph[nextx][nexty] == 'X'){
      printf("Game over. You collided with the obstacle!\n");
      return 0;
    }
    if(graph[nextx][nexty] == '1') continue;
    push(&s, nextx, nexty);
    startx = nextx;
    starty = nexty;
  }
  printf("Game over. You collided with the obstacle!\n");
  return 0;
}