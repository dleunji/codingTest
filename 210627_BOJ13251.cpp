/*BOJ 13251*/
/*Combination*/
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
int M, K, input, N;
double res = 0;
vector<int> color;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> M;
	N = 0;
	for (int i = 0; i < M; i++) {
		cin >> input;
		color.push_back(input);
		N += input;
	}
	cin >> K;
	for (int i = 0; i < M; i++) {
		double tmp = 1;
		if (color[i] >= K) {
			for (int j = 0; j < K; j++) {
				tmp *= (double)(color[i] - j) / (double)(N - j);
			}
			res += tmp;
		}
	}
	printf("%.18lf", res);
	return 0;
}