/** 단순한 Greedy Algorithm으로는 시간초과가 뜬다.
 * 시간단축을 위해선 Greedy + Union Find
 * Path Compression 필요
 */

#include <iostream>
using namespace  std;
int G, P;
int g[100001];
int p[100000] = {0,};
int find(int pos);
void merge(int p1, int p2);
int main() {
    int cnt = 0;
    cin >> G >> P;
    for(int i = 1;i <= G;i++){
        g[i] = i;
    }
    for(int i = 0;i < P;i++){
        cin >> p[i];
    }
    for(int i = 0;i < P;i++){
        int pos = p[i];
        int result = find(pos);
        if(result){
            cnt++;
            merge(result, result-1);
        }
        else {
            break;
        }
    }
    printf("%d", cnt);
}

void merge(int p1, int p2){
    int parent1 = find(p1);
    int parent2 = find(p2);
    g[parent1] = parent2;
}

int find(int pos){
    if(g[pos] == pos){
        return pos;
    }
    else {
        return g[pos] = find(g[pos]);
    }
}
