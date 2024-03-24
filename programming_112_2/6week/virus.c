/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char graph[1005][1005];
int table[1005][1005];
int direc[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

struct node{
  int x, y;
  struct node *next;
}typedef node;

struct queue{
  node *front;
  node *back;
  int len;
}typedef queue;

queue *init_queue(){
  queue *q = (queue*)malloc(sizeof(queue));
  q -> front = NULL;
  q -> back = NULL;
  q -> len = 0;
  return q;
}

void push(queue *q, int x, int y) {
  node *new_node = (node*)malloc(sizeof(node));
  new_node->x = x;
  new_node->y = y;
  new_node->next = NULL;
  
  if (q->back == NULL) { 
    q->front = q->back = new_node;
  } else {
    q->back->next = new_node;
    q->back = new_node;
  }
  q->len++;
}


void pop(queue *q) {
  if (q->front == NULL) { 
    return;
  }
  node *temp = q->front;
  q->front = q->front->next;
  
  if (q->front == NULL) { 
    q->back = NULL;
  }
  
  q->len--;
}


int size(queue *q) {
  return q->len;
}


node *front(queue *q) {
  if (q->front == NULL) {
    return NULL; 
  }
  return q->front;
}

bool go(char c){
  if(c == '.') return true;
  return false;
}

int main()
{
  int n, m, count = 0;
  queue *q = init_queue();
  scanf("%d %d", &n, &m);
  
  for(int i = 0; i < 1005; i++)
    for(int j = 0; j < 1005; j++)
      graph[i][j] = '#';
      
  
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      scanf(" %c", &graph[i][j]);
      if(graph[i][j] != '#' && graph[i][j] != '.'){
        table[i][j] = ++count;
        push(q, i, j);
      }
    }
  }
  
  int time = 0;
  
  while(size(q) != 0){
    int len = size(q);
    bool now_graph[1005][1005];
    for(int i = 0; i < 1005; i++)
      for(int j = 0; j < 1005; j++)
        now_graph[i][j] = false;
    
    for(int i = 0; i < len; i++){
      node *nn = front(q);
      pop(q);
      int x = nn -> x, y = nn -> y;
      for(int j = 0; j < 4; j++){
        int nx = x + direc[j][0];
        int ny = y + direc[j][1];
        if(go(graph[nx][ny])){
          graph[nx][ny] = graph[x][y];
          table[nx][ny] = table[x][y];
          now_graph[nx][ny] = true;
          push(q, nx, ny);
        }
        else{
          if(graph[nx][ny] != '#' && graph[nx][ny] != '+' && table[nx][ny] != table[x][y] && now_graph[nx][ny] == true)
          { 
            graph[nx][ny] = '+';
            table[nx][ny] = -1;
            push(q, nx, ny);
          }
        }
      }
    }
    time++;
  }
  

  printf("%d\n", time - 1 == -1 ? 0 : time - 1);
  for(int q = 1; q <= n; q++){
    for(int k = 1; k <= m; k++){
      printf("%c", graph[q][k]);
    }
    printf("\n");
  }
  
  return 0;
}
