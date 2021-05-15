#include <iostream>
using namespace std;
int tabs[1000]; //이동해야하는 탭 수
int cnt = 0;
// e.g. [1,2,3,4] -> [3,1,1,0]
// tabs = [2,-1,-2,4]
// [2] / [-1,-2,-4] -> [0] / [0] / [-1,-3] -> [0] / [0] / [0] / [-2] -> [0] / [0] / [0] / [0]
// 위와같이 이분탐색으로 그룹을 나누어 tabs의 값이 모두 0이 될 때까지 최소 이동을 구한다.
void tabtab(int start, int end);
int main(void){
    int n, temp;
    cin >> n;
    for(int i =0; i < n;i++){
        cin >> tabs[i];
    }
    for(int i =0; i < n;i++){
        cin >> temp;
        tabs[i] = temp - tabs[i];
    }
    tabtab(0,n-1);
    cout << cnt << '\n';
}
// 이분 탐색을 위한 recursive func
void tabtab(int start, int end){
    if(start > end){
        return;
    }
    //시작점에 이동해야하는 tab이 없는 경우 제외함
    if(tabs[start] == 0){
        tabtab(start + 1, end);
        return;
    }
    // 분기점
    // start ~ index-1 , index ~ end로 그룹을 나누기 위함
    int index = end + 1;
    // 1은 양수, -1은 음수 의미함과 동시에 추후 연산을 간편하게 하기 위한 도구
    int flag = tabs[start] > 0 ? 1 : -1;
    // 방향과 상관없이 절대적인 이동값
    int minimum = abs(tabs[start]);
    // 그룹 내에서 최소 이동량을 지닌 인덱스
    // 만약 현 그룹에서 부호가 다른 값을 만나 그룹으로 나뉘지 않으면, min_index를 기준으로 그룹 나누어야 한다.
    int min_index = start;
    for(int i = start+1;i <= end;i++){
        // 이전 값과 부호가 같은 경우 동일 그룹으로 취급
        // 그러나 현 그룹에 부호가 다른 값인 분기점이 없는 경우 최소 이동량을 지닌 값이 추후 분기점이 되어야 하므로
        // 이를 위한 인덱스도 min_index로 표시하며 순회
        if(tabs[i-1] * tabs[i] > 0){
            if(minimum > abs(tabs[i])){
                minimum = abs(tabs[i]);
                min_index = i;
            }
        }
        // 분기점 발견
        else {
            index = i;
            break;
        }
    }
    // 같은 부호인 값까지 탭 이동
    for(int i = start;i < index;i++){
        tabs[i] -= flag * minimum;
    }
    if(index == end + 1){
        index = min_index + 1;
    }
    cnt += minimum;
    tabtab(start, index-1);
    tabtab(index, end);
    return;
}

