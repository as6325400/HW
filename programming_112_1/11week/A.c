#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

struct node{
  int num;
  struct node *next;
}typedef node;

void append(int num, node **root){
  node *newnode = (node*)malloc(sizeof(node));
  newnode -> num = num;
  newnode -> next = NULL;
  node *temp = *root;
  if(!temp){
    *root = newnode;
    return;
  }
  while(temp -> next != NULL){
    temp = temp -> next;
  }
  temp -> next = newnode;
  return;
}

void print(node *root){
  while(root){
    printf("%d ", root -> num);
    root = root -> next;
  }
  printf("\n");
}

void destroy(node *root){
  while(root){
    node *temp = root;
    root = root -> next;
    free(temp);
  }
}

signed main(){
  char operation[25];
  node *root = NULL;
  while(scanf("%s", operation) != EOF){
    if(strcmp(operation, "print") == 0) print(root);
    else{
      int num;
      scanf("%lld", &num);
      printf("APPEND_SUCC\n");
      append(num, &root);
    }
  }
  destroy(root);
  return 0;
}