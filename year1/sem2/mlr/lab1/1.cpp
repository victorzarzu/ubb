#include <bits/stdc++.h>
#define nod pair<int, int>
#define varf first 
#define muchie second

using namespace std;
ifstream f("1.txt");

int main()
{
  int n, m, x, y;

  f>>n>>m;

  bool ma[n + 1][n + 1];
  memset(ma, 0, sizeof(ma));

  for(int i = 1;i <= m;++i)
    f>>x>>y, ma[x][y] = ma[y][x] = true;

  cout<<"Matricea de adiacenta\n";
  for(int i = 1;i <= n;++i, cout<<'\n')
    for(int j = 1;j <= n;++j)
      cout<<ma[i][j]<<" ";

  vector<nod> la[n + 1];
  int indice = 0;

  vector<pair<int, int>> muchii;

  for(int i = 1;i <= n;++i)
    for(int j = 1;j <= i;++j)
      if(ma[i][j] == 1)
        {
          ++indice;
          muchii.push_back(make_pair(i, j));
          la[i].push_back(make_pair(j, indice));
          la[j].push_back(make_pair(i, indice));
        }

  cout<<"Lista de adiacenta\n";
  for(int i = 1;i <= n;++i, cout<<'\n')
    for(auto node : la[i])
      cout<<node.first<<" ";

  int mi[n + 1][m + 1];
  memset(mi, 0, sizeof(mi));

  for(int i = 1;i <= n;++i)
    for(auto node : la[i])
      mi[i][node.muchie] = 1;

  cout<<"Matricea de incidenta\n";
  for(int i = 1;i <= n;++i, cout<<'\n')
    for(int j = 1;j <= m;++j)
      cout<<mi[i][j]<<" ";
    

  bool ma1[n + 1][n + 1];
  memset(ma1, false, sizeof(ma1));


  for(auto muchie : muchii)
    ma1[muchie.first][muchie.second] = ma1[muchie.second][muchie.first] = 1;
  
  cout<<"Matricea de adiacenta\n";
  for(int i = 1;i <= n;++i, cout<<'\n')
    for(int j = 1;j <= n;++j)
      cout<<ma1[i][j]<<" "; 

  return 0;
}
