#include <cstdio>
#define MAX_SZ	1005
#define EMPTY	'.'
#define WALL	'#'
#define RABBIT	'R'		// [!] �ݵ�� �ϳ��� �־�����.
#define CARROT	'C'
#define DOOR	'O'		// [!] ���ų� ���� ���� �� �ִ�. 

/***  17130 :: �䳢�� �������� �ö�� ����
1. ���븦 ���ϵ� -> �䳢�� ��������� ������ ������ �����Ƿ�(������) �� ������ ���x
2. ���� ���� ����� �ֿ��� �Ѵ�.
��� ����� ���� ����ؾ� �ϹǷ� Memoization �� Ȱ���Ͽ� ���� ��θ� �ٽ� Ž������ �ʵ��� �Ѵ�.
-> Dynamic Programming
***/

struct Point {
	int y, x;
};

int N, M, DOOR_NUM = 0;
char map[MAX_SZ][MAX_SZ] = { WALL, };
Point START;
Point wayOut[MAX_SZ * MAX_SZ];

int dp[MAX_SZ][MAX_SZ];		// dp[i][j] = (i, j) ��ǥ�� �䳢�� ��ġ�� �� ȹ���� �ִ� ��� ��

int max3(int a, int b, int c) {
	if (a < b) {
		return b < c ? c : b;
	}
	else {
		return a < c ? c : a;
	}
}

int solve(int i, int j) {
	if (map[i][j] == RABBIT) return 0;
	if (j <= START.x) return -1;				// �䳢�� �������� �̵��� �� ����. 
	if (map[i][j] == WALL) return -1;
	if (dp[i][j] != -1) return dp[i][j];

	dp[i][j] = max3(solve(i - 1, j - 1), solve(i, j - 1), solve(i + 1, j - 1));
	if (map[i][j] == CARROT) dp[i][j] += 1;

	return dp[i][j];
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
			if (map[i][j] == DOOR) {
				wayOut[DOOR_NUM].y = i;
				wayOut[DOOR_NUM].x = j;
				DOOR_NUM++;
			}
		}
	}

	if (DOOR_NUM == 0) {
		// no way out
		printf("%d", -1);
	}
	else {
		// check the carrot number for each door
		int maxCarrot = -1;
		for (int i = 0; i < DOOR_NUM; ++i) {
			int y = wayOut[i].y;
			int x = wayOut[i].x;
			if (maxCarrot < solve(y, x)) maxCarrot = dp[y][x];
		}
		printf("%d", maxCarrot);
	}

	return 0;
}