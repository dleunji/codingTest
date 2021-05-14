/*BOJ 2879*/
/*Divide and conquer*/
/*Greedy*/
/*결국 그룹 지을 수 있는 것은 연속적으로 원하는 intent 수보다 크거나 작은것들*/
/*그렇게 계속 그룹 지어서 통째로 줄이는 greedy 방법 사용*/
/*또한, 예시에서는 ..234..를 ..110..으로 만들기 위해 234를 그룹짓고 그룹이 나누어지는 일이 없지만*/
/*만약 ..324..를 ..110..으로 만들고 싶다면 divide and conquer를 사용해야 한다.*/
/*즉, 먼저 ..324..의 2가 가장 작기 때문에 ..213..이 되는데 이후 1을 기준으로 ..2, 3..으로 나눠지게 된다*/
/*그러면 ..2에 대해서 한번, 3..에 대해서 한번 해서 각각의 결과를 더하면 ..324..에 대한 최종 결과가 나온다*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int N;
int input;
vector<int> intent;
vector<int> want;
int divide(int st, int ed) {
	int res = 0;
	int idx = st;
	if (st == ed) {
		if (intent[st] == want[st]) {
			return 0;
		}
		else if (intent[st] > want[st]) {
			return intent[st] - want[st];
		}
		else {
			return want[st] - intent[st];
		}
	}
	while (1) {
		if (idx > ed) {
			break;
		}
		if (intent[idx] == want[idx]) {//같은 경우 작업 필요 없음
			idx++;
		}
		else if (intent[idx] > want[idx]) {//줄여야 하는 경우
			int gap = intent[idx] - want[idx];
			int start = idx;
			int min_idx = idx;
			int end = idx;
			idx++;
			while (1) {
				if (idx > ed) {
					end = ed;
					break;
				}
				if (intent[idx] <= want[idx]) {
					end = idx - 1;
					break;
				}
				if (intent[idx] - want[idx] < gap) {//줄여야 하는 개수가 가장 적은 곳을 중심으로 양쪽으로 divide될 예정
					gap = intent[idx] - want[idx];
					min_idx = idx;
				}
				idx++;
			}
			if (start == end) {
				intent[start] -= gap;
				res += gap;
			}
			else {
				for (int i = start; i <= end; i++) {
					intent[i] -= gap;
				}
				res += gap;
				res += divide(start, min_idx - 1);//줄여야 하는 개수가 가장 적었던 곳 중심으로 왼쪽
				res += divide(min_idx + 1, end);//줄여야 하는 개수가 가장 적었던 곳 중심으로 오른쪽
				//즉 이 부분이 divide and conquer
			}
		}
		else if (intent[idx] < want[idx]) {//늘려야 하는 경우
			int gap = want[idx] - intent[idx];
			int start = idx;
			int min_idx = idx;
			int end = idx;
			idx++;
			while (1) {
				if (idx > ed) {
					end = ed;
					break;
				}
				if (intent[idx] >= want[idx]) {
					end = idx - 1;
					break;
				}
				if (want[idx] - intent[idx] < gap) {//늘려야 하는 개수가 가장 적은 곳을 중심으로 양쪽으로 divide될 예정
					gap = want[idx] - intent[idx];
					min_idx = idx;
				}
				idx++;
			}
			if (start == end) {
				intent[start] += gap;
				res += gap;
			}
			else {
				for (int i = start; i <= end; i++) {
					intent[i] += gap;
				}
				res += gap;
				res += divide(start, min_idx - 1);//늘려야 하는 개수가 가장 적은 곳의 왼쪽
				res += divide(min_idx + 1, end);//늘려야 하는 개수가 가장 적은 곳의 오른쪽
				//즉, 이곳이 divide and conquer
			}
		}
	}
	return res;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input;
		intent.push_back(input);
	}
	for (int i = 0; i < N; i++) {
		cin >> input;
		want.push_back(input);
	}
	cout << divide(0, N - 1);
	return 0;
}