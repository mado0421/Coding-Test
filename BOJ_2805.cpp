// https://www.acmicpc.net/problem/2805
// Created by 신재욱 on 25. 10. 2..
//

#include <iostream>
#include <vector>

using namespace std;

/// @return 더 크면 +, 같으면 0, 더 작으면 - 반환
long long Check(const vector<int> &tree_heights, const int height) {
	long long sum = 0;
	for (const auto tree_height: tree_heights) {
		sum += max(tree_height - height, 0);
	}
	return sum;
}

// 1 <= N <= 10^6
// 1 <= M <= 2 * 10^9
// 0 <= h <= 10^9
//
// 나는 처음에 이진탐색 방식으로 접근하려고 했는데 두번째 예시에서 계속 36이 아니라 35가 나오는 문제가 있었다.
// 풀이법을 찾아보니 파라메트릭 서치라는 개념이 있어서 그걸 사용했다.
int solution(const vector<int> &tree_heights, const int target_sum) {
	int low = 0;
	int high = 1'000'000'000;
	int answer = 0;

	while (low <= high) {
		int mid = (low + high) / 2;
		long long sum = Check(tree_heights, mid);

		if (sum >= target_sum) {
			answer = mid;
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;

	cin >> N >> M;

	vector<int> arr(N);

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	cout << solution(arr, M);
}
