// https://www.acmicpc.net/problem/2110
// Created by 신재욱 on 25. 10. 4..
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 2 <= N <= 2 * 10^6
// 2 <= C <= N
// 0 <= X[i] <= 10^9

int GetInstallableCount(const int distance, const vector<int> &positions) {
	// 첫 지점에 하나 설치
	int count = 1;
	int current_position = positions.front();

	// 다음 지점부터 돌면서 이전 설치 지점과 일정 간격 이상 떨어져 있으면
	// 거기에 새로 설치하고 설치한 count를 하나 늘림
	for (int i = 1; i < positions.size(); i++) {
		if (positions[i] >= current_position + distance) {
			current_position = positions[i];
			count++;
		}
	}

	return count;
}

// 목표 개수만큼 설치할 수 있는 최대 간격을 구하는 문제
int solution(const int goal_count, vector<int> &positions) {

	// 먼저 정렬하기
	sort(positions.begin(), positions.end());

	int min_distance = 0;
	int max_distance = positions.back() - positions.front();

	while (min_distance <= max_distance) {
		const int mid = (min_distance + max_distance) / 2;
		const int installable_count = GetInstallableCount(mid, positions);

		if (installable_count >= goal_count) {
			min_distance = mid + 1;
		} else {
			max_distance = mid - 1;
		}
	}

	return max_distance;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, C;

	cin >> N >> C;

	vector<int> X(N);

	for (int i = 0; i < N; i++) {
		cin >> X[i];
	}

	cout << solution(C, X);
}
