#include<stdio.h>
#include<stdlib.h>

struct node{
  struct node *prev;
  struct node *next;
  int num;
}typedef node;

struct list{
  struct node *start;
  struct node *end;
  int len;
}typedef list;

list *init_list(list *li){
  li = (list*)malloc(sizeof(list));
  li -> start = NULL;
  li -> end = NULL;
  li -> len = 0;
  return li;
}

list *insert(list *li, int site, int num){
  node *newnode = (node*)malloc(sizeof(node));
  newnode -> prev = NULL;
  newnode -> next = NULL;
  newnode -> num = num;
  if(site == 0){
    if(num == 0){
      newnode -> next = li -> start;
      if(li -> start != NULL) li -> start -> prev = newnode;
      else li -> end = newnode;
      li -> start = newnode;
    }
    // 第一個 且非0(非初始化插入)
    else{
      // 只有一個數字
      if(li -> start != NULL){
        if(li -> start -> num == num){
          li -> start = li -> start -> next;
          li -> len -= 2;
        }
        else
        {
          newnode -> next = li -> start;
          li -> start -> prev = newnode;
          li -> start = newnode;
        }
        
      }
      else{
        li -> start = newnode;
        li -> end = newnode;
      }
    }
  }
  else if(site == li ->len){
    if(li -> end -> num == num)
    {
      li -> end = li -> end -> prev;
      li -> end -> next = NULL;
      li -> len -= 2;
    }
    else{
      li -> end -> next = newnode;
      newnode -> prev = li -> end;
      li -> end = newnode;
    }
  }
  else{
    int count = 0;
    node *ptr = li -> start;
    while(count < site - 1){
      ptr = ptr -> next;
      count++;
    }
    if(ptr -> num != num && ptr -> next -> num != num){
      newnode -> next = ptr -> next;
      ptr -> next -> prev = newnode;
      ptr -> next = newnode;
      newnode -> prev = ptr;
    }
    else if(ptr -> num == num && ptr -> next -> num == num)
    {
      ptr -> prev -> next = ptr -> next -> next;
      ptr -> next -> next -> prev = ptr -> prev;
      li -> len -= 3;
    }
    else if(ptr -> num == num)
    {
      if(ptr -> prev != NULL) ptr -> prev -> next = ptr -> next;
      else li -> start = ptr -> next;
      ptr -> next -> prev = ptr -> prev;
      li -> len -= 2;
    }
    else if(ptr -> next -> num == num)
    {
      ptr -> next = ptr -> next -> next;
      if(ptr -> next != NULL) ptr -> next -> prev = ptr;
      else li -> end = ptr;
      li -> len -= 2;
    }
  }
  li -> len++;
  return li;
}

int main(){
  int n;
  scanf("%d", &n);
  list *li = NULL;
  li = init_list(li);
  for(int i = 0; i < n; i++){
    li = insert(li, 0, 0);
  }
  int t, v;
  while(scanf("%d %d", &t, &v) != EOF){
    li = insert(li, t, v);
    node *ptr = li -> start;
  }
  node *ptr = li -> start;
  while(ptr)
  {
    printf("%d ", ptr -> num);
    ptr = ptr -> next;
  }
  printf("\n");

}