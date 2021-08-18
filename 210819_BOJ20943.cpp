/**
 두 직선이 평행하기 위해서는 기울기 -a/b만 일치하지 않으면 된다는 점에서 접근
 */
#include <iostream>
#include <unordered_map>
using namespace std;
long long vertical = 0;
unordered_map<double, long long> map;
long long coupling(long long n) {
    return n * (n - 1) / 2;
}
int main(void) {
    int n;
    long long a, b, c;
    long long answer = 0;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> a >> b >> c;
        if(b == 0) {
            vertical++;
        }
        else if (map.find(- a / (double) b) != map.end()){
            map[-a/(double)b]++;
        } else {
            map[-a/(double)b] = 1;
        }
    }
    // 분류된 키를 이중 for문으로 돌면서 평행하지 않은 선분들의 조합을 구하는 것보다
    // 하나의 key 그룹을 방문할 때마다 평행한 선분의 조합을 구하는 것이 빠르다..
    answer = coupling(n) - coupling(vertical);
    for(auto key: map){
        answer -= coupling(key.second);
    }
    cout << answer;
}
