#include <iostream>
#define MAX_SZ	100005
using namespace std;

/*** 10775 :: 공항
순서대로 도킹을 진행
-> greedy

시간초과를 해결하기 위한 방법:
(1) 일단 시간 초과가 발생하는 부분은 비어 있는 게이트를 찾는 부분이다. -> O(n)
(2) 따라서 이를 해결하기 위하여 linear time 보다 빠른 시간 내에 탐색이 필요하다.
즉, 정적인 선형 배열이 아닌 다른 자료구조의 도입이 필요하다. (예를 들면 log n 의 시간복잡도 내에 탐색이 가능한)
(3) 주어진 g 기준으로 g보다 작은 값만을 탐색하면 됨.
-> union find
***/

int G, P;
int parent[MAX_SZ];
int r[MAX_SZ];
bool gate[MAX_SZ];

int findSet(int x) {
	if (x != parent[x]) {
		parent[x] = findSet(parent[x]); // update parent info
	}
	return parent[x];
}

void unionSet(int x, int y) {
	x = findSet(x);
	y = findSet(y);
	parent[y] = x;
}

int main() {
	int gateNum, ans = 0;

	cin >> G >> P;
	
	/* init */
	for (int i = 1; i <= G; ++i) {
		parent[i] = i;
	}

	for (int i = 1; i <= P; ++i) {
		cin >> gateNum;
		int p = findSet(gateNum);
		if (p == 0) break; // no more free gate
		ans += 1;
		gate[p] = true;
		int freeNum = p;
		while (gate[freeNum]) freeNum -= 1;
		unionSet(freeNum, p);
	}

	cout << ans;

	return 0;
}