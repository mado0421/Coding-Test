// https://www.acmicpc.net/problem/16499

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

// '같은 그룹이다'는 두 알파벳 뭉치를 각각 이루는 재료가 동일하다는 것을 의미하는 것 같다.
// 입력받은 뭉치들을 보고 그룹 몇 개가 존재하는지 반환하는 것 같다.
//
// 처음 든 생각은 '알파벳은 각각 숫자로 변환할 수 있으니까 그 숫자들의 합이 같으면 같은 그룹으로 판단해볼까'였는데
// 생각해보니 1 + 5 + 9 (=15)와 2 + 5 + 8 (=15)는 서로 다른 그룹인데도 동일하다고 판단할 것 같아서 넘겼다.
//
// 문자열을 알파벳 순으로 정렬할 수 있다면 정렬하고 해싱을 해버리면 되지 않을까?
int solution(const vector<string> & words)
{
	unordered_set<string> hash;

	for (string word : words)
	{
		ranges::sort(word);
		hash.insert(word);
	}

	return hash.size();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;

	cin >> N;

	vector<string> words(N);

	for (int i = 0; i < N; i++)
	{
		cin >> words[i];
	}

	cout << solution(words);
}
