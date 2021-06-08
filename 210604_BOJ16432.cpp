#include <iostream>
#define MAX_NUM		1005
using namespace std;

/*** 16432 :: ������� ȣ����
�� �� ������ ���� �ٸ� ������ ���� ������ �� �ִ��� ���ʴ�� Ȯ��
-> ��� ����� ���� Ȯ���ؾ� �� (����Ž��)
-> ���� �켱 Ž�� (���� N�� ��θ� ã�� �� �ִ��� ����)
-> �ð� �ʰ��� �����ϱ� ���� �湮�� ���� üũ�ؾ� ��
***/

int N, M;
int type[MAX_NUM][10], ans[MAX_NUM];

bool solve(int day) {
	if (day > N) return true;

	for (int i = 1; i <= type[day][0]; ++i) {
		if (type[day][i] == 0) continue;
		if (type[day][i] == ans[day - 1]) continue;
		ans[day] = type[day][i];
		type[day][i] = 0;
		bool ret = solve(day + 1);
		if (ret) return ret;
	}

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> type[i][0]; // ���� i��° �� ��� ���� ���� ����
		for (int j = 1; j <= type[i][0]; ++j) {
			cin >> type[i][j];
		}
	}

	int found = solve(1);
	if (found) {
		for (int i = 1; i <= N; ++i) {
			cout << ans[i] << '\n';
		}
	}
	else {
		cout << -1;
	}

	return 0;
}