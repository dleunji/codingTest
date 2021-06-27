/**
 * n = 학생 수
 * A = 중간고사 점수가 나보다 높고, 기말고사 점수도 나보다 높다.
 * B = 중간고사 점수가 나보다 높지만, 기말고사 점수가 나보다 낮다.
 * C = 중간고사 점수가 나보다 낮지만, 기말고사 점수도 나보다 높다.
 * D = 중간고사 점수가 나보다 낮고, 기말고사 점수도 나보다 낮다.
 * k등 : 내 위로 k - 1명 있고, 아래로 n - k명 있다.
 * 중간고사에서 x등, 기말고사에서 y등 했다면?
 * A + B + C + D = n -1
 * B - C = n - 1 - A - D - 2C
 * = n - 1 - (A + C) - (C + D)
 * = n - 1 - (y - 1) - (n - x)
 * = x - y
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <pair<int,int>> students;
int main(void){
    int n, mid;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> mid;
        students.push_back(make_pair(mid, i+1));
    }
    sort(students.begin(), students.end());
    for(int i= 0;i < n;i++){
        cout << students[i].first - students[i].second << '\n';
    }
}