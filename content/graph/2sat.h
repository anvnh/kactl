/**
 * Author: anvnh
 * Date: 2026-11-07
 * Source: KACTL
 * Description: Giải bài toán 2-SAT: cho $N$ biến boolean và các mệnh đề dạng
 * "$a$ hoặc $b$", tìm một phép gán thỏa mãn tất cả mệnh đề hoặc kết luận vô
 * nghiệm. Biến đánh số từ $0$. Literal "biến $x$ đúng" viết là \texttt{x},
 * literal "biến $x$ sai" viết là phép phủ định bit của $x$ (xem Usage).
 * \texttt{either(a, b)} thêm mệnh đề $a \lor b$. \texttt{setValue(x)} ép
 * literal \texttt{x} đúng. \texttt{atMostOne(li)} thêm ràng buộc có tối đa một
 * literal trong \texttt{li} đúng (tạo thêm biến phụ, mất $\mathcal{O}(|li|)$).
 * \texttt{solve()} trả về true nếu có nghiệm, khi đó \texttt{values[i]} là giá
 * trị của biến $i$. Cách làm: mệnh đề $a \lor b$ cho hai cạnh kéo theo
 * $\lnot a \to b$ và $\lnot b \to a$, rồi tìm SCC bằng Tarjan. Vô nghiệm khi và
 * chỉ khi có biến $x$ mà $x$ và $\lnot x$ thuộc cùng một SCC.
 * Usage: TwoSat ts(n); // n biến
 * ts.either(0, ~3); // biến 0 đúng hoặc biến 3 sai
 * ts.setValue(2); // biến 2 đúng
 * ts.atMostOne({0, ~1, 2}); // tối đa một trong ba literal đúng
 * ts.solve(); // true nếu có nghiệm, kết quả ở ts.values[0..n-1]
 * Time: $\mathcal{O}(N + E)$
 * Status: Đã test với brute force
 */
#pragma once

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true
	TwoSat(int n = 0) : N(n), gr(2 * n) {}
	int addVar() { // new auxiliary variable
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}
	void either(int f, int j) {
		f = max(2 * f, -1 - 2 * f);
		j = max(2 * j, -1 - 2 * j);
		gr[f].push_back(j ^ 1);
		gr[j].push_back(f ^ 1);
	}
	void setValue(int x) { either(x, x); }
	void atMostOne(const vi &li) {
		if (sz(li) <= 1)
			return;
		int cur = ~li[0];
		rep(i, 2, sz(li)) {
			int next = addVar();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}
	vi val, comp, z;
	int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x;
		z.push_back(i);
		for (int e : gr[i])
			if (!comp[e])
				low = min(low, val[e] ?: dfs(e));
		if (low == val[i])
			do {
				x = z.back(), z.pop_back();
				comp[x] = low;
				if (values[x >> 1] == -1)
					values[x >> 1] = x & 1;
			} while (x != i);
		return val[i] = low;
	}
	bool solve() {
		values.assign(N, -1);
		val.assign(2 * N, 0);
		comp = val;
		rep(i, 0, 2 * N) if (!comp[i]) dfs(i);
		rep(i, 0, N) if (comp[2 * i] == comp[2 * i + 1]) return 0;
		return 1;
	}
};
