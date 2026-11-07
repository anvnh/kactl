/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Tìm các thành phần liên thông mạnh (SCC) trong đồ thị có
 *  hướng. Hai đỉnh thuộc cùng một SCC khi có thể đi từ mỗi đỉnh đến
 *  đỉnh còn lại. Hàm scc(graph, callback) gọi callback với danh sách
 *  các đỉnh thuộc từng SCC, theo thứ tự topo ngược. comp[v] là chỉ số
 *  SCC chứa v; mỗi SCC chỉ có cạnh đến các SCC có chỉ số nhỏ hơn.
 *  ncomps là tổng số SCC.
 * Time: O(V + E)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vi val, comp, z, cont;
int Time, ncomps;
template <class G, class F> int dfs(int j, G &g, F &f) {
	int low = val[j] = ++Time, x;
	z.push_back(j);
	for (auto e : g[j])
		if (comp[e] < 0)
			low = min(low, val[e] ?: dfs(e, g, f));

	if (low == val[j]) {
		do {
			x = z.back();
			z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont);
		cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template <class G, class F> void scc(G &g, F f) {
	int n = sz(g);
	val.assign(n, 0);
	comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i, 0, n) if (comp[i] < 0) dfs(i, g, f);
}
