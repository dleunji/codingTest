#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(vector<vector<int>> scores) {
    string answer = "";
    int s = scores.size();
    int turn = 0;
    for(int j = 0; j < s; j++){
        int maximum = -1;
        int minimum = 101;
        bool duplicate_max = false;
        bool duplicate_min = false;
        for(int i = 0;i < s;i++){
            if(maximum == scores[i][j]) {
                duplicate_max = true;
            }
            if(minimum == scores[i][j]) {
                duplicate_min = true;
            }
            if(maximum < scores[i][j]) {
                maximum = scores[i][j];
            }
            if(minimum > scores[i][j]) {
                minimum = scores[i][j];
            }
        }
        bool flag = false;
        int total = 0;
        for(int i = 0;i < s;i++){
            if(((maximum == scores[i][j] && !duplicate_max) || 
                (minimum == scores[i][j] && !duplicate_min)) 
               && turn == i) {
                flag = true;
            }
            else {
                total += scores[i][j];
            }
        }
        float score = flag ? (float)total / (s-1) : (float)total / s;
        if(score >= 90) {
            answer += "A";
        }
        else if(score >= 80) {
            answer += "B";
        }
        else if(score >= 70) {
            answer += "C";
        }
        else if(score >= 50) {
            answer += "D";
        } 
        else {
            answer += "F";
        }
        turn++;
    }
    return answer;
}