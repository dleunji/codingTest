/**
 * 1,2,3 나누어진 경우의 수가 있으므로 DP와 유사하다고 생각
 * 그런데 사람들 대부분 BFS로 푼 거 같아서 따라 풀었다..
 * 아무래도 visited 배열로 단순히 방문 여부만 따질 게 아니라 DP 풀이용으로서 풀어야겠다는 생각이 들었다.
 * dp[display][clipboard]  + 1= dp[display + clipboard][clipboard] / dp[display][display] / dp[display - 1][clipboard] 구조 활용
 */
#include <iostream>
#include <queue>
#include <cstring>
#define MAX 1000 + 1
using namespace std;
struct component {
    int display;
    int clipboard;
    int time;
};
int s;
// [display][clipboard]
bool visited[MAX][MAX];
int bfs();
int main(void){
    cin >> s;
    cout << bfs();
}

int bfs() {
    queue<component> q;
    q.push({1,0,0});
    visited[1][0] = true;

    while(!q.empty()){
        int display = q.front().display;
        int clipboard = q.front().clipboard;
        int time = q.front().time;
        q.pop();
        if (display == s) {
            return time;
        }
        // 1. 화면에 있는 이모티콘을 모두 복사해서 클립보드에 저장한다.
        // display = 0인 경우까지 가지 않는다.. 왜냐면 2 <= S <= 1000이기 때문.
        if(display > 0 && display < MAX){
            if(!visited[display][display]){
                visited[display][display] = true;
                q.push({display, display, time + 1});
            }
            // 2. 클립보드에 있는 모든 이모티콘을 화면에 붙여넣기 한다.
            if(clipboard > 0 && display + clipboard < MAX){
                if(!visited[display + clipboard][clipboard]){
                    visited[display + clipboard][clipboard] = true;
                    q.push({display + clipboard, clipboard, time + 1});
                }
            }
            // 3. 화면에 있는 이모티콘 중 하나를 삭제한다.
            if(!visited[display - 1][clipboard]){
                visited[display - 1][clipboard] = true;
                q.push({display - 1, clipboard, time + 1});
            }
        }
    }
    return 0;
}
