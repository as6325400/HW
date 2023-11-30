#include <bits/stdc++.h>
#define int long long

using namespace std;

class dsu
{
  private:
    vector<int> parent;
  public:
    dsu(int number){
        parent.resize(number);
        for(int i = 0; i < number; i++)
            parent[i] = i;
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
};


void solve(){
  int n, m;
  cin >> n >> m;
  vector<vector<int>> edge;
  vector<int> node(n + 1);
  for(int i = 1; i <= n; i++){
    cin >> node[i];
  }
  set<pair<int, int>> ss;
  for(int i = 0; i < m; i++){
    int w, n, v;
    cin >> n >> v >> w;
    edge.push_back({w, n, v});
  }
  for(int i = 1; i <= n; i++){
    for(int j = i + 1; j <= n; j++){
      if(!ss.count({i, j}) && !ss.count({j, i})){
        edge.push_back({node[i] + node[j], i, j});
      }
    }
  }
  sort(edge.begin(), edge.end());

  dsu d(n);
  int ans = 0;
  for(int i = 0; i < edge.size(); i++){
    if(!d.Same(edge[i][1], edge[i][2])){
      d.Union(edge[i][1], edge[i][2]);
      ans += edge[i][0];
    }
  }
  cout << ans << '\n';
}

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while(tt--){
    solve();
  }
}