#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
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

bool search(int num, node *root){
  while(root){
    if(root -> num == num) return true;
    root = root -> next;
  }
  return false;
}

bool update(int num, int target, node **root){
  node *temp = *root;
  while(temp){
    if(temp -> num == num){
      temp -> num = target;
      return true;
    }
    temp = temp -> next;
  }
  return false;
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
    else if(strcmp(operation, "append") == 0){
      int num;
      scanf("%lld", &num);
      printf("APPEND_SUCC\n");
      append(num, &root);
    }
    else if(strcmp(operation, "search") == 0){
      int num;
      scanf("%lld", &num);
      bool ans = search(num, root);
      if(ans) printf("SEARCH_SUCC\n");
      else printf("SEARCH_FAIL\n");
    }
    else if(strcmp(operation, "update") == 0){
      int num, target;
      scanf("%lld%lld", &num, &target);
      bool ans = update(num, target, &root);
      if(ans) printf("UPDATE_SUCC\n");
      else printf("UPDATE_FAIL\n");
    }
  }
  destroy(root);
  return 0;
}