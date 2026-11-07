/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: Tìm ghép cặp cực đại trên đồ thị hai phía bằng thuật toán
 * Hopcroft-Karp. g[u] chứa danh sách các đỉnh kề thuộc phía phải của đỉnh u
 * ở phía trái. r phải được khởi tạo toàn bộ bằng -1 và có kích thước bằng
 * số đỉnh phía phải. Trả về kích thước matching. r[v] là đỉnh phía trái
 * được ghép với v, hoặc -1 nếu v chưa được ghép.
 * Time: $O(E\sqrt{V})$
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 */
#pragma once

int hopcroftKarp(vector<vi> &g, vi &r) {
	int n = sz(g), res = 0;
	vi l(n, -1), q(n), d(n);
	auto dfs = [&](auto f, int u) -> bool {
		int t = exchange(d[u], 0) + 1;
		for (int v : g[u])
			if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
				return l[u] = v, r[v] = u, 1;
		return 0;
	};
	for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
		rep(i, 0, n) if (l[i] == -1) q[t++] = i, d[i] = 1;
		rep(i, 0, t) for (int v : g[q[i]]) {
			if (r[v] == -1)
				f = 1;
			else if (!d[r[v]])
				d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
		}
		if (!f)
			return res;
		rep(i, 0, n) if (l[i] == -1) res += dfs(dfs, i);
	}
}
