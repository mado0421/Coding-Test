// https://www.acmicpc.net/problem/1931
// Created by 신재욱 on 25. 9. 24..
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 이렇게 자료형 별칭을 선언해두면 알아보기 좋고 기분이 좋다.
using StartTime = int;
using EndTime = int;

int solution(const vector<pair<StartTime, EndTime>> & arr) {

    // 입력받은 배열의 복사본을 생성하고 정렬해준다. 이 때, 단순히 종료 시간만 보고 비교할 게 아니라 시작 시간 또한 같이 비교해야
    // 다음 순회 과정에서 N번 확인 하고 끝낼 수 있어서 편한거 같다.
    vector<pair<StartTime, EndTime>> meetings = arr;
    sort(meetings.begin(), meetings.end(), [](const pair<StartTime, EndTime> & a, const pair<StartTime, EndTime> & b) {
        if (a.second < b.second) return true;
        if (a.second == b.second) return a.first < b.first;
        return false;
    });

    int answer = 0;
    EndTime min_end_time = 0;
    for (const auto &[start_time, end_time] : meetings) {
        if (start_time >= min_end_time) {
            answer++;
            min_end_time = end_time;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;

    cin >> n;
    
    vector<pair<StartTime, EndTime>> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    cout << solution(a);
}