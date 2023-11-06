#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

struct node{
  char n;
  struct node *next;
}typedef node;

struct list{
  struct node *front;
  struct node *back;
  int len;
}typedef list;

void init(list **ptr){
  list *temp = (list*)malloc(sizeof(list));
  temp -> front = NULL;
  temp -> back = NULL;
  temp -> len = 0;
  *ptr = temp;
}

void push_back(list *ptr, char n){
  node *temp = (node*)malloc(sizeof(node));
  temp -> n = n;
  ptr -> len++;
  temp -> next = NULL;
  if(ptr -> len == 1){
    ptr -> back = temp;
    ptr -> front = ptr -> back;
    return;
  }
  ptr -> back -> next = temp;
  ptr -> back = temp;
  return;
}

void push_front(list *ptr, char n){
  node *temp = (node*)malloc(sizeof(node));
  temp -> n = n;
  ptr -> len++;
  temp -> next = ptr -> front;
  if(ptr -> len == 1){
    ptr -> front = temp;
    ptr -> back = ptr -> front;
    return;
  }
  ptr -> front = temp;
}

int max(int a, int b){
  return a > b ? a : b;
}

int value(char a){
  if(a >= '0' && a <= '9') return a - '0';
  return a - 'A' + 10;
}

char to_char(int a){
  if(a <= 9) return '0' + a;
  return (a - 10) + 'A';
}

node *r(node *ptr, int offset){
  node *ptr_p = NULL, *temp;
  for(int i = 0; i < offset; i++){
    temp = ptr -> next;
    ptr -> next = ptr_p;
    ptr_p = ptr;
    ptr = temp;
  }
  return ptr_p;
}

void reverse(list *li, int offset){
  node *ptr = li -> front, *tt = ptr;
  int num = li -> len / offset;
  node *n_p[10000];
  for(int i = 0; i < num; i++){
    for(int j = 0; j < offset; j++) tt = tt -> next;
    n_p[i]  = r(ptr, offset);
    ptr = tt;
  }
  n_p[num] = tt;
  li -> front = n_p[0];
  ptr = n_p[0];
  for(int i = 1; i <= num; i++){
    for(int j = 0; j < offset - 1; j++){
      ptr = ptr -> next;
    }
    ptr -> next = n_p[i];
    ptr = ptr -> next;
  }
}

signed main(){
  int r;
  char s1[100000];
  char s2[100000];
  scanf("R=%lld", &r);
  scanf("%s", s1);
  scanf("%s", s2);
  list *l1, *l2, *l3;
  init(&l1); init(&l2); init(&l3);
  int len1 = strlen(s1), len2 = strlen(s2);
  for(int i = len1 - 1; i >= 0; i -= 2){
    push_back(l1, s1[i]);
  }
  for(int i = len2 - 1; i >= 0; i -= 2){
    push_back(l2, s2[i]);
  }
  len1 = len1 / 2 + 1;
  len2 = len2 / 2 + 1;
  for(int i = len1; i < max(len1, len2); i++){
    push_back(l1, '0');
  }
  for(int i = len2; i < max(len1, len2); i++){
    push_back(l2, '0');
  }
  node *ptr1 = l1 -> front, *ptr2 = l2 -> front;
  int carry = 0;
  for(int i = 0; i < max(len1, len2); i++){
    int val = value(ptr1 -> n) + value(ptr2 -> n) + carry;
    carry = 0;
    if(val >= 16){
      carry = 1;
      val -= 16;
    }
    push_front(l3, to_char(val));
    ptr1 = ptr1 -> next;
    ptr2 = ptr2 -> next;
  }
  if(carry) push_front(l3, to_char(carry));
  reverse(l3, r);
  node *ptr3 = l3 -> front;
  printf("[");
  while(ptr3){
    printf("%c", ptr3 -> n);
    if(ptr3 -> next) printf(",");
    ptr3 = ptr3 -> next;
  }
  printf("]");
  printf("\n");
}