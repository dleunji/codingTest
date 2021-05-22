#include <iostream>
#include <string>
using namespace std;

bool checkSet(string str);
bool checkElem(string elem);

/*** 6531 :: �̷� ������ ��ġ������ �ذ��� �� �־� ***
���ڿ� ó��
������ ����: ',' '{' '}' �Ǵ� ������B
������ ����: {,}   {{}   {}}   {}

(1) ���� �־��� ���ڿ��� �� ���� {�� }�� �ѷ��ο� �ִ��� Ȯ���Ѵ�.
(2) �� �� ���� ��ȣ�� ������ �κ� ���ڿ��� ���ҵ� �Ǵ� ���յ�θ� �̷���� �ִ��� Ȯ���Ѵ�.
	a. ���� �� ���� ������ ���� �Ǵ� �� ���� ������ ���� �� �ϳ����� Ȯ���Ѵ�.
	b. �ϰ����� ���� �� �ϳ����� Ȯ�εǸ� �� ������ ������(,)�� ������ Ȯ���Ѵ�.
	c. ������(,)�� ����� ��ġ�ϰ� �ִٸ� �� ���� ���ڿ��� ���Ͽ� a~b�� �ݺ��Ѵ�.
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