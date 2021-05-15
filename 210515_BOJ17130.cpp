#include <cstdio>
#define MAX_SZ	1005
#define EMPTY	'.'
#define WALL	'#'
#define RABBIT	'R'		// [!] 반드시 하나만 주어진다.
#define CARROT	'C'
#define DOOR	'O'		// [!] 없거나 여러 개일 수 있다. 

/***  17130 :: 토끼가 정보섬에 올라온 이유
1. 늑대를 피하되 -> 토끼의 진행방향은 무조건 정해져 있으므로(오른쪽) 이 조건은 고려x
2. 가장 많은 당근을 주워야 한다.
모든 경우의 수를 고려해야 하므로 Memoization 을 활용하여 같은 경로를 다시 탐색하지 않도록 한다.
-> Dynamic Programming
***/

struct Point {
	int y, x;
};

int N, M;
char map[MAX_SZ][MAX_SZ] = { WALL, };
Point START;

int dp[MAX_SZ][MAX_SZ];		// dp[i][j] = (i, j) 좌표에 토끼가 위치할 때 획득한 최대 당근 수

int max3(int a, int b, int c) {
	if (a < b) {
		return b < c ? c : b;
	}
	else {
		return a < c ? c : a;
	}
}

int main() {
	scanf("%d %d", &N, &M);

	START.y = START.x = -1;
	for (int i = 0; i <= N + 1; ++i) {
		for (int j = 0; j <= M + 1; ++j) {
			// init dp
			dp[i][j] = -1;

			// out of range 
			if (i == 0 || j == 0 || i == N + 1 || j == M + 1) {
				map[i][j] = WALL;
				continue;
			}

			// fill map info
			scanf(" %c", &map[i][j]);
			if (map[i][j] == RABBIT) {
				START.y = i; START.x = j;
			}
		}
	}

	dp[START.y][START.x] = 0;
	int maxCarrot = -1;

	for (int j = START.x + 1; j <= M; ++j) {
		for (int i = 1; i <= N; ++i) {
			if (map[i][j] == WALL) continue;

			dp[i][j] = max3(dp[i - 1][j - 1], dp[i][j - 1], dp[i + 1][j - 1]);
			if (dp[i][j] == -1) continue;
			if (map[i][j] == CARROT) dp[i][j] += 1;
			if (map[i][j] == DOOR) {
				// check the carrot number for each door
				if (maxCarrot < dp[i][j]) maxCarrot = dp[i][j];
			}
		}
	}

	printf("%d", maxCarrot);

	return 0;
}
