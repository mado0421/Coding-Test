// https://www.acmicpc.net/problem/1074
// Created by 신재욱 on 25. 9. 26..
//

#include <iostream>
#include <cmath>

using namespace std;

// r행 c열을 몇 번째로 방문했는지 출력한다.
int solution(const int N, const int r, const int c) {

    // 그냥 찾으면 감도 안 잡히니까 이걸 사분면으로 쪼개고 쪼개는 식으로 생각하자.
    //  1 ┃ 2
    // ━━━╋━━━
    //  3 ┃ 4
    // 제일 작은 2 * 2 box를 전부 통과하면 4
    // 만약 4 * 4 box라면 우상단 첫번째에 들어갈 때, 좌상단 box를 통과하고 왔을 테니까 4 + 1이 될 것.
    // 좌하단 첫번째에 들어갈 때라면 좌상단, 우상단, 좌하단을 통과하고 왔을 테니까 4 * 3 + 1이 될 것.
    //
    // r을 4로 나눴더니 1이면 오른쪽, 아니면 왼쪽, 왼쪽일 때, r을 2로 나눠서 1이면 오른쪽, 아니면 왼쪽 이런 식으로 c까지 해서 오른쪽, 왼쪽 구한 다음에
    // r 오오왼에 c 위위아래 이러면 전체에서 좌상단 더하고, 우상단의 좌상단 더하고, 우상단의 우상단에서 세번째 이런 식으로 구하면?

    int row = r, column = c;
    int size = pow(2, N);
    int answer = 0;

    while (size > 1) {
        const int half = size / 2;
        int quadrant = 0;

        if (row >= half) { // 아래쪽
            quadrant += 2;
            row -= half;
        }
        if (column >= half) { // 오른쪽
            quadrant += 1;
            column -= half;
        }

        answer += quadrant * (half * half); // half가 현재 사분면의 절반이니까 한 사분면에 들어 있는 개수가 half * half.
        size = half;
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, r, c;

    cin >> N >> r >> c;

    cout << solution(N, r, c);
}
