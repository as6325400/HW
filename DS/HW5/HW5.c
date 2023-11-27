#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define int long long

int **edge;
bool graph[105][105];
int trace[105];
int visit[105];
int t = 0;
bool ans[105];

void DFS(int p, int i){
  
  visit[i] = ++t;
  printf("node i %lld node j %lld\n", p, i);
  printf("node %lld visit[i] %lld\n", i, visit[i]);
  trace[i] = i;

  int child = 0;
  bool ap = false;
  for (int j=1; j < 105; ++j)			
		if (graph[i][j] && j != p)	
			if (visit[j])			
			{
				if (visit[j] < visit[trace[i]])
					trace[i] = j;
			}
			else					
			{
				child++;
				DFS(i, j);

				
				if (visit[trace[j]] < visit[trace[i]])
					trace[i] = trace[j];

				if (visit[trace[j]] >= visit[i])
					ap = true;
			}


	if ((i == p && child > 1) || (i != p && ap)){
    printf("%lld\n", i);
		ans[i] = true;
  }

}

void swap(int *a, int *b) {
  int temp[3];
  for(int i = 0; i < 3; i++){
    temp[i] = a[i];
  }
  for(int i = 0; i < 3; i++){
    a[i] = b[i];
  }
  for(int i = 0; i < 3; i++){
    b[i] = temp[i];
  }
}

void heapify(int **arr, int n, int i) {
  // Find largest among root, left child and right child
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left][0] > arr[largest][0])
    largest = left;

  if (right < n && arr[right][0] > arr[largest][0])
    largest = right;

  // Swap and continue heapifying if root is not largest
  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

// Main function to do heap sort
void HeapSort(int **arr, int n) {
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  // Heap sort
  for (int i = n - 1; i >= 0; i--) {
    swap(arr[0], arr[i]);

    // Heapify root element to get highest element at root again
    heapify(arr, i, 0);
  }
}

int parent[105];

void init(){
  for(int i = 0; i < 105; i++){
    parent[i] = i;
  }
}

int find_root(int x){
  if(x == parent[x]) return x;
  return parent[x] = find_root(parent[x]);
}
bool Same(int a, int b){
  return find_root(a) == find_root(b);
}
void Union(int a, int b){
  //將a併進b
  parent[find_root(a)] = find_root(b);
}


signed main(){
  int n, nm, m;

  int temp[10][3];
  int countedge[105];

  for(int i = 0; i < 105; i++){
    ans[i] = false;
    visit[i] = 0;
    countedge[i] = 0;
  }

  scanf("%lld%lld", &n, &nm);

  edge = (int**)malloc(sizeof(int*) * 5000);
  for(int i = 0; i < 5000; i++){
    edge[i] = (int*)malloc(sizeof(int) * 3);
  }

  for(int i = 0; i < nm; i++){
    scanf("%lld%lld%lld", &temp[i][1], &temp[i][2], &temp[i][0]);
    graph[temp[i][1]][temp[i][2]] = true;
    graph[temp[i][2]][temp[i][1]] = true;
  }

  scanf("%lld", &m);

  for(int i = 0; i < m; i++){
    scanf("%lld%lld%lld", &edge[i][1], &edge[i][2], &edge[i][0]);
    graph[edge[i][1]][edge[i][2]] = true;
    graph[edge[i][2]][edge[i][1]] = true;
  }

  HeapSort(edge, m);

  // for(int i = 0; i < m; i++){
  //   printf("%lld %lld %lld\n", edge[i][0], edge[i][1], edge[i][2]);
  // }

  int count = 0;
  init();



  for(int i = 0; i < m; i++){
    if(!Same(edge[i][1], edge[i][2])){
      Union(edge[i][1], edge[i][2]);
      count += edge[i][0];
    }
  }
  
  printf("%lld\n", count);

  for(int i = m; i < m + nm; i++){
    edge[i][0] = temp[i - m][0];
    edge[i][1] = temp[i - m][1];
    edge[i][2] = temp[i - m][2];
  }

  HeapSort(edge, m + nm);

  count = 0;
  init();

  for(int i = 0; i < m; i++){
    if(!Same(edge[i][1], edge[i][2])){
      Union(edge[i][1], edge[i][2]);
      countedge[edge[i][1]]++;
      countedge[edge[i][2]]++;
      count += edge[i][0];
    }
  }

  printf("%lld\n", count);

	

  count = 0;

  for(int i = 1; i < 105; i++){
    if(countedge[i] > 1){
      if(count == 0) printf("%lld", i);
      else printf(",%lld", i);
      count++;
    }
  }

  printf("\n");
  return 0;
}