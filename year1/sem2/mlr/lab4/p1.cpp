#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;


class Prufer {
private:
	string input_file;
	string output_file;
	vector<int> t;
	vector<int> result;
	vector<int> degree;
	int n, root;

	void read() {
		ifstream in(input_file);

		if (in.fail()) {
			return;
		}

		in >> n;
		t.resize(n);
		degree.resize(n, 0);

		for (int i = 0; i < n; ++i) {
			in >> t[i];
			if (t[i] == -1) {
				root = i;
			}
			else {
				degree[i]++;
				degree[t[i]]++;
			}
		}

		in.close();
	}

	int lowest_leaf() {
		for (int i = 0; i < n; ++i) {
			if (i != root && degree[i] == 1) {
				return i;
			}
		}
	}

	void solve() {
		read();

		for (int i = 0; i < n - 1; ++i) {
			int lowest = lowest_leaf();
			degree[t[lowest]]--;
			degree[lowest] = 0;
			result.push_back(t[lowest]);
		}
	}

public:
	Prufer(const string& input_file, const string& output_file) : input_file{ input_file }, output_file{ output_file }{};

	void print() {
		ofstream out(output_file);

		if (out.fail()) {
			return;
		}

		solve();

		out << n - 1 << '\n';
		for (const auto& val : result) {
			out << val << " ";
		}

		out.close();
	}
};

int main(int argc, char** argv) {
	if (argc != 3) {
		return 0;
	}

	Prufer prufer = Prufer{ argv[1], argv[2] };
	prufer.print();

	return 0;
}