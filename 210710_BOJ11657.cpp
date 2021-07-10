/* BOJ 11657*/
/*Bellman Ford*/
#include<iostream>
#include<vector>
using namespace std;
typedef struct _info {
	int start;
	int end;
	int time;
}info;
int N, M, A, B, C;
vector<info> edge;
long long int dist[501];
int bellman_ford(void) {
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < edge.size(); j++) {
			int st = edge[j].start;
			int ed = edge[j].end;
			int time = edge[j].time;
			if (dist[st] != 1e9) {
				if (dist[ed] > dist[st] + time) {
					if (i == N) {
						return -1;
					}
					else {
						dist[ed] = dist[st] + time;
					}
				}
			}
		}
	}
	return 1;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		edge.push_back({ A, B, C });
	}
	for (int i = 1; i <= N; i++) {
		dist[i] = 1e9;
	}
	dist[1] = 0;
	int infinite=bellman_ford();
	if (infinite == -1) {
		cout << -1;
	}
	else {
		for (int i = 2; i <= N; i++) {
			if (dist[i] == 1e9) {
				cout << -1 << "\n";
			}
			else {
				cout << dist[i] << "\n";
			}
		}
	}
	return 0;
}}
