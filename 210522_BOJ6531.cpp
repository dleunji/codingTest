#include<iostream>
#include<string>
using namespace std;
int N;
string input;
int dp[201][201];
int check_element(int st, int ed);
int dp_set(int st, int ed);
int check_element(int st, int ed) {
	if (st == ed) {
		return dp[st][ed] = 1;
	}
	else if (st > ed) {
		return 0;
	}
	if (dp[st][ed] != -1) {
		return dp[st][ed];
	}
	if (dp_set(st, ed)) {//set
		return dp[st][ed] = 1;
	}
	for (int i = st; i <= ed; i++) {//list
		if (input.at(i) == ',') {
			if (check_element(st, i - 1) && check_element(i + 1, ed)) {
				return dp[st][ed] = 1;
			}
		}
	}
	return dp[st][ed] = 0;
}
int dp_set(int st, int ed) {
	if (st == ed) {
		return dp[st][ed] = 1;
	}
	else if (st > ed) {
		return 0;
	}
	if (dp[st][ed] != -1) {
		return dp[st][ed];
	}
	if (input.at(st) == '{' && input.at(ed) == '}') {
		if (st + 1 == ed) {//empty
			return dp[st][ed] = 1;
		}
		else if (st + 2 == ed) {//atom
			return dp[st][ed] = 1;
		}
		else if (dp_set(st + 1, ed - 1)) {//set
			return dp[st][ed] = 1;
		}
		for (int i = st+1; i <= ed-1; i++) {
			if (input.at(i) == ',') {//check "element, list", list도 결국 element로 구성
				if (check_element(st + 1, i - 1) && check_element(i + 1, ed - 1)) {
					return dp[st][ed] = 1;
				}
			}
		}
	}
	return dp[st][ed] = 0;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int a = 0; a <= 200; a++) {
			for (int b = 0; b <= 200; b++) {
				dp[a][b] = -1;
			}
		}
		if (input.length() == 1) {
			cout << "Word #" << i + 1 << ": No Set" << "\n";
		}
		else {
			if (dp_set(0, input.length() - 1)) {
				cout << "Word #" << i + 1 << ": Set" << "\n";
			}
			else {
				cout << "Word #" << i + 1 << ": No Set" << "\n";
			}
		}
	}
	return 0;
}