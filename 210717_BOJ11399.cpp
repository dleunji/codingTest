#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector <int> line;
int main(void){
    int n, p;
    int time = 0;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> p;
        line.push_back(p);
    }
    sort(line.begin(), line.end());
    for(int i = 0; i < n; i++){
        time += line[i] * (n - i);
    }
    cout << time << endl;
    
}
