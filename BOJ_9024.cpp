//
// Created by 신재욱 on 25. 9. 23..
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 답을 구하는 것 자체는 0부터 n까지 순회하면서 찾아도 된다. 근데 그렇게 봤더니 너무 오래 걸림. 탐색하는 횟수를 줄여야 함.
//
// 한 배열의 두 값을 가지고 무언가 하는 일이면 투 포인터를 쓰면 될 것 같다는 느낌까지는 왔었는데 문제가 있었다.
// 내 생각에 투 포인터를 쓰려면 '좌에서 우로, 우에서 좌로 어떤 포인터를 움직일 것인지 정해주는 기준'이 필요한데
// 좌우 중 어떤 인덱스를 움직여야 | 두 값의 합 - K |이 작아지는지 감이 안잡혔다.
//
// 저걸 어떻게 해결하는지 궁금해서 답안을 확인했는데 입력값을 먼저 정렬해서 위의 기준을 정할 수 있도록 가공하는 구문이 있었다.
// 앞으로는 투 포인터 전략을 써야 할 때 좌우측 포인터 중 어떤 포인터를 이동할 지 기준이 안세워진다면 그걸 세울 수 있도록
// 입력값을 가공해서 사용하도록 하자.

int solution(int n, int K, vector<int> a) {
    int left_index = 0;
    int right_index = n - 1;
    long min_difference = INT_MAX;
    int count = 0;

    sort(a.begin(), a.end());

    while (left_index < right_index) {
        long sum = a[left_index] + a[right_index];
        long difference = abs(sum - K);

        if (difference < min_difference) {
            min_difference = difference;
            count = 1;
        } else if (difference == min_difference) {
            count++;
        }

        if (sum < K) {
            left_index++;
        } else {
            right_index--;
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;  // number of test case

    cin >> t;

    vector<pair<long, vector<int>>> test_cases(t, make_pair(0, vector<int>()));

    for (int i = 0; i < t; i++) {
        int n, K;
        cin >> n >> K;

        test_cases[i].first = K;
        test_cases[i].second.resize(n);

        for (int j = 0; j < n; j++) {
            cin >> test_cases[i].second[j];
        }
    }

    for (int i = 0; i < t; i++) {
        cout << solution(test_cases[i].second.size(), test_cases[i].first, test_cases[i].second) << "\n";
    }
}
