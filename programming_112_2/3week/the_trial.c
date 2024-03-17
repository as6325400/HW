#include<stdio.h>
#define int long long

#define GRAPHMAX 100

int graph[GRAPHMAX][GRAPHMAX];
int p1_x, p1_y, p2_x, p2_y, flag = 1;

void dfs(int x, int y){
  if(x == p2_x && y == p2_y){
    flag = 0;
    return;
  }
  if(flag == 0) return;
  if(graph[x][y] == 1) return;
  graph[x][y] = 1;
  dfs(x + 1, y);
  dfs(x, y + 1);
  dfs(x, y - 1);
  dfs(x - 1, y);
  graph[x][y] = 0;
}


signed main(){
  for(int i = 0; i < GRAPHMAX; i++)
    for(int j = 0; j < GRAPHMAX; j++)
      graph[i][j] = 1;

  int w, l;
  scanf("%lld %lld", &w, &l);
  scanf("%lld %lld %lld %lld", &p1_x, &p1_y, &p2_x, &p2_y);
  p1_x++;
  p1_y++;
  p2_x++;
  p2_y++;
  for(int i = 1; i <= w; i++)
  {
    for (int j = 1; j <= l; j++)
    {
      scanf("%lld", &graph[i][j]);
    }
  }
  dfs(p1_x, p1_y);
  if(flag == 1) printf("No\n");
  else printf("Yes\n");
}