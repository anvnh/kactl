/**
 * Author: Anvnh
 * Date: 2026-11-06
 * License: CC0
 * Source: Wikipedia - Bellman-Ford algorithm
 * Description: Tìm đường đi ngắn nhất từ đỉnh $s$ trên đồ thị có thể
 *  chứa cạnh trọng số âm.
 *  Đỉnh không thể đi tới có dist = inf; đỉnh có thể đi tới thông qua
 *  chu trình trọng số âm có dist = -inf.
 *  Giả sử $V^2 \max |w_i| < 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once
const ll inf = LLONG_MAX;
struct Ed {
	int a, b, w, s() { return a < b ? a : -a; }
};
struct Node {
	ll dist = inf;
	int prev = -1;
};
void bellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s) {
	nodes[s].dist = 0;
	sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

	int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
	rep(i, 0, lim) for (Ed ed : eds) {
		Node cur = nodes[ed.a], &dest = nodes[ed.b];
		if (abs(cur.dist) == inf)
			continue;
		ll d = cur.dist + ed.w;
		if (d < dest.dist) {
			dest.prev = ed.a;
			dest.dist = (i < lim - 1 ? d : -inf);
		}
	}
	rep(i, 0, lim) for (Ed e : eds) {
		if (nodes[e.a].dist == -inf)
			nodes[e.b].dist = -inf;
	}
}
