/**
 * Author: Vo Nguyen Hoang An
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Tìm đường đi ngắn nhất từ đỉnh s trên đồ thị có trọng số
 *  cạnh không âm. Trả về {dist, par}, trong đó:
 *  - dist[i]: khoảng cách ngắn nhất từ s đến i (inf nếu không thể đi tới).
 *  - par[i]: đỉnh đứng trước i trên đường đi ngắn nhất (hoặc -1 nếu không có).
 * Time: O((V + E) log V)
 * Usage: auto [dist, par] = dijkstra(s, adj);
 * Status: Tested on CSES Shortest Routes I
 */
#pragma once
const ll inf = 1LL << 62;
pair<vector<ll>, vi> dijkstra(int s, const vector<vector<pair<int, ll>>> &adj) {
	int n = sz(adj);
	vector<ll> dist(n, inf);
	vi par(n, -1);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
		pq;
	dist[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		pair<ll, int> cur = pq.top();
		ll d = cur.first;
		int u = cur.second;
		pq.pop();
		if (d != dist[u])
			continue;
		for (const pair<int, ll> &e : adj[u]) {
			int v = e.first;
			ll w = e.second;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				par[v] = u;
				pq.push({dist[v], v});
			}
		}
	}
	return {dist, par};
}
