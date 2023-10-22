#include<stdio.h>
#include<stdlib.h>
#define int long long

struct queue{
  int arr[10000];
  int start;
  int end;
}typedef queue;


void init(queue *q){
  q -> start = 0;
  q -> end = 0;
}

void push(queue *q, int num){
  q -> end++;
  q -> arr[q -> end - 1] = num;
}

void pop(queue *q){
  q -> start++;
}

int front(queue *q){
  if(q -> end <= q -> start) return 0;
  return q -> arr[q -> start];
}

int size(queue *q){
  return q -> end - q -> start;
}

int time[200000];
int cus[200000] = {0};

signed main(){
  int n, m, num = 1, t = 1, count = 0;
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    scanf("%d", &time[i]);
  }
  scanf("%d", &m);
  queue q;
  init(&q);
  for(int i = 1; i <= m; i++)
  {
    push(&q, i);
  }
  while(count < m){
    for(int i = 0; i < n; i++){
      if(cus[i] == 0){
        cus[i] = front(&q);
        pop(&q);
      }
      if(cus[i] != 0) printf("Cashier %lld is checking out Customer %lld\n", i + 1, cus[i]);
      if(t % (time[i] + 1) == 0 && cus[i] != 0){
        printf("Cashier %lld has finished checking out for Customer %lld\n", i + 1, cus[i]);
        cus[i] = 0;
        count++;
      }
    }
    t++;
  }
  return 0;
}