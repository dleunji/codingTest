/**
 * 세그먼트 트리 연습
 * 오버플로우 방지를 위해 쿼리의 부호만 표시 (음,양,0)
 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct segment_tree {
    int size;
    vector<long long> mult;
    //constructor
    segment_tree(vector<long long> &nums){
        size = nums.size();
        int height = ceil(log2(size));
        mult.resize(1 << (height + 1));
        init_tree(nums, 1, 0, size - 1);
    }
    
    long long init_tree(vector<long long> &nums, int root, int start, int end){
        if(start == end){
            return mult[root] = nums[start];
        }
        int mid = (start + end) / 2;
        long long left_sub_root = init_tree(nums, root * 2, start, mid);
        long long right_sub_root = init_tree(nums, root * 2 + 1, mid + 1, end);
        
        return mult[root] = left_sub_root * right_sub_root;
    }
    
    long long update(int index, int value){
        // 실질적인 value를 저장한 배열들은 index 0부터 저장되었기 때문
        return _update(index - 1, value, 1, 0, size - 1);
    }
    
    long long _update(int index, int value, int root, int start, int end){
        if(index < start || index > end) {
            return mult[root];
        }
        else if (start == end) {
            return mult[root] = value;
        }
        int mid = (start + end) / 2;
        return mult[root] = _update(index, value, root * 2, start, mid) * _update(index, value, root * 2 + 1, mid + 1, end);
    }
    
    long long query(int left, int right){
        return _query(left - 1, right - 1, 1, 0, size - 1);
    }
    // root가 subtree로 구현하고 있는 범위 : nums[start...end]
    // 그 중에서 left...right와의 교집합을 구한다.
    long long _query(int left, int right, int root, int start, int end){
        // 겹치는 구간이 아예 없으면 패스
        if(right < start || left > end){
            return 1;
        }
        // 구하는 구간(left...right)중 일부가 현재의 구간(start...end)이 완전히 포함되면 반영
        else if(left <= start && right >= end){
            return mult[root];
        }
        // 애매하게 섞여 있으면 나누어서 계산
        int mid = (start + end) / 2;
        return _query(left, right, root * 2, start, mid) * _query(left, right, root * 2 + 1, mid + 1, end);
    }
};
    
int main() {
    int n, k, num;
    string c;
    int a, b;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while(cin >> n){
        cin >> k;
        vector<long long> nums(n);
        for(int i = 0;i < n;i++){
            cin >> num;
            if(num > 0){
                nums[i] = 1;
            }
            else if(num < 0){
                nums[i] = -1;
            }
            else {
                nums[i] = 0;
            }
        }
        //세그먼트 트리 형성
        segment_tree seg(nums);
        for(int i = 0;i < k;i++){
            cin >> c >> a >> b;
            if(c == "C"){
                if(b > 0){
                    seg.update(a,1);
                    nums[a - 1] = 1;
                }
                else if(b < 0){
                    seg.update(a, -1);
                    nums[a - 1] = -1;
                }
                else {
                    seg.update(a, 0);
                    nums[a - 1] = 0;
                }
            }
            else {
                long long result = seg.query(a, b);
                if(result > 0){
                    cout << "+";
                }
                else if(result < 0){
                    cout << "-";
                }
                else {
                    cout << "0";
                }
            }
        }
        cout << "\n";
    }
    return 0;
}


