#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef struct _trie trie;
struct _trie {
	char num;
	vector<trie> children;

	int size() {
		return (int)this->children.size();
	}
};

bool insert(trie *root, string str) {
	int idx = 0;
	vector<trie> *cur = &(root->children);

	// 문자가 같을 때까지 탐색
	bool flag = true;
	while (idx < str.length() && flag && (*cur).size() > 0) {
		if (str[idx] == '*') return false;
		for (int i = 0; i < (*cur).size(); ++i) {
			trie t = (*cur)[i];
			if (t.num == '*') return false;
			else if (t.num == str[idx]) {
				cur = &((*cur)[i].children);
				idx += 1;
				break; // break for loop
			}
			else if (i == (*cur).size() - 1) flag = false; // 같은 문자열이 없다면 종료
		}
	}

	while (idx < str.length()) {
		trie *newTrie = new trie; 
		newTrie->num = str[idx];
		(*cur).push_back(*newTrie);
		idx += 1;
		cur = &(((*cur)[(*cur).size() - 1]).children);
	}

	return true;
}

// trie
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	//freopen("phone_in.txt", "r", stdin);

	int t, n;
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		cin >> n;
		string str;
		bool res = true;

		trie *root = new trie;
		root->num = '*';

		for (int j = 0; j < n; ++j) {
			cin >> str;

			if (res) {
				str.append("*");
				res = (res && insert(root, str));
			}
		}
		if (res) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
