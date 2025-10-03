// https://www.acmicpc.net/problem/1786
// Created by 신재욱 on 25. 10. 3..
//

#include <iostream>
#include <vector>

using namespace std;

// KMP 알고리즘을 구현하는 문제
vector<int> solution(const string &Text, const string &Pattern) {
	// 자세하게 설명해주신 링크: https://bowbowbow.tistory.com/6
	// 원리를 정리하면 다음과 같다.
	// Pattern 문자열이 있을때, pi[i]는 0~i까지의 부분 문자열(전체가 동일한건 제외한다는 뜻) 중에서
	// prefix와 suffix가 같은 부분 문자열 중 가장 긴 문자열의 길이를 의미한다.
	// 예를 들어 "ABAABAB"라는 Pattern에 대해서 pi[4]는 0~4까지(ABAAB)의 부분 문자열 중에서
	// 맨 앞부분부터 시작한 문자열과 맨 뒷부분부터 시작한 문자열이 같은 문자열 중 가장 긴 문자열의 길이니까
	// "AB"A"AB"라서 2가 된다. 이런 정보를 어떻게 사용할 수 있는가?
	//
	// 예를 들어, i=4까지 T[j]와 P[i]가 일치했다고 하자. (T=...ABAABBBA...와 P=ABAABAB에 일 때)
	// 다음 i=5일 때 일치하지 않았다면, 마지막까지 일치했던 i=4로 pi[4]의 값을 참조하여 i=2까지는 맞았었다고 갱신한다.
	// 그리고 다음 i=3에 대해 또 일치하는지 검사한다. 일치하지 않으면 i=2로 pi[2]의 값을 참조하는데 pi[2]의 값은 1이기 때문에("A"B"A")
	// i=1로 치고... 다음 i=2에 대해 또 일치하는지 보고... 일치하지 않으면 i=1로 pi[1]의 값을 참조하는데 pi[1]의 값은 0이고...
	// T[j]와 P[0]이 일치하는지 보고... 일치하지 않으니 j++ 하고...
	//
	// 만약 P의 마지막 글자까지 전부 일치했다면 j-i를 answers에 추가하자. 그리고 P의 마지막 인덱스에 대해 pi[P의 마지막 인덱스]를 참조하여...
	// 동일한 일을 반복한다...
	//
	// 쉽게 말하면 '여기까지는 일치했었으니까 일치했던 부분에서 이어 가겠다'는 의미

	// 먼저 Text와 Pattern을 같이 확인하면서 Pattern[index]에서 불일치 할 때(즉, 실패했을 때) Pattern의 몇번째 글자까지는
	// 일치한다고 볼 수 있는지 저장할 인덱스 배열을 하나 만들자. 즉, 위에서 설명한 pi 배열이다.
	// 이 배열의 역할은 Pattern[i]에서 실패했을 때 돌아갈 인덱스를 저장한다. 따라서 fallback 배열이라고 하자.
	//
	// 왜 예시에서 pi 라고 했는지 찾아봤는데 이유는 잘 모르겠음. LPS나 failureFunction 등으로 부른다는데 엄...
	vector<int> fallback(Pattern.size());
	fallback[0] = 0;
	for (int i = 1, j = 0; i < Pattern.size(); i++) {
		while (Pattern[i] != Pattern[j] && j > 0) {
			j = fallback[j - 1];
		}
		if (Pattern[i] == Pattern[j]) {
			j++;
		}
		fallback[i] = j;
	}

	// 우선 패턴이 시작하는 인덱스들을 반환하자.
	// 문제에서는 0 based가 아니라 1 based를 요구하고 있긴 한데...
	vector<int> answers;
	// Text[i]와 Pattern[j]를 비교하자.
	for (int i = 0, j = 0; i < Text.size(); i++) {
		while (Text[i] != Pattern[j] && j > 0) {
			j = fallback[j - 1];
		}
		if (Text[i] == Pattern[j]) {
			j++;

			if (j == Pattern.size()) {
				answers.push_back(i - j + 1);
				j = fallback[j - 1];
			}
		}
	}

	return answers;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string T, P;

	// 그냥 cin >> T >> P 로 받으면 공백문자 때문에 박살난다 ! ! !
	getline(cin, T);
	getline(cin, P);

	const vector<int> answer = solution(T, P);

	cout << answer.size() << "\n";
	for (int i = 0; i < answer.size(); i++) {
		// 문제에서 인덱스 말고 번호를 출력하라고 함...
		// 즉, 1 based 값을 반환해야 함..........
		cout << answer[i] + 1;
		if (i != answer.size() - 1) cout << " ";
	}
}
