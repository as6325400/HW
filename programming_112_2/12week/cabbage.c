#include<stdio.h>
#include<stdlib.h>
// #define int long long

struct vector{
  int *arr;
  int size;
  int capacity;
}typedef vector;

vector *new_vector(){
  vector *v = (vector*)malloc(sizeof(vector));
  v->size = 0;
  v->capacity = 32;
  v->arr = (int*)malloc(sizeof(int) * v->capacity);
  return v;
}

void push_back(vector *v, int val){
  if(v->size == v->capacity){
    v->capacity *= 2;
    v->arr = (int*)realloc(v->arr, sizeof(int) * v->capacity);
  }
  v->arr[v->size++] = val;
}

int size(vector *v){
  return v->size;
}

int arr[100005];
int s = 0;

void dfs(int u, vector **graph, int *visited){
  visited[u] = 1;
  arr[s++] = u;
  for(int i = 0; i < size(graph[u]); i++){
    int v = graph[u]->arr[i];
    if(visited[v] == 0){
      dfs(v, graph, visited);
    }
  }
}

int compare(const void *a, const void *b){
  int va = *((int*)a);
  int vb = *((int*)b);
  return (int)(va - vb);
}

signed main(){
  int n, e;
  scanf("%d %d", &n, &e);
  vector **graph = (vector**)malloc(sizeof(vector*) * (n + 1));
  for(int i = 0; i < n; i++){
    graph[i] = new_vector();
  }
  for(int i = 0; i < e; i++){
    int u, v;
    scanf("%d %d", &u, &v);
    push_back(graph[v], u);
  }
  dfs(0, graph, (int*)calloc(n + 1, sizeof(int)));
  qsort(arr, s, sizeof(int), compare);
  for(int i = 0; i < s; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}