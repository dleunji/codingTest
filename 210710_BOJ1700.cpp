/**
 * 굉장히 출제 가능성이 높은 유형인 Greedy Algorithm
 * 고려할 사항
 * 1) 해당 기기가 플러그에 꽂혀있는 경우
 * 2) 플러그에 빈 곳이 있는 경우
 * 3) 플러그에 빈 곳이 있는 경우
 *
 * 1)과 2)의 경우 콘센트를 뺄 필요가 없다.
 *
 * 3)의 경우에는 어떻게 콘센트를 뺄 지 Greedy Rule을 정해야 한다.
 * - 이후에 단 한 번도 쓰지 않을 기기나 제일 마지막에 쓰이는 기기를 빼는 것이 최적
 * - 뺀 다음에 사용 예정인 기기의 플러그를 꽂는다.
 */
#include <iostream>
#include <algorithm>
#define MAXNUM 101

using namespace std;

int n,k;
int schedule[MAXNUM], plug[MAXNUM];
int main(void){
    int result = 0;
    int idx = -1, device_idx, last_idx;
    // n : 멀티탭 구멍의 개수
    // k : 전기용품의 총 사용 횟수
    cin >> n >> k;
    for(int i = 0;i < k;i++){
        cin >> schedule[i];
    }
    for(int i = 0;i < k;i++){
        // 이미 꽂혀있으면 continue하기 위해
        bool is_plugged_in = false;
        for(int j = 0;j < n;j++){
            if(plug[j] == schedule[i]){
                is_plugged_in = true;
                break;
            }
        }
        if(is_plugged_in)
            continue;
        // 플러그에 빈 곳이 있으면 continue하기 위해
        for(int j = 0;j < n;j++){
            if(!plug[j]){
                plug[j] = schedule[i];
                is_plugged_in = true;
                break;
            }
        }
        if(is_plugged_in)
            continue;
        //이제 뺄 플러그를 선택해야 한다.
        //이를 위해 가장 나중에 사용되거나 앞으로 사용되지 않는 플러그를 찾는다.
        device_idx = -1;
        for(int j = 0;j < n;j++){
            last_idx = 0;
            //현재 꽂을 플러그 이후에 꽂아야할 플러그를 탐색하며
            for(int s = i + 1;s < k;s++){
                if(plug[j] == schedule[s]) {
                    break;
                }
                last_idx++;
            }
            if(last_idx > device_idx){
                //더 나중에 쓰이는 플러그 발견하면 reset
                idx = j;
                device_idx = last_idx;
            }
            
        }
        result++;
        plug[idx] = schedule[i];
    }
    cout << result <<'\n';
}

