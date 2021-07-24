#include <iostream>
#include <vector>
#define MAX_N	1000005
#define EARLY	0
#define LATE	1
using namespace std;

int N;
vector<int> g[MAX_N];
int dp[MAX_N][2];
bool v[MAX_N];

int min2(int a, int b) {
	return a < b ? a : b;
}

int solve(int cur, int type) {
	v[cur] = true;

	if (dp[cur][type] != -1) return dp[cur][type];

	if (type == EARLY) {
		dp[cur][type] = 1; // 본인이 얼리어댑터이므로
		for (int next : g[cur]) {
			if (v[next]) continue;
			dp[cur][type] += min2(solve(next, EARLY), solve(next, LATE));
		}
	}
	// 부모가 얼리어댑터가 아니라면 자식은 무조건 얼리어댑터여야 한다.
	else {
		dp[cur][type] = 0;
		for (int next : g[cur]) {
			if (v[next]) continue;
			dp[cur][type] += solve(next, EARLY);
		}
	}

	v[cur] = false;
	return dp[cur][type];
}

// 알고리즘: 트리 dp (각 노드에 대하여 "얼리어댑터인 경우"와 "얼리어댑터가 아닌 경우"에 대하여 계산
int main() {
	int u, v;

	// get input
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		cin >> u >> v;
		// u가 v와 친구라면 v도 u와 친구이므로 양방향 그래프를 구축한다.
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 1; i <= N; ++i) {
		dp[i][0] = dp[i][1] = -1;
	}

	cout << min2(solve(1, EARLY), solve(1, LATE));

	return 0;
}
