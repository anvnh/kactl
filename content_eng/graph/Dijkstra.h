/**
 * Author: Vo Nguyen Hoang An
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Calculates shortest paths from $s$ in a graph with non-negative
 * edge weights. Returns $\{dist, par\}$ where $dist[i]$ is the shortest distance
 * (or $inf$ if unreachable) and $par[i]$ is the parent on the shortest path.
 * Time: O((V + E) \log V)
 * Usage: auto [dist, par] = dijkstra(s, adj);
 * Status: Tested on CSES Shortest Routes I
 */
#pragma once

const ll inf = 1LL << 62;
pair<vector<ll>, vi> dijkstra(int s, const vector<vector<pair<int, ll>>>& adj) {
	int n = sz(adj);
	vector<ll> dist(n, inf);
	vi par(n, -1);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	dist[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (d != dist[u]) continue;
		for (auto [v, w] : adj[u])
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				par[v] = u;
				pq.push({dist[v], v});
			}
	}
	return {dist, par};
}
