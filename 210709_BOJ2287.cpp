/**
 *최소 K-표현수 길이가 8보다 크면 NO 이기 때문에 int 범위 내에서 해결 가능
 *즉 dp의 길이는 최대 8. 그 이상은 필요가 없다.
 *표현길이 최소화를 위해 중복되는 연산을 최소화해야한다.
 *다행히도 표현의 결과는 식이 아니라 결과값이다.
 */
#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;
int arr[1000];
unordered_set<int> dp[9];
void mono_digital(int a);

int main(void){
    int k,n;
    int cnt = 1;
    int tmp;
    
    cin >> k >> n;
    tmp = k;
    for(int i = 0;i < n;i++) {
        cin >> arr[i];
    }
    //e.g. k = 5
    //5, 55, 555...
    while(cnt < 9){
        dp[cnt++].insert(tmp);
        tmp = tmp * 10 + k;
    }
    // 표현의 길이가 i인 자연수 집합의 k번째 원소와
    // 표현의 길이가 j인 자연수 집합의 s번째의 원소를 사칙연산한 값을 i + j번째 집합에 넣어준다.
    for(int i = 1;i < 8;i++){
        for(int j = 1;j < 8;j++){
            if(i + j > 8)
                continue;
            for(auto k = dp[i].begin();k != dp[i].end();k++){
                for(auto s = dp[j].begin();s != dp[j].end();s++){
//                    cout << *k << " " << *s << endl;
                    dp[i + j].insert(*k + *s);
                    dp[i + j].insert(*k * *s);
                    // 두 원소를 뺀 결과가 0이면 안된다.
                    // 음수인 경우에는 두 원소를 바꾸면 양수가 되기에 절대값을 취해주면 된다.
                    if(abs(*k - *s)){
                        dp[i + j].insert(abs(*k - *s));
                    }
                    // 나누기에서는 결과가 0이면 안된다. 큰 수를 작은 수로 나눈다.
                    if(min(*k, *s)){
                        dp[i + j].insert(max(*k, *s) / min(*k, *s));
                    }
                }
            }
        }
    }
    
    for(int i = 0;i < n;i++){
        mono_digital(arr[i]);
    }
}

void mono_digital(int a){
    bool pass = false;
    for(int i = 1;i <= 8;i++){
        if(dp[i].find(a) != dp[i].end()){
            pass = true;
            cout << i << '\n';
            break;
        }
    }
    if(!pass){
        cout << "NO" << '\n';
    }
}
