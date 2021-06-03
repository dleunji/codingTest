#include <iostream>
#define MAX_SZ	100005
using namespace std;

/*** 10775 :: ����
������� ��ŷ�� ����
-> greedy

�ð��ʰ��� �ذ��ϱ� ���� ���:
(1) �ϴ� �ð� �ʰ��� �߻��ϴ� �κ��� ��� �ִ� ����Ʈ�� ã�� �κ��̴�. -> O(n)
(2) ���� �̸� �ذ��ϱ� ���Ͽ� linear time ���� ���� �ð� ���� Ž���� �ʿ��ϴ�.
��, ������ ���� �迭�� �ƴ� �ٸ� �ڷᱸ���� ������ �ʿ��ϴ�. (���� ��� log n �� �ð����⵵ ���� Ž���� ������)
(3) �־��� g �������� g���� ���� ������ Ž���ϸ� ��.
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