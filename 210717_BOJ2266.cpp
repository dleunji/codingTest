/**
 *(n,k)에서 i번째 높이에서 금고를 떨어뜨린다고 가정
 *깨지면 (i-1, k-1) + 1
 *안 깨지면 (n-i, k) + 1
 *이 중 최악의 경우를 생각해야하므로 i번째 높이에서 최소한의 금고 낙하 횟수는 max((i-1, k-1),(n-i, k)) + 1
 *가능한 i 중 최소 낙하 횟수는 E(n,k) = min((n,k), max((i-1, k-1),(n-i, k)) + 1)
 *DP를 익힐 수 있는 좋은 문제였다..
 *ex) n = 2, k = 2 => 1층에서만 던져서 깨지면 F = 0 or 1 => 한 번 더 던져봐야 정확히 알 수 있다.
 *ex) n = 3, k = 2 => 2층에서 던져보고 깨지면 (1,1)+1(1층에서만 한 번 더 던져보면 알 수 있다) , 안깨지면 (1,2) + 1 (이미 3층인 거 답 나왔다)
 */
#include <iostream>
#include <algorithm>

using namespace std;
int dp[501][501];
int main(void){
    int n,k;
    cin >> n >> k;
    for(int i = 1;i <= n;i++) dp[i][1] = i;
    for(int i = 1;i <= n;i++){
        for(int j = 2;j <= k;j++){
            dp[i][j] = 1e8;
            for(int s = 1;s <= i;s++){
                dp[i][j] = min(dp[i][j], max(dp[s-1][j-1], dp[i-s][j]) + 1);
            }
        }
    }
    cout << dp[n][k] << endl;
}
