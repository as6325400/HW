/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

char graph[2300][2300];

void dfs(int x, int y){
  if(graph[x][y] == '+') return;
  graph[x][y] = '+';
  dfs(x + 1, y);
  dfs(x, y + 1);
  dfs(x - 1, y);
  dfs(x, y - 1);
}

int main()
{
  int n, m, ans = 0;
  scanf("%d %d", &n, &m);
  
  for(int i = 0; i < 2300; i++)
    for(int j = 0; j < 2300; j++)
      graph[i][j] = '+';
  
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      scanf(" %c", &graph[i][j]);
  
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      if(graph[i][j] != '+'){
        ans++;
        dfs(i, j);
      }
  
  printf("%d\n", ans);
  return 0;
}
