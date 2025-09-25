// https://www.acmicpc.net/problem/7576
// Created by 신재욱 on 25. 9. 25..
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 전체 순회를 하면서 깡으로 밀어버리는 방법도 있으나 그렇게 하면 너무 오래 걸린다.
// 전체 순회를 하는 횟수를 최소화하고 필요한 토마토만 접근하도록 하자.
int solution(vector<vector<int> > &box) {
    queue<pair<int, int> > to_spread;

    // 준비
    for (int row = 0; row < box.size(); row++) {
        for (int column = 0; column < box[0].size(); column++) {
            if (box[row][column] == 1) {
                to_spread.emplace(row, column);
            }
        }
    }

    // 상하좌우로 퍼트리면서 걸리는 일자 계산
    // 더 이상 퍼트릴 수 있는 토마토가 없을 때까지 반복
    //
    // 모든 토마토가 다 익었을 때에도 마지막으로 익은 토마토들은 주변에 전파할 수 있는지(즉, to_spread에 추가할 토마토가 있는지) 체크해야 함.
    // 그래서 spread_check_count가 실제로 경과한 일자보다 1 더 크게 계산됨.
    // 따라서 일자를 반환할 때는 spread_check_count - 1을 반환해야 함.
    int spread_check_count = 0;
    while (!to_spread.empty()) {
        // day를 세야 하니까 일단 하루치 볼 수 있는 개수를 저장
        int remaining_spread_count = to_spread.size();

        while (remaining_spread_count > 0) {
            const int row = to_spread.front().first;
            const int column = to_spread.front().second;
            to_spread.pop();

            // 상하좌우를 보고 덜 익은 토마토가 있으면 to_spread에 추가
            if (row - 1 >= 0 && box[row - 1][column] == 0) {
                box[row - 1][column] = 1;
                to_spread.emplace(row - 1, column);
            }
            if (row + 1 < box.size() && box[row + 1][column] == 0) {
                box[row + 1][column] = 1;
                to_spread.emplace(row + 1, column);
            }
            if (column - 1 >= 0 && box[row][column - 1] == 0) {
                box[row][column - 1] = 1;
                to_spread.emplace(row, column - 1);
            }
            if (column + 1 < box[0].size() && box[row][column + 1] == 0) {
                box[row][column + 1] = 1;
                to_spread.emplace(row, column + 1);
            }

            // 오늘 볼 수 있는 개수를 줄임
            remaining_spread_count--;
        }

        spread_check_count++;
    }

    // 전체 보드에 아직 덜 익은 토마토가 남아 있는지 보고 있으면 실패했다고 반환하기
    for (int row = 0; row < box.size(); row++) {
        for (int column = 0; column < box[0].size(); column++) {
            if (box[row][column] == 0) {
                return -1;
            }
        }
    }

    return spread_check_count - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;

    // N이 열이고, M이 행임 ! ! !
    cin >> N >> M;

    vector box(M, vector<int>(N));

    for (int row = 0; row < M; row++) {
        for (int column = 0; column < N; column++) {
            cin >> box[row][column];
        }
    }

    cout << solution(box);
}
