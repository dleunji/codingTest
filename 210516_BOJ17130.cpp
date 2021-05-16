// 래빗의 위치에 따른 Queue로 풀면 메모리 초과
// 그래서 DP로 전환
// dp[i][j] = max(dp[i-1][j-1], dp[i][j-1], dp[i+1][j-1]) + 1 (if island[i][j] == 'C')
#include <iostream>
#include <queue>
using namespace std;
char island[1001][1001];
int dp[1001][1001] = {-1,};// 초기화 : 미방문
int d[3] = {0, 1, -1};
int maxScore = -1;
int n, m;
void move(int i, int j);
int main(void){
    cin >> n >> m;
    int r = 0, c = 0;
    for(int i = 0;i < n;i++){
        cin >> island[i];
        for(int j = 0;j< m;j++){
            dp[i][j] = -1;
            if(island[i][j] == 'R'){
                r = i;
                c = j;
            }
        }
    }
    move(r,c);
    cout << maxScore << endl;
}

void move(int r, int c){
    int row, col;
    int maxBefore = -1;
    dp[r][c] = 0;
    //토끼가 있는 col+1부터 시작
    for(int j = c + 1;j < m;j++){
        for(int i = 0;i < n;i++){
            maxBefore = -1;
            //벽돌로 인해 해당 장소에 도달 불가
            if(island[i][j] == '#') continue;
            //해당 장소에 오기 전에 있었을 곳 탐색
            for(int k = 0;k < 3;k++){
                //현재 장소까지 오기 위한 직전 후보 장소 탐색
                row = i - d[k];
                col = j - 1;
                if(row < n && row >=0 && col < m && col >= 0){
                    maxBefore = max(dp[row][col], maxBefore);
                }
            }
            //해당 장소까지 올 수 있는 경로 없다.
            if(maxBefore == -1){
                continue;
            }
            if(island[i][j] == 'C'){
                maxBefore += 1;
            }
            if(island[i][j] == 'O'){
                //꼭 종료할 필요 없음
                maxScore = max(maxScore, maxBefore);
            }
            dp[i][j] = maxBefore;
        }
    }
}
