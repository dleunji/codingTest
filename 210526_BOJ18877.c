#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct interval {
    long long start;
    long long end;
};
struct interval *intervals;
int n,m;
int cmp (const void* a, const void *b){
    struct interval *ia = (struct interval *)a;
    struct interval *ib = (struct interval *)b;
    if(ia->start > ib->start)
        return 1;
    else if(ia->start < ib->start)
        return -1;
    else
        return 0;
}
int getCows(long long d){
    long long pre = intervals[0].start;
    int cows = 1;
    for(int i = 0;i < m;i++){
        long long start = intervals[i].start;
        long long end = intervals[i].end;
        while(pre + d <= end){
            pre = (pre+d) > start ? pre+d : start;
            cows++;
        }
    }
    return cows;
    
}
int main(int argc, const char * argv[]) {
    scanf("%d %d", &n, &m);
    intervals = (struct interval*)malloc(sizeof(struct interval) * 100000);
    for(int i = 0 ;i < m;i++){
        scanf("%lld %lld", &intervals[i].start, &intervals[i].end);
    }
    qsort(intervals, m, sizeof(struct interval), cmp);
    long long start = 0;
    long long end = pow(10,18);
    long long mid ,cows;
    long long maxgap = 0;
    //소의 간격 구하기
    while(start <= end){
        mid = (start + end) / 2;
        cows = getCows(mid);
        if(cows < n){
            end = mid - 1;
        }
        else {
            maxgap = mid;
            start = mid + 1;
        }
        
    }
    printf("%lld\n", maxgap);
    return 0;
}
