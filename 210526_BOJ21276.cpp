/** 처음에는 단순히 가문만 비교하기 위해 union-find를 쓰다가
* 조상세대와 후손세대를 순서대로 열거해야하기 때문에 그래프를 사용하여 이를 구분한다.
* 그리고 이 시조부터 시작해서 link를 제거하며 후손 노드를 찾아나간다.
* 위상정렬
* 네이밍을 잘하자. 그리고 배열 내용이 헷갈리면 시간을 많이 날린다...기록하거나 잘 기억해두자
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;
vector<vector<int>> G(1000);         // vector 메모리 할당
vector<vector<int>> children(1000);  // 가문별 후손 입력
int indegree[1000];
vector <string> names;
map<string, int> hashmap;       //인덱스와 이름 매치(사전순)
queue <int> q;
vector<int> grand;
int main(void){
  int n, m;
  int cur;
  string name;
  string child, parent;
  cin >> n;
  for(int i = 0; i < n;i++){
    cin >> name;
    names.push_back(name);
  }
  sort(names.begin(), names.end());
  for(int i = 0 ;i < n;i++){
    hashmap[names[i]] = i;
  }
  cin >> m;
  for(int i = 0;i < m;i++){
    cin >> child >> parent;
    int u = hashmap[child];
    int v = hashmap[parent];
    // 조상 -> 후손
    // v -> u
    G[v].push_back(u);
    indegree[u]++;
  }
  for(int i = 0; i < n;i++){
    // 시조
    if(indegree[i] == 0){
      grand.push_back(i);
      q.push(i);
    }
  }
  while(!q.empty()){
    cur = q.front();
    q.pop();
      //후손은 또다른 후손의 조상이므로 큐에 입력
    for(auto c: G[cur]){
      indegree[c]--;
      // 후손 중 자식만 출력하기 때문
      if(indegree[c] == 0){
          children[cur].push_back(c);
          q.push(c);
      }
    }
  }

  cout << grand.size() << '\n';
  for(int i = 0 ;i < grand.size();i++){
    cout << names[grand[i]] << " ";
  }
  cout << "\n";
  for(int i = 0 ;i < n;i++){
    cout << names[i] << " " << children[i].size() << " ";
    sort(children[i].begin(), children[i].end());
    for(int j = 0; j < children[i].size();j++){
      cout << names[children[i][j]] << " ";
    }
    cout << "\n";
  }
}
