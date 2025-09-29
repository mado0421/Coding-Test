// https://www.acmicpc.net/problem/1260
// Created by 신재욱 on 25. 9. 29..
//

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 단순하게 DFS와 BFS 결과물을 출력하면 되는 문제다.
// 방문할 수 있는 정점이 여러개일 때는 번호가 작은 정점 먼저 방문한다.

string DFS(int vertex_count, int start_vertex_number, const unordered_map<int, set<int>> &edges) {
	unordered_set<int> visited;
	vector<int> visited_history;
	stack<pair<int, int> > to_visit;

	// 시작 번호를 방문 기록에 추가하고, 갈 수 있는 길들을 추가함
	visited.insert(start_vertex_number);
	visited_history.push_back(start_vertex_number);
	if (edges.contains(start_vertex_number)) {
		for_each(edges.at(start_vertex_number).rbegin(), edges.at(start_vertex_number).rend(), [&](int to) {
			to_visit.emplace(start_vertex_number, to);
		});
	}

	while (visited.size() < vertex_count && !to_visit.empty()) {
		auto [from, to] = to_visit.top();
		to_visit.pop();

		// 방문하려고 한 곳이 이미 방문한 곳이면 패스.
		if (visited.contains(to)) continue;

		// 방문 기록에 추가하고 거기서 갈 수 있는 곳들을 to_visit에 추가함
		visited.insert(to);
		visited_history.push_back(to);
		if (edges.contains(to)) {
			for_each(edges.at(to).rbegin(), edges.at(to).rend(), [&](int to_to) {
				to_visit.emplace(to, to_to);
			});
		}
	}


	string answer;
	for (int i = 0; i < visited_history.size(); i++) {
		answer += to_string(visited_history[i]);
		if (i != visited_history.size() - 1) answer += " ";
	}
	return answer;
}

string BFS(const int vertex_count, const int start_vertex_number, const unordered_map<int, set<int> > &edges) {
	unordered_set<int> visited;
	vector<int> visited_history;
	queue<pair<int, int> > to_visit;

	// 시작 번호를 방문 기록에 추가하고, 갈 수 있는 길들을 추가함
	visited.insert(start_vertex_number);
	visited_history.push_back(start_vertex_number);
	if (edges.contains(start_vertex_number))
		for (auto to: edges.at(start_vertex_number))
			to_visit.emplace(start_vertex_number, to);

	while (visited.size() < vertex_count && !to_visit.empty()) {
		auto [from, to] = to_visit.front();
		to_visit.pop();

		// 방문하려고 한 곳이 이미 방문한 곳이면 패스.
		if (visited.contains(to)) continue;

		// 방문 기록에 추가하고 거기서 갈 수 있는 곳들을 to_visit에 추가함
		visited.insert(to);
		visited_history.push_back(to);
		if (edges.contains(to))
			for (auto to_to: edges.at(to))
				to_visit.emplace(to, to_to);
	}


	string answer;
	for (int i = 0; i < visited_history.size(); i++) {
		answer += to_string(visited_history[i]);
		if (i != visited_history.size() - 1) answer += " ";
	}
	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, V;

	cin >> N >> M >> V;

	unordered_map<int, set<int> > from_to_edges;

	for (int i = 0; i < M; i++) {
		int vertex0, vertex1;
		cin >> vertex0 >> vertex1;

		// 양방향이니까 둘 다 넣기
		from_to_edges[vertex0].insert(vertex1);
		from_to_edges[vertex1].insert(vertex0);
	}

	cout << DFS(N, V, from_to_edges) << "\n" << BFS(N, V, from_to_edges);
}
