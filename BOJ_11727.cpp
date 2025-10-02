// https://www.acmicpc.net/problem/11727
// Created by 신재욱 on 25. 10. 1..
//

#include <iostream>
#include <vector>

using namespace std;

int solution(const int n)
{
	if (1 == n) return 1;
	if (2 == n) return 3;

	vector<int> dp(n + 1);

	dp[1] = 1;
	dp[2] = 3;
	for (int i = 3; i <= n; i++)
		dp[i] = (dp[i - 1] + 2 * dp[i - 2]) % 10007;

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
