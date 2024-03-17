#include<stdio.h>
#include<stdlib.h>
#define int long long

struct node{
  struct node *prev;
  struct node *next;
  int val;
}typedef node;

struct list{
  struct node *start;
  struct node *end;
  int num;
}typedef list;

list* init_list(list *li)
{
  li = (list*)malloc(sizeof(list));
  li -> start = NULL;
  li -> end = NULL;
  li -> num = 0;
  return li;
}

list* insert(list *li, int num){
  node *newnode = (node*)malloc(sizeof(node));
  newnode -> prev = NULL;
  newnode -> next = NULL;
  newnode -> val = num;
  if(li -> num == 0){
    li -> start = newnode;
    li -> end = newnode;
  }
  else{
    li -> end -> next = newnode;
    newnode -> prev = li -> end;
    li -> end = newnode;
  }
  li -> num++;
  return li;
}

int left(list *li, int id, int range, int dis){
  int count = 0;
  node *ptr = li -> start;
  while(count < dis + 1){
    if(ptr -> val >= (id - range) && ptr -> val <= (id + range) && ptr -> val != id){
      return count;
    }
    ptr = ptr -> prev;
    count++;
  }
  return (int)1e9;
}

int right(list *li, int id, int range, int dis){
  int count = 0;
  node *ptr = li -> start;
  while(count < dis + 1){
    if(ptr -> val >= (id - range) && ptr -> val <= (id + range) && ptr -> val != id){
      return count;
    }
    ptr = ptr -> next;
    count++;
  }
  return (int)1e9;
}

list *find(list *li, int id, int *check){
  node *ptr = li -> start;
  for(int i = 0; i < 200005; i++){
    if(id == ptr -> val){
      li -> start = ptr;
      *check = 1;
      return li;
    }
    ptr = ptr -> next;
  }
  return li;
}

list *remove_left(list *li, int dis){
  int count = 0;
  node *ptr = li -> start;
  while(count < dis - 1)
  { 
    ptr = ptr -> prev;
    count++;
  }
  ptr -> prev = ptr -> prev -> prev;
  ptr -> prev -> next = ptr;
  ptr = li -> start;
  // printf("-----------------------------\n");
  // for(int i = 0; i < li -> num; i++){
  //   printf("%lld ", ptr -> val);
  //   ptr = ptr -> next;
  // }
  // printf("\n");
  // printf("-----------------------------\n");
  ptr = li -> start;
  ptr -> next -> prev = ptr -> prev;
  ptr -> prev -> next = ptr -> next;
  // printf("debug %lld %lld %lld\n", ptr -> val, ptr -> prev -> val, ptr -> next -> val);
  li -> start = ptr -> prev;
  ptr = li -> start;
  // printf("-----------------------------\n");
  // for(int i = 0; i < li -> num; i++){
  //   printf("%lld ", ptr -> val);
  //   ptr = ptr -> next;
  // }
  // printf("\n");
  // printf("-----------------------------\n");
  li -> num -= 2;
  return li;
}

list *remove_right(list *li, int dis){
  // printf("dis %lld\n", dis);
  int count = 0;
  node *ptr = li -> start;
  while(count < dis - 1)
  { 
    ptr = ptr -> next;
    count++;
  }
  ptr -> next = ptr -> next -> next;
  ptr -> next -> prev = ptr;
  ptr = li -> start;
  // printf("-----------------------------\n");
  // for(int i = 0; i < li -> num; i++){
  //   printf("%lld ", ptr -> val);
  //   ptr = ptr -> next;
  // }
  // printf("\n");
  // printf("-----------------------------\n");
  ptr -> next -> prev = ptr -> prev;
  ptr -> prev -> next = ptr -> next;
  li -> start = ptr -> prev;
  ptr = li -> start;
  li -> num -= 2;
  return li;
}

signed main(){
  int n;
  list *li = NULL;
  li = init_list(li);
  int arr[200005];
  scanf("%lld", &n);
  for(int i = 0; i < n; i++){
    int num;
    scanf("%lld", &num);
    arr[i] = num;
    li = insert(li, num);
  }
  li -> end -> next = li -> start;
  li -> start -> prev = li -> end;
  int id, dis, range;
  while(scanf("%lld %lld %lld", &id, &dis, &range) != EOF){
    int check = 0;
    li = find(li, id, &check);
    // node *ptr = li -> start;
    // for(int i = 0; i < li -> num; i++){
    //   printf("%lld ", ptr -> val);
    //   ptr = ptr -> next;
    // }
    // printf("\n");
    if(check == 0) continue;
    int l = left(li, id, range, dis);
    int r = right(li, id, range, dis);
    if(l == (int)1e9 && r == (int)1e9) continue;
    if(l <= r) li = remove_left(li, l);
    else li = remove_right(li, r);
  }
  if(li -> num == 0) printf("Wonderful\n");
  for(int i = 0; i < n; i++){
    int check = 0;
    li = find(li, arr[i], &check);
    // printf("check %lld\n", check);
    if(check == 1){
      // printf("%lld\n", li -> start -> val);
      break;
    }
  }
  node *ptr = li -> start;
  for(int i = 0; i < li -> num; i++){
    printf("%lld ", ptr -> val);
    ptr = ptr -> next;
  }
  printf("\n");
}