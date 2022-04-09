#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

#define oo 0x3f3f3f3f

#define arc pair<int, int>
#define nod first
#define cost second

using std::vector;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::make_pair;
using std::string;
using std::fstream;
using std::queue;
using std::set;

class Johnson {
private:
	int n, m;
	bool positive;
	vector<arc>* graf;
	string in_file;
	string out_file;
	vector<int> bellman;
	int** mat;

	void Dijsktra(int source, int* distance) {
		memset(distance, oo, sizeof(int) * n);
		distance[source] = 0;
		set<pair<int, int>> heap;
		heap.insert(make_pair(0, source));

		while (!heap.empty()) {
			int node = heap.begin()->second;
			heap.erase(heap.begin());

			for (auto muchie : graf[node]) {
				if (distance[muchie.nod] > distance[node] + muchie.cost) {
					if (distance[muchie.nod] != oo) {
						heap.erase(heap.find(make_pair(distance[muchie.nod], muchie.nod)));
					}
					distance[muchie.nod] = distance[node] + muchie.cost;
					heap.insert(make_pair(distance[muchie.nod], muchie.nod));
				}
			}
		}

	}

	bool Bellman_Ford() {
		bellman.resize(n + 1, oo);
		bellman[n] = 0;

		bool* viz = new bool[n + 1];
		memset(viz, false, sizeof(bool) * (n  + 1));

		int* number = new int[n + 1];
		memset(number, 0, sizeof(int) * (n + 1));

		queue<int> q;
		q.push(n);

		while (!q.empty()) {
			int first = q.front();

			for (auto muchie : graf[first]) {
				if (bellman[muchie.nod] > bellman[first] + muchie.cost) {
					bellman[muchie.nod] = bellman[first] + muchie.cost;
					if (!viz[muchie.nod]) {
						q.push(muchie.nod);
					}

					viz[muchie.nod] = true;
					number[muchie.nod]++;
					if (number[muchie.nod] >= n + 1) {
						delete[] viz;
						delete[] number;
						return false;
					}
				}
			}

			q.pop();
			viz[first] = false;
		}

		delete[] viz;
		delete[] number;
		return true;
	}

	bool solve() {
		citire();
;
		if (!positive) {
			for (int i = 0; i < n; ++i) {
				graf[n].push_back(make_pair(i, 0));
			}

			if (!Bellman_Ford()) {
				return false;
			}

			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < graf[i].size(); ++j) {
					graf[i][j].cost = graf[i][j].cost + bellman[i] - bellman[graf[i][j].nod];
					//std::cout << i << " " << muchie.nod << " " << muchie.cost << '\n';
				}
			}
		}

		for (int i = 0; i < n; ++i) {
			Dijsktra(i, mat[i]);
		}
		return true;
	}

	void citire() {
		ifstream in(in_file);

		in >> n >> m;

		graf = new vector<arc>[n + 1];
		mat = new int* [n];
		for (int i = 0; i < n; ++i) {
			mat[i] = new int[n];
		}

		int x, y, w;
		for (int i = 1; i <= m; ++i) {
			in >> x >> y >> w;
			graf[x].push_back(make_pair(y, w));
			if (w < 0) {
				positive = false;
			}
		}
		for (int i = 0; i < n; ++i) {
			sort(graf[i].begin(), graf[i].end());
		}

		in.close();
	}

public:
	Johnson() = delete;
	Johnson(const string intrare, const string iesire) : n{ 0 }, m{ 0 }, in_file{ intrare }, out_file{ iesire }, positive{ true } {};

	~Johnson() {
		delete[] graf;
		for (int i = 0; i < n; ++i) {
			delete[] mat[i];
		}
		delete[] mat;
	}

	void afisare() {
		ofstream out(out_file, std::ofstream::ate);

		if (!solve()) {
			out << -1 << '\n';
		}
		else {
			for (int i = 0; i < n; ++i) {
				for (auto muchie : graf[i]) {
					out << i << " " << muchie.nod << " " << muchie.cost << '\n';
				}
			}


			for (int i = 0; i < n; ++i, out<<'\n') {
				for (int j = 0; j < n; ++j) {
					if (mat[i][j] == oo) {
						out << "INF ";
					}
					else {
						out << mat[i][j] - bellman[i] + bellman[j] << " ";
					}
				}
			}
		}

		out.close();
	}

};

int main(int argc, char** argv) {
	if (argc != 3) {
		return 0;
	}

	Johnson r2 = Johnson(argv[1], argv[2]);
	r2.afisare();

	return 0;
}