// https://www.acmicpc.net/problem/17498
// Created by 신재욱 on 25. 9. 21..
//

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 열에 관계 없이, 마지막 행에 도달했을 때 얻을 수 있는 최대 점수를 구해야 함.
// 점수는? 현재 점수 + 이전 칸의 값 * 현재 칸의 값
// 따라서 각 칸마다 얻을 수 있는 최대 점수를 적어두고 다음 칸에서 계산할 때 활용하는 방식으로 접근하면 될 듯
// 계산 결과를 적어둔다는 점에서 DP 전략이라고 볼 수 있겠다.
//
// 처음에는 '어떤 행 i에서의 최대 점수 = dp[i]'와 같이 생각하고 접근했었는데 이렇게 하니 개별 칸의 최대 점수를 알 수가 없었다.
// 따라서 '어떤 행 r과 열 c에서의 최대 점수 = dp[r][c]'로 변경하고 점화식을 세우기로 함.
// 어떤 칸의 최대 점수는 그 칸에서 접근할 수 있는 이전 칸들의 최대 점수 + 어떤 칸의 값 * 이전 칸의 값
// dp[r][c] = max(dp[r - j][c - k] + a[r][c] * a[r - j][c - k]), (1 <= j <= D)(D - j <= k <= D + j)
// 예를 들어 D가 2면 dp[r][c]의 값을 계산할 때 위로 두 칸 떨어진 칸이나 위로 한 칸 떨어지고 왼쪽 한 칸, 오른쪽 한 칸, 가운데 한 칸 떨어진 칸들을
// 확인해야 한다. <- 이걸 프로그래밍 언어로 표현하기 위해 j와 k를 따로 선언해서 사용함. 위로도 찾아봐야 하고, 좌우로도 찾아봐야 하기 때문
//
// 위의 내용을 구현하면 아래와 같다.
int solution(const int N, const int M, const int D, const vector<vector<int> > &a) {
    int answer = INT_MIN;

    // 각 칸들의 최대 점수를 저장할 2차원 배열을 하나 만들어준다.
    // 이 문제는 값에 따라 음수도 최댓값이 될 수 있기 때문에 초기값을 INT_MIN으로 정해주자.
    vector dp(N, vector(M, INT_MIN));

    // N은 2 이상이고(=무조건 행이 두 개 이상 있고), 점수의 초기값이 0이라고 하였기 때문에 첫 행에서의 각 칸의 최대 점수는 모두 0으로 정해준다.
    for (int c = 0; c < M; c++)
        dp[0][c] = 0;

    // 두번째 행부터 각 칸당 최대 점수 구하기 시작
    for (int r = 1; r < N; r++) {
        for (int c = 0; c < M; c++) {

            // D보다 작은 거리 내의 dp 값들 중에서 최댓값을 구해야 함
            for (int j = 1; j <= D; j++) {  // (1 <= j <= D)
                if (r - j < 0) continue; // 보려고 하는 행이 0보다 작으면 넘어감

                for (int k = j - D; k <= D - j; k++) {  // (D - j <= k <= D + j)
                    if (c + k < 0 || c + k >= M) continue;  // 보려고 하는 열이 0보다 작거나, M과 같거나 크면 넘어감

                    if (dp[r - j][c + k] + a[r][c] * a[r - j][c + k] > dp[r][c])
                        dp[r][c] = dp[r - j][c + k] + a[r][c] * a[r - j][c + k];
                }
            }
        }
    }

    // 마지막 행까지 각 칸당 최대 점수를 구했다면 모든 열을 돌면서 마지막 행의 최대 점수를 구한다.
    for (int c = 0; c < M; c++) {
        if (dp[N - 1][c] > answer)
            answer = dp[N - 1][c];
    }

    // 감사합니다~
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, D;
    cin >> N >> M >> D;

    vector a(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> a[i][j];
        }
    }

    cout << solution(N, M, D, a);
}
