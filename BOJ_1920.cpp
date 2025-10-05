// https://www.acmicpc.net/problem/1920
// Created by 신재욱 on 25. 10. 5..
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 1 ≤ N ≤ 100,000
// 1 ≤ M ≤ 100,000
// -2^31 < A[i] < 2^31

// target이 numbers 안에 있으면 1, 없으면 0을 반환하게 하면 된다.
// set 컨테이너를 쓰면 바로 정답 처리가 된다. <- 방금 되는거 확인함
// 학습 목적이니까 직접 작성해보자.
int solution(const vector<int> & numbers, const int target) {
	int left = 0;
	int right = numbers.size() - 1;

	while (left <= right) {
		int mid = (left + right) / 2;

		if (numbers[mid] == target)
			return 1;

		if (numbers[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;

	cin >> N;

	vector<int> A(N);

	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	// 정렬을 해둬야 이분 탐색을 할 수 있을 것 같다.
	sort(A.begin(), A.end());

	cin >> M;

	for (int i = 0, Q; i < M; i++) {
		cin >> Q;
		cout << solution(A, Q) << "\n";
	}
}
