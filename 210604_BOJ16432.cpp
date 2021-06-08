#include <iostream>
#define MAX_NUM		1005
using namespace std;

/*** 16432 :: 떡장수와 호랑이
전 날 선택한 떡과 다른 종류의 떡을 선택할 수 있는지 차례대로 확인
-> 모든 경우의 수를 확인해야 함 (완전탐색)
-> 깊이 우선 탐색 (길의 N의 경로를 찾을 수 있는지 여부)
-> 시간 초과를 방지하기 위해 방문한 곳을 체크해야 함
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
		cin >> type[i][0]; // 동희가 i번째 날 들고 가는 떡의 개수
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