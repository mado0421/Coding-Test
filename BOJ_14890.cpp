// https://www.acmicpc.net/problem/14890
// Created by 신재욱 on 25. 10. 6..
//

#include <iostream>
#include <vector>

using namespace std;

// 2 ≤ N ≤ 100
// 1 ≤ L ≤ N
// 1 ≤ board[row][column] ≤ 10

bool IsCanGoDown(const vector<pair<int, bool> > &levels, const int start, const int L) {
	if (start + L > levels.size()) return false;

	const int level = levels[start].first;
	for (int i = start; i < start + L; i++) {
		if (levels[i].second) return false;
		if (levels[i].first != level) return false;
	}
	return true;
}

bool IsCanGoUp(const vector<pair<int, bool>> &levels, const int start, const int L) {
	if (start - (L - 1) < 0) return false; // 수정

	const int level = levels[start].first;
	for (int i = start; i >= start - (L - 1); i--) {
		if (levels[i].second) return false;
		if (levels[i].first != level) return false;
	}
	return true;
}

void SetLimps(vector<pair<int, bool>> &levels, const int from, const int to) {
	if (from <= to) {
		for (int i = from; i <= to; i++) levels[i].second = true;
	} else {
		for (int i = from; i >= to; i--) levels[i].second = true;
	}
}

bool IsPassable(vector<pair<int, bool>> &line, const int L) {
	int previous_level = line[0].first;
	for (int i = 1; i < line.size(); i++) {
		const int current_level = line[i].first;
		const int difference = current_level - previous_level;

		if (abs(difference) > 1) return false;

		if (difference == 1) { // 오르막
			if (!IsCanGoUp(line, i - 1, L)) return false;
			SetLimps(line, i - 1, i - L); // 수정
		}
		else if (difference == -1) { // 내리막
			if (!IsCanGoDown(line, i, L)) return false;
			SetLimps(line, i, i + L - 1); // 수정
		}

		previous_level = current_level;
	}
	return true;
}

int solution(const int N, const int L, const vector<vector<int> > &levels) {
	// 우선 각 방향으로 깡 계산을 돌려보는걸로 하자.
	// 현재 방향으로 쭉 진행하되, 단차를 만나면 다음과 같이 검사한다.
	// 1. 현재 칸과 다음 칸의 단차가 2 이상이다. -> 실패
	// 2. 현재 칸과 다음 칸의 단차가 1이고 현재 칸이 더 클 때, 다음 칸 이후로 L만큼 동일 높이가 연속되지 않는다. -> 실패
	// 3. 현재 칸과 다음 칸의 단차가 1이고 다음 칸이 더 클 때, 현재 칸 이전으로 L만큼 동일 높이가 연속되지 않는다. -> 실패
	// 4. 그 외, 성공
	//
	// 각 방향의 끝까지 가면 성공

	int success_count = 0;

	// 가로 방향 검사
	for (int row = 0; row < N; row++) {
		vector<pair<int, bool> > line;
		line.reserve(N);
		for (auto level: levels[row])
			line.emplace_back(level, false);
		if (IsPassable(line, L)) success_count++;
	}
	// 세로 방향 검사
	for (int column = 0; column < N; column++) {
		vector<pair<int, bool> > line;
		line.reserve(N);
		for (int row = 0; row < N; row++)
			line.emplace_back(levels[row][column], false);
		if (IsPassable(line, L)) success_count++;
	}

	return success_count;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, L;

	cin >> N >> L;

	vector board(N, vector<int>(N));

	for (int row = 0; row < N; row++) {
		for (int column = 0; column < N; column++) {
			cin >> board[row][column];
		}
	}

	cout << solution(N, L, board);
}
