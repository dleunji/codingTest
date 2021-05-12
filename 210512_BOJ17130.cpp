/*BOJ 17130*/
/*DFS 활용한 DP*/
/*dp[i][j]=(i, j)에서 쪽문까지 가는 경우 당근 최대 개수*/
/*단, dp[i][j]=-1인 경우 (i, j)에서 쪽문으로 가는 경로 없음*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<char>> map;
int N, M;
int sx, sy;
int dx[3] = { 1, 0, -1 };
int dy[3] = { 1, 1, 1 };
char input;
int dp[1000][1000];
int dfs_dp(int nowx, int nowy) {
	if (dp[nowx][nowy] != -2) {//이전에 한번 왔던 곳이라면
		return dp[nowx][nowy];
	}
	if (nowy == M - 1) {//정보섬 마지막 열에 도착한 경우
		if (map[nowx][nowy] == 'O') {//그곳이 쪽문이라면 탈출 가능
			return 0;
		}
		else {//쪽문이 아니라서 탈출 불가능이라서 -1 return
			return -1;
		}
	}
	int ret = -1;
	for (int i = 0; i < 3; i++) {
		int nx = nowx + dx[i];
		int ny = nowy + dy[i];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M) {//정보섬 범위
			continue;
		}
		if (map[nx][ny] == '#') {//벽
			continue;
		}
		int now = dfs_dp(nx, ny);
		if (now != -1) {//-1이 아니라는 것은 쪽문으로 나가는 경로 존재한다는 것
			if (ret == -1) {
				ret = now;
			}
			else {
				ret = max(ret, now);
			}
		}
	}
	if (ret == -1) {//열 끝까지 갔을 때 쪽문이 없는 경우
		if (map[nowx][nowy] == 'O') {//만약 현재 위치가 쪽문인 경우 탈출 가능
			ret = 0;
		}
	}
	else {//열 끝까지 갔을 때 쪽문 있는 경우
		if (map[nowx][nowy] == 'C') {//만약 현재 위치가 당근이라면 +1
			ret += 1;
		}
	}
	return dp[nowx][nowy] = ret;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		vector<char> now;
		for (int j = 0; j < M; j++) {
			cin >> input;
			if (input == 'R') {
				sx = i; sy = j;
			}
			now.push_back(input);
			dp[i][j] = -2;//dp 배열은 처음에 -2로 세팅
		}
		map.push_back(now);
	}
	cout << dfs_dp(sx, sy);
	return 0;
}