/**
 * Author: Vo Nguyen Hoang An
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Finds the length of the shortest cycle (girth) in an unweighted
 * undirected graph. Returns $-1$ if the graph is acyclic.
 * Time: O(V(V + E))
 * Usage: int len = shortestCycle(adj);
 * Status: Tested on CSES Graph Girth
 */
#pragma once

int shortestCycle(const vector<vi>& adj) {
	int n = sz(adj), ans = INT_MAX;
	rep(s,0,n) {
		vi dist(n, -1), par(n, -1), q = {s};
		dist[s] = 0;
		rep(qi,0,sz(q)) {
			int u = q[qi];
			for (int v : adj[u]) {
				if (dist[v] == -1) {
					dist[v] = dist[u] + 1;
					par[v] = u;
					q.push_back(v);
				} else if (par[u] != v)
					ans = min(ans, dist[u] + dist[v] + 1);
			}
		}
	}
	return ans == INT_MAX ? -1 : ans;
}
