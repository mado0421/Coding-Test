// https://www.acmicpc.net/problem/11726
// Created by 신재욱 on 25. 9. 30..
//

#include <iostream>
#include <vector>

using namespace std;

// 2 * n을 1 * 2, 2 * 1 타일로 채우는 방법의 수를 반환하기
//
// dp[n]을 n일 때, 방법의 수로 치고 dp[5]까지 해봤는데 이거 피보나치 수열이랑 값이 똑같은 것 같다.
// 예시로 주어진 값도 n이 9일 때, 답이 55라잖아. 이거 무조건 피보나치네(ㅋㅋ)
int solution(const int n) {
	vector dp(n + 1, 0);

	if (1 == n) return 1;
	if (2 == n) return 2;

	dp[1] = 1;
	dp[2] = 2;

	// 최종 결과에 10,007 모듈러 연산을 해야 하는줄 알았는데 아니었음...
	for (int i = 3; i <= n; i++) {
		dp[i] = (dp[i - 1] + dp[i - 2]) % 10'007;
	}

	return dp[n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;

	cin >> n;

	cout << solution(n);
}
