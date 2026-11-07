/**
 * Author: anvnh
 * Date: 2026-11-07
 * Source: folklore
 * Description: Heavy-Light Decomposition. Tách cây có gốc thành các chuỗi
 * (chain) sao cho mọi đường đi từ đỉnh lên gốc cắt $\mathcal{O}(\log N)$ chuỗi.
 * Mỗi chuỗi là một đoạn liên tục trong mảng \texttt{pos}, nên truy vấn đường
 * đi hoặc cây con quy về vài truy vấn đoạn trên Segment Tree. Đỉnh con nặng
 * (heavy child) là con có cây con lớn nhất và được đánh số liền sau cha, nên
 * cây con của $v$ chiếm đúng đoạn $[\texttt{pos}[v], \texttt{pos}[v] +
 * \texttt{siz}[v])$.
 * Giá trị nằm trên đỉnh: \texttt{update(v, x)} gán giá trị đỉnh $v$,
 * \texttt{queryPath(u, v)} trả về $f$ trên mọi đỉnh của đường đi từ $u$ tới
 * $v$, \texttt{querySubtree(v)} tương tự cho cây con của $v$.
 * Giá trị nằm trên cạnh: lưu giá trị cạnh $(\texttt{par}[v], v)$ tại đỉnh con
 * $v$, gọi \texttt{update(v, x)} với $v$ là đỉnh con, và truyền
 * \texttt{edges = true} cho query (bỏ qua đỉnh LCA, vì LCA không có cạnh lên).
 * Hàm gộp $f$ (đặt trong \texttt{Tree}) phải có tính kết hợp và giao hoán
 * (max, min, sum, xor, ...). Nếu $f$ không giao hoán thì phải xử lý thứ tự
 * hai nửa đường đi (lên từ $u$ và xuống tới $v$) riêng. Muốn cộng/gán trên
 * cả đường đi hoặc cây con thì thay \texttt{Tree} bằng Lazy Segment Tree với
 * cùng cách chia đoạn. DFS viết lặp nên không tràn stack với cây lớn. Đỉnh
 * đánh số từ $0$, mặc định gốc là $0$. \texttt{vals} (nếu có) là giá trị ban
 * đầu của từng đỉnh. Dựng cây mất $\mathcal{O}(N \log N)$, query cây con và
 * \texttt{lca} mất $\mathcal{O}(\log N)$.
 * Usage: HLD h(g, vals); // g: danh sách kề, vals[i]: giá trị đỉnh i
 * h.update(v, 5); h.queryPath(u, v); h.querySubtree(v); h.lca(u, v);
 * Time: Query đường đi $\mathcal{O}(\log^2 N)$.
 * Status: Đã test với brute force
 */
#pragma once

#include "../data-structures/SegmentTree.h"

struct HLD {
	typedef Tree::T T;
	int n, timer = 0;
	vi par, siz, dep, head, pos, heavy;
	Tree seg;
	HLD(const vector<vi> &g, vector<T> vals = {}, int root = 0)
		: n(sz(g)), par(n, -1), siz(n, 1), dep(n), head(n), pos(n),
		  heavy(n, -1), seg(n) {
		vi ord, st = {root};
		while (!st.empty()) { // DFS lặp: tính cha, độ sâu
			int v = st.back();
			st.pop_back();
			ord.push_back(v);
			for (int u : g[v])
				if (u != par[v])
					par[u] = v, dep[u] = dep[v] + 1, st.push_back(u);
		}
		for (int i = n; i--;) { // cộng dồn size từ dưới lên, chọn con nặng
			int v = ord[i], p = par[v];
			if (p >= 0) {
				siz[p] += siz[v];
				if (heavy[p] < 0 || siz[v] > siz[heavy[p]])
					heavy[p] = v;
			}
		}
		st.assign(1,
				  root); // đánh số: con nhẹ push trước, con nặng push sau cùng
		while (!st.empty()) {
			int v = st.back();
			st.pop_back();
			pos[v] = timer++;
			head[v] = (par[v] >= 0 && heavy[par[v]] == v) ? head[par[v]] : v;
			for (int u : g[v])
				if (u != par[v] && u != heavy[v])
					st.push_back(u);
			if (heavy[v] >= 0)
				st.push_back(heavy[v]);
		}
		rep(v, 0, n) if (v < sz(vals)) seg.update(pos[v], vals[v]);
	}
	void update(int v, T x) { seg.update(pos[v], x); }
	T queryPath(int u, int v, bool edges = false) {
		T res = Tree::unit;
		for (; head[u] != head[v]; v = par[head[v]]) {
			if (dep[head[u]] > dep[head[v]])
				swap(u, v);
			res = seg.f(res, seg.query(pos[head[v]], pos[v] + 1));
		}
		if (dep[u] > dep[v])
			swap(u, v);
		return seg.f(res, seg.query(pos[u] + edges, pos[v] + 1));
	}
	T querySubtree(int v, bool edges = false) {
		return seg.query(pos[v] + edges, pos[v] + siz[v]);
	}
	int lca(int u, int v) {
		for (; head[u] != head[v]; v = par[head[v]])
			if (dep[head[u]] > dep[head[v]])
				swap(u, v);
		return dep[u] < dep[v] ? u : v;
	}
};
