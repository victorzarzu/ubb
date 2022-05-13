#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::tuple;

#define muchie tuple<int, int, int>
#define cost(x) (std::get<0>(x))
#define v1(x) (std::get<1>(x))
#define v2(x) (std::get<2>(x))

class Kruskal {
private:
	string input_file;
	string output_file;
	vector<muchie> muchii;
	vector<muchie> result;
	vector<int> t;
	vector<int> r;
	int n, m;
	long long cost;

	void read() {
		ifstream in(input_file);
		
		if (in.fail()) {
			return;
		}

		in >> n >> m;
		int x, y, w;
		
		for (int i = 1; i <= m; ++i) {
			in >> x >> y >> w;
			muchii.push_back({ w, x, y });
		}

		t.resize(n);
		r.resize(n);

		for (int i = 0; i < n; ++i) {
			t[i] = i;
			r[i] = 1;
		}

		in.close();
	}

	int find(int x) {
		if (t[x] == x) {
			return x;
		}
		return t[x] = find(t[x]);
	}

	void unite(int x, int y) {
		if (r[x] >= r[y]) {
			t[y] = x;
			r[x] += r[y];
			return;
		}

		t[x] = y;
		r[y] += r[x];
	}

	void solve() {
		read();
		std::sort(muchii.begin(), muchii.end());

		for (const auto& much : muchii) {
			if (find(v1(much)) != find(v2(much))) {
				cost += cost(much);
				unite(find(v1(much)), find(v2(much)));
				result.push_back(much);
			}
		}
	}

public:
	Kruskal(const string& input_file, const string& output_file) : input_file{ input_file }, output_file{ output_file }, cost{ 0 }{};

	void print() {
		solve();

		ofstream out(output_file);

		if (out.fail()) {
			return;
		}

		out << cost << '\n';
		out << n - 1 << '\n';
		
		for (const auto& much : result) {
			out << v1(much) << " " << v2(much) << '\n';
		}

		out.close();
	}
};

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Numar de argumente incorect!";
		return 0;
	}

	Kruskal k = Kruskal(argv[1], argv[2]);
	k.print();


	return 0;
}