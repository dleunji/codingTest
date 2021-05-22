#include <iostream>
#include <string>
using namespace std;

bool checkSet(string str);
bool checkElem(string elem);

/*** 6531 :: 이런 문제는 유치원생도 해결할 수 있어 ***
문자열 처리
가능한 원소: ',' '{' '}' 또는 공집합B
가능한 집합: {,}   {{}   {}}   {}

(1) 먼저 주어진 문자열의 양 끝이 {와 }로 둘러싸여 있는지 확인한다.
(2) 양 끝 집합 기호를 제외한 부분 문자열이 원소들 또는 집합들로만 이루어져 있는지 확인한다.
	a. 위의 네 가지 종류의 집합 또는 세 가지 종류의 원소 중 하나인지 확인한다.
	b. 일곱가지 유형 중 하나임이 확인되면 그 다음에 구분자(,)가 오는지 확인한다.
	c. 구분자(,)가 제대로 위치하고 있다면 그 다음 문자열에 대하여 a~b를 반복한다.
***/

bool checkElem(string elem) {
	bool ret = false;
	int len = elem.length();
	// check element
	// {{}   {}}   {,}   {}   ,   {    }
	for (int i = 0; i < len;) {
		// (2).b
		if (ret) {
			if (elem[i] == ',') {
				ret = false;
				++i;
			}
			else return false;
		}
		// (2).a
		else {
			if (elem[i] == '{') {
				if (i + 2 < len) {
					if (elem[i + 1] == '{' && elem[i + 2] == '}') {
						ret = true;
						i += 3;
						continue;
					}
					else if (elem[i + 1] == '}' && elem[i + 2] == '}') {
						ret = true;
						i += 3;
						continue;
					}
					else if (elem[i + 1] == ',' && elem[i + 2] == '}') {
						ret = true;
						i += 3;
						continue;
					}
				}
				if (i + 1 < len) {
					if (elem[i + 1] == '}') {
						ret = true;
						i += 2;
						continue;
					}
				}

				for (int closing = i + 1; closing < len; ++closing) {
					if (elem[closing] == '}' && checkSet(elem.substr(i, closing - i + 1))) {
						ret = true;
						i = closing + 1;
						continue;
					}
				}

				ret = true;
				i += 1;
				continue;
			}
			else if (elem[i] == '}') {
				ret = true;
				i += 1;
				continue;
			}
			else if (elem[i] == ',') {
				ret = true;
				i += 1;
				continue;
			}
			else return false;
		}
	}
	return ret;
}



// {{{{,},,},},,}}

bool checkSet(string str) {
	int len = str.length();

	if (len < 2)
		return false;
	else if (str[0] != '{' || str[len - 1] != '}')
		return false;
	else if (len == 2)
		return true;

	string inside = str.substr(1, len - 2);
	if (checkSet(inside) || checkElem(inside)) return true;
	return false;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N;
	string str;

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> str;
		bool isSet = false;

		isSet = checkSet(str);

		cout << "Word #" << i << ": ";
		if (isSet) cout << "Set";
		else cout << "No Set";
		if (i != N) cout << '\n';
	}

	return 0;
}