#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(void){
    string koo, cube;
    char result[300000];
    
    // turn = 0이면 구사과 차례, 1이면 큐브러버 차례
    int turn = 0;
    cin >> koo >> cube;
    int n = (int) koo.size();
    
    // kfront, kback : 구사과의 front, back
    // cfront, cback : 큐브러버의 front, back
    int kfront = 0, cstart = 0;
    int kback = (n + 1) / 2 - 1;
    // n = 1인 경우 대비
    int cback = n / 2 - 1 >= 0 ? n / 2 - 1 : 0;
    
    sort(koo.begin(), koo.end());
    sort(cube.begin(), cube.end(), greater<>());
    int front = 0, back = n-1;
    while(front <= back){
        if(turn == 0){
            // 만약 구사과의 가장 작은 값이 큐브러버의 가장 큰값보다 작을 때,
            // 구사과의 가장 작은 값을 result의 front에 insert
            if(koo[kfront] < cube[cstart]){
                result[front] = koo[kfront];
                front++;
                kfront++;
            }
            // 만약 구사과의 가장 작은 값이 큐브러버의 가장 큰값보다 크거나 같을 때,
            // 구사과의 가장 큰 값을 result의 back에 insert
            // 큐브러버의 값들이 앞에 가는 게 구사과에게 유리하기 때문.
            else {
                result[back] = koo[kback];
                back--;
                kback--;
            }
            turn = 1;
        }
        else {
            //vice versa
            if(cube[cstart] > koo[kfront]){
                result[front] = cube[cstart];
                front++;
                cstart++;
            }
            else {
                result[back] = cube[cback];
                back--;
                cback--;
            }
            turn = 0;
        }
    }
    for(int i = 0;i < n;i++){
        cout << result[i];
    }
}
