/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int graph[30][30];
int time[30][30];

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

int main()
{
  int n, m, k;
  int x1[2], x2[2];
  int dire[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  
  scanf("%d %d %d", &n, &m, &k);
  scanf("%d %d %d %d", &x1[0], &x1[1], &x2[0], &x2[1]);
  
  for(int i = 0; i < 30; i++)
    for(int j = 0; j < 30; j++)
      graph[i][j] = 1;
      
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      graph[i][j] = 0;
  
  for(int i = 0; i < k; i++){
    int x, y;
    scanf("%d %d", &x, &y);
    graph[++x][++y] = 1;
  }
  
  
  queue *q = init_queue();
  push(q, ++x1[0], ++x1[1]);
  graph[x1[0]][x1[1]] = 1;
  
  while(size(q) != 0){
    node *nn = front(q);
    pop(q);
    int x = nn -> x, y = nn -> y;
    for(int i = 0; i < 4; i++){
      int nx = x + dire[i][0];
      int ny = y + dire[i][1];
      if(graph[nx][ny] == 0){
        graph[nx][ny] = 1;
        time[nx][ny] = time[x][y] + 1;
        push(q, nx, ny);
      }
    }
  }
  
  if(time[x2[0] + 1][x2[1] + 1] == 0) printf("Oops!\n");
  else printf("%d\n", time[x2[0] + 1][x2[1] + 1] / 2);
  
  return 0;
}
