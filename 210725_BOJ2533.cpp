/**
 * DP + DFS
 * graph를 tree로 단방향화(parent->child)
 * dp[root][0,1] = 해당 root포함 child가 최소 필요 친구 얼리어답터의 수
 * 0이면 root가 얼리어답터 X, 1이면 얼리어답터 O 
 **/
#include <iostream>
#include <bits/stdc++.h>
#define MAX 1000001

using namespace std;

vector <int> tree[MAX];
vector <int> graph[MAX];
int dp[MAX][2];
bool visited[MAX];

void make_tree(int parent);
int dfs(int curr, int state);

int main() {
    int n, a, b;
	cin >> n;
	for (int i = 0;i < n;i++) {
	    cin >> a >> b;
	    graph[a].push_back(b);
	    graph[b].push_back(a);
	}
	memset(visited, false, sizeof(visited));
	// Make Tree for DFS
	make_tree(1);
	// DFS
	memset(dp, -1, sizeof(dp));
	int result1 = dfs(1,0);
	int result2 = dfs(1,1);

	cout << min(result1, result2);
}

void make_tree(int parent){
    visited[parent] = true;
    for(int i = 0;i < graph[parent].size();i++){
        int child = graph[parent][i]; 
        if(visited[child] == false){
            tree[parent].push_back(child);
            make_tree(child);
        }
    }
}

int dfs(int parent, int state){
    int child = 0;
    //dp의 대표적인 활용방식!! -> o(n)
    if(dp[parent][state] != -1) return dp[parent][state];
    //parent isn't earlyadapter
    if(state == 0){
        dp[parent][state] = 0;
        for(int i = 0;i < tree[parent].size();i++){
            child = tree[parent][i];
            dp[parent][state] += dfs(child, 1);
        }
    }
    //parent is earlyadapter
    else {
        dp[parent][state] = 1;
        for(int i = 0;i < tree[parent].size();i++){
            child = tree[parent][i];
            dp[parent][state] += min(dfs(child,0), dfs(child,1));
        }
    }
    return dp[parent][state];
}
