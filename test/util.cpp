#include "util.h"

using namespace std;


void print(vector<set<int>> v) {
	cout << "{ ";
	for (auto const &s : v) {
		cout << "{";
		for (auto elem : s) {
			cout << elem << ", ";
		}
		cout << "}, ";
	}
	cout << "}";
}

void print(vector<int> &v) {
	cout << "{ ";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << " }" << endl;
}


void print(set<int> v) {
	cout << "{ ";
	for (auto elem : v) {
		cout << elem << ", ";
	}
	cout << " }" << endl;
}
