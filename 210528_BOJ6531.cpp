/** 쉼표 전에 element인지를 반복적으로 점검
 * set = {} or {elementlist}
 * elementlist = element or element, element, element, element
 * 단순한 일방향적인 dp가 아니라 양방향적인 dp를 사용하여 set, element 여부 판단
 * 분할 정복 + DP
 * string parsing 하면 double quotes가 아니라 single quotes로! 문자열 -> 문자
 */

#include <iostream>
#include <string>
int isSet(int start, int end);
int isElem(int start, int end);

using namespace std;
int dp[200][200];   //dp[a][b] = a ~ b의 set 여부 판단 -1 : not yet / 0 : not set
int f = 0;
string str;
int main() {
    int n, idx = 1;
    cin >> n;
    for(int i = 0;i < 200;i++){
        for(int j = 0;j < 200;j++){
            dp[i][j] = -1;
        }
    }
    for(idx = 1;idx <= n;idx++){
        cin >> str;
        int size = str.size();
        // 방문 전 초기화
        if(isSet(0, size - 1)){
            printf("Word #%d: Set\n",idx);
        }
        else {
            printf("Word #%d: No Set\n",idx);
        }
        for(int i = 0;i < size;i++){
            for(int j=0;j < size;j++){
                dp[i][j] = -1;
            }
        }
    }
}
int isSet(int start, int end){
//    printf("set : %d %d\n",start, end);
    int &value = dp[start][end];
    if(value != -1){
        //dp 활용
        return value;
    }
    if(str[start]=='{' && str[end]=='}'){
        //예외처리
        if((start + 1) == end) return value = 1;
        if((start + 2) == end) return value = 1;
        //set?
        if(isSet(start+1, end-1)) return value = 1;
        //elem?
        for(int i = start+1;i <= end-1;i++){
            if(str[i] == ','){
                //,를 기준으로 반복적으로 element 판단
                if(isElem(start+1, i-1) && isElem(i+1, end-1)){
                    return 1;
                }
            }
        }
    }
    //not set
    return value = 0;
}

//Atom이거나 set이거나
//isSet, is Elem 서로가 반복 호출
int isElem(int start, int end){
//    printf("elem : %d %d\n",start, end);
    int &value = dp[start][end];
    if(value != -1){
        //dp 활용
        return value;
    }
    if(start > end) return 0;
    //Atom
    else if(start == end){
        // { , } 만 입력된다는 가정이 있다.
        return value = 1;
    }
    //Set
    else if(isSet(start, end)){
        return value = 1;
    }
    //Is List?
    else {
        for(int i = start;i <= end;i++){
            if(str[i] == ','){
                if(isElem(start,i-1) && isElem(i+1, end)){
                    return value  = 1;
                }
            }
        }
    }
    return value = 0;
}


