#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <bitset>
#include <iostream>

using std::string;
using std::vector;
using std::deque;
using std::ifstream;
using std::ofstream;
using std::set;
using std::bitset;

#define oo 0x3f3f3f3f

class Prufer {
private:
	string input_file;
	string output_file;
	int m;
	deque<int> dq;
	vector<int> result;
	bitset<100000> status;

	void read() {
		ifstream in(input_file);

		in >> m;
		int x;
		result.resize(m + 1, -1);
		status.reset();

		for (int i = 0; i < m; ++i) {
			in >> x;
			dq.push_back(x);
			status.set(x);
		}

		in.close();
	}

	int minim() {
		for (int i = 0; i <= m; ++i) {
			if (!status.test(i)) {
				return i;
			}
		}
	}

	void stat(int x) {
		for (int i = 0; i < m - 1; ++i) {
			if (dq[i] == x) {
				return;
			}
		}
		status.reset(x);
	}

	void solve() {
		read();

		for (int i = 0; i < m; ++i) {
			int first = dq.front();
			int m = minim();
			dq.pop_front();

			stat(first);
			
			result[m] = first;
			dq.push_back(m);

			status.set(m);
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
		out << m + 1 << '\n';
		for (int i = 0; i <= m; ++i) {
			out << result[i] << " ";
		}
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