/*BOJ 16890*/
/*string*/
/*string 연결시 front=front+new 이렇게 하면 시간초과 발생*/
/*string 연결시 front+=new 이렇게 해야 시간초과 발생하지 않음*/
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string koo, cube;
int N;
string front, back;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> koo >> cube;
	sort(koo.begin(), koo.end());//구사과는 사전순 빠른 것을 원하므로 오름차순
	sort(cube.begin(), cube.end(), greater<>());//큐브러버는 사전순 느린 것을 원하므로 내림차순
	int N = koo.size();
	front = "";
	back = "";
	int koo_fidx, cube_fidx, koo_bidx, cube_bidx;
	koo_fidx = cube_fidx  = 0;
	koo_bidx = (N + 1) / 2 - 1;//구사과 먼저 놓기 때문에 오름차순 결과 앞에서부터 (N+1)/2개 만큼 사용
	cube_bidx = N / 2 - 1;//큐브러버는 내림차순 결과 앞에서부터 N/2개만큼 사용
	for (int i = 0; i < N; i++) {
		if (i % 2 == 0) {//구사과
			if (koo.at(koo_fidx) < cube.at(cube_fidx)) {//구사과의 제일 작은 문자가 큐브러버의 제일 큰 문자보다 작으면 최대한 앞으로
				front += koo.at(koo_fidx); koo_fidx++;
			}
			else {//구사과의 제일 작은 문자가 큐브러버의 제일 큰 문자보다 크거나 같으면 최대한 뒤로
				back = koo.at(koo_bidx) + back; koo_bidx--;
			}
		}
		else {//큐브러버
			if (cube.at(cube_fidx) > koo.at(koo_fidx)) {//큐브러버의 제일 큰 문자가 구사과의 제일 작은 문자보다 크면 최대한 앞으로
				front += cube.at(cube_fidx); cube_fidx++;
			}
			else {//큐브러버의 제일 큰 문자가 구사과의 제일 작은 문자보다 작거나 같으면 최대한 뒤로
				back = cube.at(cube_bidx) + back; cube_bidx--;
			}
		}
	}
	cout << front << back;
	return 0;
}