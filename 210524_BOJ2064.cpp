#include <iostream>
#include <string>
#define MAX_N		1000
using namespace std;

/*** 2064 :: IP 주소
- 2진수 <-> 10진수 변환
- 문자열 <-> 정수 변환

N개의 input을 문자열로 받으며 서로 다른 지점을 찾는다.
-> 서로 다른 문자열의 길이가 곧 m이 된다.
네트워크 주소는 주어진 input 중 뒤에서부터 m개를 (2진수 기준) 제거한 값이고
네트워크 마스크는 255.255.255.255 에서 뒤어서부터 m개를 제거한 값이다.
***/

int N, m = 0;
const string zeros = "00000000000000000000000000000000";
const string ones = "11111111111111111111111111111111";
string ip_addr, common = "";
int pow2[8] = { 1,2,4,8,16,32,64,128 };

int strToInt(string str) {
	int ret = 0;

	for (char c : str) {
		ret *= 10;
		ret += c - '0';
	}

	return ret;
}

int bToD(string bin) {
	int ret = 0;

	for (char c : bin) {
		ret *= 2;
		ret += c - '0';
	}

	return ret;
}

string dTob(string dec) {
	string ret = "00000000";
	for (int i = 0; i < dec.size(); i += 4) {
		int pow = 7;
		int decimal = strToInt(dec.substr(i, 4));
		while (decimal > 0) {
			while (pow2[pow] > decimal) pow -= 1;
			decimal -= pow2[pow];
			ret[7 - pow] = '1';
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> ip_addr;
		int start = 0;
		string dot_remove = "";
		for (int j = 0; j < ip_addr.size(); ++j) {
			if (ip_addr[j] == '.') {
				dot_remove += (zeros.substr(0, 3 - (j - start))
					+ ip_addr.substr(start, j - start));
				start = j + 1;
			}
		}
		dot_remove += ip_addr.substr(start, ip_addr.size() - start);
		string dot_remove_bin = "";
		for (int i = 0; i < dot_remove.size(); i += 3) {
			dot_remove_bin += dTob(dot_remove.substr(i, 3));
		}

		if (common != "") {
			int j = 0;
			while (common[j] == dot_remove_bin[j]) j += 1;
			common = dot_remove_bin.substr(0, j) + zeros.substr(0, 32 - j);
			if (32 - j > m) m = 32 - j;
		}
		else {
			common = dot_remove_bin;
		}
	}

	for (int i = 0; i < 32; i += 8) {
		cout << bToD(common.substr(i, 8));
		if (i != 24) cout << '.';
	}
	cout << '\n';

	string net_mask = ones.substr(0, 32 - m) + zeros.substr(0, m);
	for (int i = 0; i < 32; i += 8) {
		cout << bToD(net_mask.substr(i, 8));
		if (i != 24) cout << '.';
	}


	return 0;
}