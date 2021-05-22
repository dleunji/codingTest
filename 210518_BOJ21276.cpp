#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#define MAX_N		1005
#define OUTDEGREE	0
using namespace std;

/*** 21276 :: �躸 ������ ȣ��
N���� ����� ���� �ڽ��� ������ ���ϴ� M���� ������ �־�����.
�־��� ����-�ļ� ���踦 ��� �����ؾ� �Ѵ�.
���� ���� ���İ��谡 ������� �ʵ��� ������ �����ؾ� �Ѵ�.
-> ��������
***/

int N, M;
string name, ances;
vector<string> nameVec, ancesVec;
map<string, int> nameMap;
string indexMap[MAX_N];
int info[MAX_N][MAX_N];

struct compare {
	bool operator() (int &x, int &y) {
		return indexMap[x] > indexMap[y];
	}
};
priority_queue<int, vector<int>, compare> children[MAX_N];
queue<int> q;

int main() {
	// get name
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> name;
		nameVec.push_back(name);
	}
	// make index in ascending order
	sort(nameVec.begin(), nameVec.end());
	for (int i = 1; i <= N; ++i) {
		name = nameVec[i - 1];
		nameMap.insert(make_pair(name, i));
		indexMap[i] = name;
	}

	cin >> M;
	for (int i = 1; i <= M; ++i) {
		cin >> name >> ances;
		int nameIdx = nameMap[name];
		int ancesIdx = nameMap[ances];
		info[ancesIdx][nameIdx] = 1;
		info[nameIdx][OUTDEGREE] += 1;
	}

	// topological sort start 

	// count & print 1st generation
	int K = 0;
	for (int i = 1; i <= N; ++i) {
		if (info[i][OUTDEGREE] == 0) {
			ancesVec.push_back(indexMap[i]);
			q.push(i);
			K += 1;
		}
	}

	cout << K << '\n';
	sort(ancesVec.begin(), ancesVec.end());
	for (int i = 0; i < K; ++i) {
		cout << ancesVec[i] << ' ';
	}
	cout << '\n';

	while (!q.empty()) {
		int cur = q.front();
		for (int i = 1; i <= N; ++i) {
			if (info[cur][i]) {
				info[i][OUTDEGREE] -= 1;
				if (info[i][OUTDEGREE] == 0) {
					q.push(i);
					children[cur].push(i);
				}
			}
		}
		q.pop();
	}

	for (int i = 1; i <= N; ++i) {
		cout << indexMap[i] << ' ' << children[i].size() << ' ';
		while (!children[i].empty()) {
			cout << indexMap[children[i].top()] << ' ';
			children[i].pop();
		}
		cout << '\n';
	}
}