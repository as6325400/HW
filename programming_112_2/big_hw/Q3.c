/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define typename int

unsigned int MurmurOAAT32(char *key){
  unsigned int h = 3323198485u;
  for (; *key; ++key){
  h ^= *key;
  h *= 0x5bd1e995;
  h ^= h >> 15;
  }
  return h;
}

typedef struct node{
    unsigned int num;
    struct node *left;
    struct node *right;
}node;                                                   


typedef struct vector
{
	typename *array;
	unsigned int size_t;
	unsigned int capicity;
}vector;


vector initialize() {
	vector temp;
	temp.capicity = 2;
	temp.array = (typename*)malloc(sizeof(typename) * temp.capicity);
	temp.size_t = 0;
	return temp;
}

unsigned int size(vector *datastructure) {
	return datastructure->size_t;
}

void push_back(vector *datastructure, typename value) {
	datastructure->array[datastructure->size_t] = value;
	datastructure->size_t += 1;
	if (datastructure->size_t * 2 >= datastructure->capicity) {
		datastructure->capicity *= 2;
		typename *temp = datastructure->array;
		datastructure->array = (typename *)malloc(sizeof(typename)*datastructure->capicity);
		for (int i = 0; i < datastructure -> size_t; i++)
			datastructure->array[i] = temp[i];
		free(temp);
	}
}

void clear(vector *t) {
	free(t->array);
	*t = initialize();
}


node* build(int l, int r, int num, char **save){
    node* tn = (node*)malloc(sizeof(node));
    if(l == r){
        if(l >= num) return NULL;
        tn -> num = MurmurOAAT32(save[l]);
        // tn -> left = NULL;
        // tn -> right = NULL;
        return tn;
    }
    int mid = (l + r) / 2;
    tn -> left = build(l, mid, num, save);
    tn -> right = build(mid + 1, r, num, save);
    unsigned int nnum;
    if(!tn -> left && !tn -> right) return NULL;
    else if(tn -> left && !tn -> right){
        nnum = tn -> left -> num + tn -> left -> num;
    }
    else nnum = tn -> left -> num + tn -> right -> num;
    char temp[30];
    sprintf(temp, "%u", nnum);
    tn -> num = MurmurOAAT32(temp);
    return tn;
}

vector save_index;
int tree_height[105];
unsigned int **save_tree;
int h = 0;
char **save;

void dfs(node *root, int height, int index){
    if(!root) return;
    // printf("%d %d ", height, index);
    if(root -> num == save_tree[height][index]){
      printf("%u == %u\n", root -> num, save_tree[height][index]);
      return;
    }
    else{
      printf("%u != %u\n", root -> num, save_tree[height][index]);
      if(height == h - 1){
        printf("wrong data %s\n", save[index]);
      }
    }
    dfs(root -> left, height + 1, index * 2);
    dfs(root -> right, height + 1, index * 2 + 1);
    
}

int main(){
    int len = 105, num;
    save_index = initialize();
    scanf("%d", &num);
    save = (char**)malloc(sizeof(char*) * num);
    int new_num = 1;
    while(new_num < num){
        new_num *= 2;
    }
    for(int i = 0; i < num; i++){
        save[i] = (char*)malloc(len + 1);
    }
    for(int i = 0; i < num; i++){
        scanf("%s",save[i]);
    }
    node *root = build(0, new_num - 1, num, save);
    scanf("%d", &h);
    save_tree = (unsigned int**)malloc(sizeof(unsigned int*) * h);
    for(int i = 0; i < h; i++){
      scanf("%d", &tree_height[i]);
      save_tree[i] = (unsigned int*)malloc(sizeof(unsigned int) * tree_height[i] + 1);
      for(int j = 0; j < tree_height[i]; j++){
        scanf("%u", &save_tree[i][j]);
      }
    }
    dfs(root, 0, 0);
}