/**
 * Author: Folklore
 * Date: 2024-01-01
 * License: CC0
 * Source: folklore
 * Description: Tìm cây khung nhỏ nhất (MST) trên đồ thị vô hướng có trọng số
 *  bằng thuật toán Kruskal kết hợp cấu trúc Disjoint Set Union (UF).
 *  Trả về cặp \{tổng trọng số MST, danh sách chỉ số các cạnh thuộc MST\}.
 *  Nếu đồ thị không liên thông, thuật toán trả về rừng khung nhỏ nhất (MSF);
 *  kiểm tra \texttt{sz(mst) == n - 1} để xác nhận đồ thị liên thông.
 * Usage:
 *  vector<Edge> ed;
 *  rep(i, 0, M) ed.push_back({u, v, w, i});
 *  auto [cost, mst] = kruskal(N, ed);
 * Time: O(E \log E)
 * Status: tested
 */
#pragma once
struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b)
			return false;
		if (e[a] > e[b])
			swap(a, b);
		e[a] += e[b];
		e[b] = a;
		return true;
	}
};
struct Edge {
	int u, v;
	ll w;
	int id;
	bool operator<(const Edge &o) const { return w < o.w; }
};

pair<ll, vi> kruskal(int n, vector<Edge> &ed) {
	sort(all(ed));
	UF uf(n);
	ll cost = 0;
	vi mst;
	for (auto &e : ed)
		if (uf.join(e.u, e.v)) {
			cost += e.w;
			mst.push_back(e.id);
		}
	return {cost, mst};
}
