/*BOJ 21276*/
/*map & topological sort*/
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int N, M;
string input;
string x, y;
vector<string> name;
map<string, int> order;
vector<vector<int>> relation(1000);
queue<int> q;
vector<string> ancestor;
vector<vector<string>> children(1000);
int indegree[1000];
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input;
		name.push_back(input);
	}
	sort(name.begin(), name.end());
	for (int i = 0; i < N; i++) {
		order[name[i]] = i;//string 이름을 index와 매칭
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		relation[order[y]].push_back(order[x]);//relation[y]=x는 x->y, 나의 조상들을 표시
		indegree[order[x]] += 1;//indegree는 말그대로 나의 조상의 개수
	}
	for (int i = 0; i < N; i++) {
		if (indegree[i] == 0) {//조상이 없다는 것은 각 가문의 시조, tree의 root
			ancestor.push_back(name[i]);
			q.push(i);
		}
	}
	while (!q.empty()) {//topological sort 진행
		int idx = q.front();
		q.pop();
		vector<int> now = relation[idx];
		for (int i = 0; i < now.size(); i++) {
			indegree[now[i]] -= 1;
			if (indegree[now[i]] == 0) {//1 감소했을 때 0이 되었다는 것은 더 이상 나에게 들어오는 것이 없으며 0이 될 때 제거되는 조상이 나의 직속 부모
				q.push(now[i]);
				children[idx].push_back(name[now[i]]);
			}
		}
	}
	cout << ancestor.size() << "\n";
	for (int i = 0; i < ancestor.size(); i++) {
		cout << ancestor[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < N; i++) {
		cout << name[i] << " " << children[i].size() << " ";
		vector<string> now = children[i];
		sort(now.begin(), now.end());
		for (int i = 0; i < now.size(); i++) {
			cout << now[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}