#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int b[50][50], visited_board[50][50] = {0};
int t[50][50], visited_table[50][50] = {0};
int dx[] = {-1, 1, 0 , 0};
int dy[] = {0, 0, -1, 1};
int s = 0;
struct point {
    int x;
    int y;
};
vector<point> bv, tv;
int flag = 0;
int answer = 0;

void rotate();
bool cmp(const point& a, const point& b);
int check();
void DFS(int x, int y, int main_x, int main_y, int cnt, int type);
int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    s = game_board.size();
    cout << s << endl;
    // copy
    for(int i = 0;i < s;i++){
        for (int j = 0; j < s;j++){
            b[i][j] = game_board[i][j];
            t[i][j] = table[i][j];
        }
    }
    //board의 빈칸을 중심으로 탐색
    for(int i = 0;i < s;i++){
        for(int j = 0;j < s;j++){
            // 방문하지 않은 빈 칸
            if(!visited_board[i][j] && !game_board[i][j]) {
                bv.clear();
                flag = 0;
                DFS(j, i, j, i, 1, 1);
                if(!flag){
                    for(int k = 0;k < 4;k++){
                        int c = check();
                        if(c) break;
                        rotate();
                    }
                }
            }
        }
    }
    return answer;
}


void rotate() {
    int temp[50][50];
    memcpy(temp, t, sizeof(t));
    for(int k = 0;k < s / 2;k++) {
        // 여기서 i, j는 temp의 행, 열 indexing
        for(int i = k;i < s - s / 2;i++){
            for(int j = k;j < s - s / 2;j++){
                // up
                t[j][i] = temp[s - 1 - i][j];
                // right
                t[j][s - 1 - i] = temp[i][j];
                // left
                t[s - 1 - j][i] = temp[s - 1 - i][s - 1 - j];
                // down
                t[s - 1 - j][s - 1 - i] = temp[i][s - 1 - j];
            }
        }
    }
}

bool cmp(const point& a, const point& b){
    if (a.x < b.x) return true;
    if (a.x == b.x){
        if(a.y < b.y) return true;
        else return false;
    }
    else return false;
}

int check() {
    memset(visited_table, 0, sizeof(visited_table));
    for(int i = 0;i < s;i++){
        for(int j = 0;j < s;j++){
            if(!visited_table[i][j] && t[i][j]){
                tv.clear();
                DFS(j,i,j,i,1, 2);
                if(tv.size() == bv.size()){
                    sort(tv.begin(), tv.end(), cmp);
                    sort(bv.begin(), bv.end(), cmp);

                    int tflag = 0;
                    for(int k = 0;k < tv.size();k++){
                        if(bv[k].x == tv[k].x && bv[k].y == tv[k].y) continue;
                        else {
                            tflag = 1;
                            break;
                        }
                    }
                    if (tflag) continue;

                    for(int k = 0;k < tv.size();k++) {
                        // vector에는 상대적 위치가 아니라 절대적 위치가 저장되기 때문
                        // 활용할 때는 다시 절대적 시작점 더해줘야 한다.
                        int nx = j + tv[k].x;
                        int ny = i + tv[k].y;
                        t[ny][nx] = 0;
                        answer++;
                    }
                    cout << "success" << endl;
                    // 퍼즐 맞추기 성공
                    return 1;
                }
            }
        }
    }
    return 0;
}

void DFS(int x, int y, int main_x, int main_y, int cnt, int type) {
    cout << type << " : " << x << " " << y << endl; 
    // board 탐색은 type = 1, table 탐색은 type = 2
    if (type == 1){
        bv.push_back({x - main_x, y - main_y});
        visited_board[y][x] = 1;
    }
    else {
        tv.push_back({x - main_x, y - main_y});
        visited_table[y][x] = 1;
    }
    if(cnt > 6){
        // 퍼즐조각은 최대 6개
        flag = 1;
        return;
    }
    
    for(int i = 0; i < 4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx > -1 && nx < s && ny > -1 && ny < s){
            if(type == 1 &&  !visited_board[ny][nx] && !b[ny][nx]){
                DFS(nx, ny, main_x, main_y, cnt + 1, type);
            }
            else if (type == 2 && !visited_table[ny][nx] && t[ny][nx]) {
                DFS(nx, ny, main_x, main_y, cnt + 1, type);
                if(flag) return;
            }
        }
    }
}