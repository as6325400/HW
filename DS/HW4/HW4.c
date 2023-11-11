#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define int long long

double haversine(double lat1, double lon1, double lat2, double lon2)
{
  // distance between latitudes
  // and longitudes
  double dLat = (lat2 - lat1) * M_PI / 180.0;
  double dLon = (lon2 - lon1) * M_PI / 180.0;

  // convert to radians
  lat1 = (lat1) * M_PI / 180.0;
  lat2 = (lat2) * M_PI / 180.0;

  // apply formulae
  double a = pow(sin(dLat / 2), 2) + 
              pow(sin(dLon / 2), 2) * 
              cos(lat1) * cos(lat2);
  double rad = 6371;
  double c = 2 * asin(sqrt(a));
  return rad * c;
}

// tree node
struct node{
  double distance;
  char *name;
  struct node *left;
  struct node *right;
}typedef node;


// bst insert 
void insert(node **root, char *name, double distance){
  node *n = (node*)malloc(sizeof(node));
  n -> name = name;
  n -> distance = distance;
  n -> left = NULL;
  n -> right = NULL;
  if(*root == NULL){
    *root = n;
    return;
  }
  node *temp = *root, *save;
  while(temp){
    save = temp;
    if(temp -> distance > n -> distance) temp = temp -> left;
    else temp = temp -> right;
  }
  if(save -> distance > n -> distance) save -> left = n;
  else save -> right = n;
}


// dfs preorder traversal
void dfs(node *root){
  if(!root) return;
  printf("%s\n", root -> name);
  dfs(root -> left);
  dfs(root -> right);
}


// make a queue to bfs
struct queue{
  node *save[100000];
  int start;
  int end;
}typedef queue;


// init queue
void init(queue *q){
  q -> start = 0;
  q -> end = -1;
} 


// push data to queue
void push(queue *q, node *n){
  q -> end++;
  q -> save[q -> end] = n;
}


// find minimun node in bst and printf data on path
node *minimun(node *root){
  if(!root) return NULL;
  printf("%s\n", root -> name);
  if(root -> left) return minimun(root -> left);
  return root;
}

// pop data from queue
node* pop(queue *q){
  if(q -> end < q -> start) return NULL;
  q -> start++;
  return q -> save[q -> start - 1];
}


// return queuesize
int qsize(queue *q){
  return q -> end - q -> start + 1;
}


signed main(){
  int num;
  scanf("%lld", &num);
  double x, y;
  node *root = NULL;
  scanf("%lf %lf", &x, &y);
  for(int i = 0; i < num; i++){
    double x1, y1;
    char *name = (char*)calloc(1000, sizeof(char));
    scanf("%s %lf %lf", name, &x1, &y1);
    insert(&root, name, haversine(x, y, x1, y1));
  }
  printf("DFS:\n");
  dfs(root);
  printf("\n");

  printf("BFS:\n");
  queue *q = (queue*)malloc(sizeof(queue));
  init(q);
  push(q, root);
  while(qsize(q) != 0){
    node *t = pop(q);
    printf("%s\n", t -> name);
    if(t -> left) push(q, t -> left);
    if(t -> right) push(q, t -> right);
  }
  printf("\n");

  printf("Path from Root to Minimum Node:\n");
  node *save = minimun(root);
  printf("\n");
  
  printf("Nearest Treasure Found:\n");
  printf("%s(Distance:%.1f)\n", save -> name, save -> distance);
  return 0;
}