/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include<stdlib.h>



struct p{
  int val;
  int id;
}typedef p;

p arr[1000005];

int cmp(const void *a, const void *b){
  p *va = (p*)a;
  p *vb = (p*)b;
  if(va -> val == vb -> val) return vb -> id - va -> id;
  return va -> val - vb -> val;
}

signed main(){
  int n, m, idx = 0;
  scanf("%d %d", &n, &m);
  for(int i = 1; i <= n; i++){
    for(int j = 0; j < m; j++){
      int id;
      arr[idx].id = i;
      scanf("%d", &arr[idx++].val);
    }
  }
  qsort((void *)arr, n * m, sizeof(arr[0]), cmp);

  for(int i = 0; i < n * m; i++){
    printf("%d\n", arr[i].id);
  }
}