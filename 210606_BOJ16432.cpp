#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> cakes;
int n, m;
//0은 초기화이고, 1 ~ 1000일
int check[1001][10];
int answer[1001];
int flag = 0;
void dfs(int day, int prev);
int main(void){
    vector<int> cake;
    int c;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> m;
        for(int j = 0;j < m;j++) {
            cin >> c;
            cake.push_back(c);
        }
        cakes.push_back(cake);
        cake.clear();
    }
    dfs(0,0);
    if(!flag){
        cout << -1;
    }
}

void dfs(int day, int prev){
    if(day == n){
        for(int i = 1;i <= n;i++){
            cout << answer[i] << "\n";
        }
        flag = 1;
        return;
    }
    for(int i = 0; i < cakes[day].size();i++) {
        int cake = cakes[day][i];
        // 이미 이전에 day+1날에 cake를 택해서 그 경우가 통했다면 이미 종료했을 것이다.
        if(cake != prev && check[day+1][cake] == 0){
            check[day+1][cake] = 1;
            answer[day+1] = cake;
            if(flag) return;
            dfs(day+1, cake);
        }
    }
}