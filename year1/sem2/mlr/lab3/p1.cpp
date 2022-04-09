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

class DrumMinim{
private:
	int n, m, s;
	bool positive;
	vector<arc>* graf;
	string in_file;
	string out_file;
	vector<int> result;

	bool Dijsktra() {
		set<pair<int, int>> heap;
		heap.insert(make_pair(0, s));
		
		while (!heap.empty()) {
			int node = heap.begin()->second;
			heap.erase(heap.begin());

			for (auto muchie : graf[node]) {
				if (result[muchie.nod] > result[node] + muchie.cost) {
					if (result[muchie.nod] != oo) {
						heap.erase(heap.find(make_pair(result[muchie.nod], muchie.nod)));
					}
					result[muchie.nod] = result[node] + muchie.cost;
					heap.insert(make_pair(result[muchie.nod], muchie.nod));
				}
			}
		}

		return true;
	}

	bool Bellman_Ford() {
		bool* viz = new bool[n];
		memset(viz, false, sizeof(bool) * n);

		int* number = new int[n];
		memset(number, 0, sizeof(int) * n);

		queue<int> q;
		q.push(s);

		while (!q.empty()) {
			int first = q.front();

			for (auto muchie : graf[first]) {
				if (result[muchie.nod] > result[first] + muchie.cost) {
					result[muchie.nod] = result[first] + muchie.cost;
					if (!viz[muchie.nod]) {
						q.push(muchie.nod);
					}

					viz[muchie.nod] = true;
					number[muchie.nod]++;
					if (number[muchie.nod] >= n) {
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
		if (positive) {
			return Dijsktra();
		}
		else {
			return Bellman_Ford();
		}
	}

public:
	DrumMinim() = delete;
	DrumMinim(const string intrare, const string iesire) : n{ 0 }, m{ 0 }, s{ 0 }, in_file{ intrare }, out_file{ iesire }, positive{ true } {};

	~DrumMinim() {
		delete[] graf;
	}

	void citire() {
		ifstream in(in_file);

		in >> n >> m >> s;

		result.resize(n, oo);
		result[s] = 0;
		graf = new vector<arc>[n];

		int x, y, w;
		for (int i = 1; i <= m; ++i) {
			in >> x >> y >> w;
			graf[x].push_back(make_pair(y, w));
			if (w < 0) {
				positive = false;
			}
		}

		in.close();
	}

	void afisare() {
		ofstream out(out_file);

		if (!solve()) {
			out << "Ciclu negativ!\n";
		}
		else {
			for (int i = 0; i < n; ++i) {
				if (result[i] != oo) {
					out << result[i] << " ";
				}
				else {
					out << "INF ";
				}
			}
		}
		out.close();
	}

};

int main1(int argc, char** argv) {
	if (argc != 3) {
		return 0;
	}

	DrumMinim r1 = DrumMinim(argv[1], argv[2]);
	r1.afisare();

	return 0;
}