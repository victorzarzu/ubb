#include <bits/stdc++.h>
#define oo 0x3f3f3f3f

using namespace std;
ifstream f("2.txt");
int n, m;

void dfs(int node, vector<int> graf[], bool viz[])
{
  for(auto vecin : graf[node])
    if(!viz[vecin])
      {
        viz[vecin] = true;
        dfs(vecin, graf, viz);
      }
}

int main()
{
  f>>n>>m;
  int x, y;

  vector<int> graf[n + 1];
  for(int i = 1;i <= m;++i)
    f>>x>>y, graf[x].push_back(y), graf[y].push_back(x);

  bool izolat = false;
  for(int i = 1;i <= n;++i)
    if(!graf[i].size())
      izolat = true;
  
  if(!izolat)
    cout<<"Graful nu are varfuri izolate\n";
  else
  {
    cout<<"Varfurile izolate sunt: ";
    for(int i = 1;i <= n;++i)
      if(!graf[i].size())
        cout<<i<<" ";
    cout<<'\n';
  }

  bool regular = true;
  for(int i = 2;i <= n;++i)
    if(graf[i].size() != graf[1].size())
      regular = false;
  
  if(regular)
    cout<<"Graful este regular\n";
  else
    cout<<"Graful nu este regular\n";

  int ma[n + 1][n + 1];
  memset(ma, oo, sizeof(ma));
  
  for(int i = 1;i <= n;++i)
    for(auto node : graf[i])
      ma[i][node] = 1;

  for(int k = 1;k <= n;++k)
    for(int i = 1;i <= n;++i)
      for(int j = 1;j <= n;++j)
        if(i != j && ma[i][j] > ma[i][k] + ma[k][j])
          ma[i][j] = ma[i][k] + ma[k][j];
  
  cout<<"Matricea distantelor\n";
  for(int i = 1;i <= n;++i, cout<<'\n')
    for(int j = 1;j <= n;++j)
      cout<<(ma[i][j] == oo ? 0 : ma[i][j])<<" ";

  bool viz[n + 1];
  memset(viz, false, sizeof(viz));
  viz[1] = true;
  dfs(1, graf, viz);

  for(int i = 1;i <= n;++i)
    if(!viz[i])
      {
        cout<<"Graful nu este conex\n";
        return 0;
      }
  
  cout<<"Graful este conex\n";

  return 0;
}
