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
  q -> arr[q -> end] = num;
}

void pop(queue *q){
  q -> start++;
}

signed main(){
  int time[200000];
  int cus[200000] = {0};
  int n, q, num = 1, t = 1;
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    scanf("%d", &time[i]);
  }
  scanf("%d", &q);
  while(num <= q){
    for(int i = 0; i < n; i++){
      if(num > q) break;
      if(t % time[i] == 0 || cus[i] == 0){
        cus[i] = num++;
      }
      printf("Cashier %lld is checking out Customer %lld\n", i + 1, cus[i]);
    }
    for(int i = 0; i < n; i++){
      if(cus[i] == 0) continue;
      printf("Cashier %lld is checking out Customer %lld\n", i + 1, cus[i]);
      if(t % time[i] == 0){
        printf("Cashier %lld has finished checking out for Customer %lld\n", i + 1, cus[i]);
        cus[i] = 0;
      }
    }
    t++;
  }
  return 0;
}