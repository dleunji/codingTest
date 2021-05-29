/**
* 컴퓨터의 IP에 서브넷 마스크를 AND 연산 -> 네트워크 주소
* 서브넷 마스크 : 네트워크 부분은 1, 호스트 부분은 0
* 비트마스크 문제는 거의 안 풀어봤더니 어렵더라..
*/

#include <iostream>
void print(int bits);
using namespace std;
int ip[1000];   //int : 4bytes => 32bits
int main(void){
    int n, tmp;
    int flag = 0;
    cin >> n;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < 4;j++){
            cin >> tmp;
            ip[i] <<= 8;
            ip[i] |= tmp;
            //엔터 제거
            getchar();
        }
    }
    int subnet = 0;
    // 0 ~ 31 비트부터 점검 - ip 중에 1이 아닌 경우가 있으면 체크
    // 달라지는 비트 전까지는 서브넷은 1로 채운다
    for(int i = 31;i >=0;i--){
        //i번째 비트 추출
        int bit = 1 << i;
        // 0 ~ n까지 누적으로 동일 여부 판단
        for(int j = 0;j < n;j++){
            if((ip[0] & bit) != (ip[j] & bit)){
                flag = 1;
                break;
            }
        }
        if(flag)  break;
        else subnet |= bit;
    }
    //32비트 출력
    print(ip[0] & subnet);
    print(subnet);
}
void print(int bits){
    int shift = 24;
    for(int i = 0;i < 4;i++){
        // 8비트씩 & 1111111
        cout << ((bits >> shift) & (1 << 8) - 1);
        if(i!=3) cout << ".";
        shift -= 8;
    }
    cout << "\n";
}