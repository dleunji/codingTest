/**
 * 경우의 수를 다 구해서 확률을 구하는 방식은 비효율적
 * (aCk + bCk + cCk..) / nCk
 * 따라서 확률로 미리 만들어둔 수를 활용
 * n은 조약돌의 총 개수
 */
#include <iostream>
using namespace std;
int colors[50];
double p[50];
int main(void){
    int m, n = 0, k;
    double answer = 0;
    cin >> m;
    for(int i = 0;i < m;i++) {
        cin >> colors[i];
        n += colors[i];
    }
    cin >> k;
    for(int i = 0;i < m;i++) {
        if(colors[i] < k) {
            continue;
        }
        double temp = 1.0;
        for(int j = 0;j < k;j++) {
            temp *= (double) (colors[i] - j) / (n - j);
        }
        p[i] = temp;
    }
    for(int i = 0 ;i < m;i++) {
        answer += p[i];
    }
    cout << fixed;
    cout.precision(18);
    cout << answer;
}