/*************************************************************
 * Small generator of Directed Acyclic Graphs (DAG)
 *  - of size V and
 *  - prob p of creating the edge (u,v)
 *
 * Pedro T. Monteiro - Pedro.Tiago.Monteiro@tecnico.ulisboa.pt
 *************************************************************/

#include <iostream>
#include <list>

using namespace std;

// Graph
int _V;
int _E = 0;
list<int>* _g;

float _prob;
int* _v2ID;  // map vertex position to ID

//-------------------------------------------------------------------

void printUsage() {
	cout << "Usage: randomDAG #V #p seed" << endl;
	cout << "\t#V: number of vertices" << endl;
	cout << "\t#p: prob \\in [0,1] to create edge (u,v)" << endl;
	cout << "\tseed: random seed number (optional)" << endl;
	exit(0);
}

void parseArgs(int argc, char **argv) {
	int seed = 0;

	if (argc < 3) printUsage();

	sscanf(argv[1], "%d", &_V);
	if (_V < 1) {
		cout << "ERROR: # vertices must be > 1" << endl;
		printUsage();
	}

	sscanf(argv[2], "%f", &_prob);
	if (_prob < 0 || _prob > 1) {
		cout << "ERROR: Prob to create edge (u,v) between [0,1]" << endl;
		printUsage();
	}

	if (argc > 3) {
		// Init rand seed
		sscanf(argv[3], "%d", &seed);
		srand(seed);
	} else {
		srand((unsigned int)time(NULL));
	}
}


int randomValue(int max) {
	return rand() % max; // [0, max - 1]
}

void addEdge(int u, int v) {
	if (((float) rand() / RAND_MAX) <= _prob) {
		_g[u].push_back(v);
		_E++;
	}
}

int main(int argc, char *argv[]) {
	// parse arguments
	parseArgs(argc, argv);

	// init vector of IDs (to be shuffled)
	_v2ID = new int[_V];
	for (int i = 0; i < _V; i++)
		_v2ID[i] = i;
	// shuffle IDs
	for (int i = 0; i < _V; i++) {
		int u = randomValue(_V);
		int v = randomValue(_V);
		int aux = _v2ID[u];
		_v2ID[u] = _v2ID[v];
		_v2ID[v] = aux;
	}

	// init graph
	_g = new list<int>[_V];
	// add edges
	for (int i = 0; i < _V; i++) {
		for (int j = i+1; j < _V; j++) {
			addEdge(i, j);
		}
	}

	// print header
	cout << _V << " " << _E << endl;
	// print edges (with _v2ID transformation)
	for (int i = 0; i < _V; i++) {
		for (list<int>::iterator it = _g[i].begin(); it != _g[i].end(); it++) {
			cout << (_v2ID[i]+1) << " " << (_v2ID[*it]+1) << endl;
		}
	}
	return 0;
}
