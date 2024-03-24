/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define int long long

const int maxn = 1e6 + 5;

typedef struct {
  int mode;
  int *heap;
  int size;
} priority_queue;



void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

bool cmp(priority_queue *pq, int par, int child){
  return (pq->mode == 1 ? pq->heap[par] <= pq->heap[child] : pq->heap[par] >= pq->heap[child]);
}

void par_to_child_heapify(priority_queue *pq, int par){
  int lc = par * 2 + 1, rc = par * 2 + 2, tar = par;
  if(lc < pq->size) tar = cmp(pq, tar, lc) ? tar : lc;
  if(rc < pq->size) tar = cmp(pq, tar, rc) ? tar : rc;
  if(tar == par) return;
  swap(pq->heap + par, pq->heap + tar);
  par_to_child_heapify(pq, tar);
}

int pop(priority_queue *pq){
  if(pq->size == 0) return -1;
  pq->size--;
  swap(pq->heap + 0, pq->heap + pq->size);
  par_to_child_heapify(pq, 0);
  return pq->heap[pq->size];
}

void child_to_par_heapify(priority_queue *pq, int child){
  int par = (child - 1) / 2;
  if(child > 0){
    if(!cmp(pq, par, child)){
      swap(pq->heap + par, pq->heap + child);
      child_to_par_heapify(pq, par);
    }
  }
}

void push(priority_queue *pq, int val){
  pq->heap[pq->size] = val;
  child_to_par_heapify(pq, pq->size++);
}

int top(priority_queue *pq){
  return (pq->size == 0 ? -1 : pq->heap[0]);
}

int size(priority_queue *pq){
  return pq->size;
}

signed main(){
  
  priority_queue min_heap = {1, (int*)malloc(sizeof(int) * maxn), 0};
  int n, ans = 0;
  
  scanf("%lld", &n);
  for(int i = 0; i < n; i++){
    int x;
    scanf("%lld", &x);
    push(&min_heap, x);
  }
  
  
  while(size(&min_heap) >= 2){
    int a = pop(&min_heap);
    int b = pop(&min_heap);
    ans += (a + b);
    push(&min_heap, (a + b));
  }
  
  printf("%lld\n", ans);
}