#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int from, to, cost;
};

class Grath {
private:
	int temp = 0;
	int nodesCount, ribsCount;
	static const int maxNodes = 100, maxRibs = maxNodes * 2;
	int head[maxNodes];
	int next[maxRibs];
	int terminal[maxRibs];
	vector<edge> edges;
	int minLengths[maxNodes - 1];


	void add(int from, int to, int weight) {
		temp = temp + 1;
		terminal[temp] = to;
		next[temp] = head[from];
		head[from] = temp;
		edges.push_back(edge({ from, to, weight }));
	}

public:
	Grath() {
		std::fill(std::begin(minLengths), std::end(minLengths), std::numeric_limits<int>::max() - 1);

		cout << "Edges count >> "; cin >> nodesCount;
		cout << "Ribs count >> "; cin >> ribsCount;
		cout << "Edges:" << endl;

		for (int i = 0; i < ribsCount; i++) {
			int from, weight, to; char choice;
			cout << "From >> "; cin >> from;
			cout << "To >> "; cin >> to;
			cout << "Weight >> "; cin >> weight;
			cout << "Bidirectional ? (y/n) >> "; cin >> choice;
			if (choice == 'n') add(from, to, weight);
			else {
				add(from, to, weight);
				add(to, from, weight);
			}

			cout << "..." << endl;
		}
	}

	void list() {
		cout << "Paths:";
		for (int i = 0; i < nodesCount + 1; i++) {
			int j = head[i];
			if (i) cout << i << "->";
			while (j > 0) {
				if (!next[j]) cout << terminal[j];
				else cout << terminal[j] << ", ";
				j = next[j];
			}
			cout << endl;
		}
	}

	void fordbelman(int node) {
		minLengths[node - 1] = 0;
		int max = std::numeric_limits<int>::max() - 1;
		for (int i = 0; i < nodesCount; ++i)
			for (edge j : edges)
				if (minLengths[j.from - 1] < std::numeric_limits<int>::max()) {
					minLengths[j.to - 1] = min(minLengths[j.to - 1], minLengths[j.from - 1] + j.cost);
				}
		for (int i = 0; i < nodesCount; ++i) {
			cout << "From edge " << node << " to edge: " << i + 1 << " -> Length: " << minLengths[i] << endl;
			if (minLengths[i] == std::numeric_limits<int>::max() - 1) continue;
			if (max == std::numeric_limits<int>::max() - 1 || max < minLengths[i]) max = minLengths[i];
		}

		cout << "Eccentricity: " << max << endl;

	}
};

void main() {
	int edge = 1;
	setlocale(LC_ALL, "Rus");
	Grath grath;
	grath.list();
	grath.fordbelman(edge);
}