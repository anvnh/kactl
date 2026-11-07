/**
 * Author: anvnh
 * Date: 2026-11-07
 * Source: KACTL
 * Description: Xây dựng mảng hậu tố (suffix array) và mảng LCP của xâu $s$ bằng
 * thuật toán nhân đôi (prefix doubling) kết hợp counting sort.
 * \texttt{sa} là thứ tự từ điển của các hậu tố: \texttt{sa[0] = sz(s)} (hậu tố
 * rỗng, luôn đứng đầu), các hậu tố thật nằm ở \texttt{sa[1..n]}.
 * \texttt{lcp[i]} là độ dài tiền tố chung dài nhất của hai hậu tố
 * \texttt{sa[i-1]} và \texttt{sa[i]}, còn \texttt{lcp[0] = 0}.
 * LCP của hai hậu tố bất kỳ bằng min của \texttt{lcp} trên một đoạn liên tục
 * (dùng kèm RMQ.h). Số xâu con phân biệt của $s$ bằng $n(n+1)/2$ trừ tổng
 * \texttt{lcp}. Mọi ký tự phải nằm trong $[1, \texttt{lim})$ vì giá trị $0$
 * dành cho ký tự kết thúc; mặc định \texttt{lim = 256} cho \texttt{string}. Với
 * số nguyên lớn hơn, dùng \texttt{basic\_string<int>} và đặt \texttt{lim} bằng
 * giá trị lớn nhất cộng $1$ (mọi giá trị phải $\ge 1$).
 * Usage: string s;
 * SuffixArray a(s); a.sa[i]; a.lcp[i]; long long distinct = (ll)n * (n + 1) / 2
 * - accumulate(all(a.lcp), 0LL);
 * Time: $\mathcal{O}(N \log N)$
 * Status: Đã test với brute force
 */
#pragma once

struct SuffixArray {
	vi sa, lcp;
	template <class S> SuffixArray(const S &s, int lim = 256) {
		int n = sz(s) + 1, k = 0, a, b;
		vi x(begin(s), end(s) + 1), y(n), ws(max(n, lim)), rnk(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i, 0, n) ws[x[i]]++;
			rep(i, 1, lim) ws[i] += ws[i - 1];
			for (int i = n; i--;)
				sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i, 1, n) a = sa[i - 1], b = sa[i],
						 x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1
																	   : p++;
		}
		rep(i, 1, n) rnk[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rnk[i++]] = k)
			for (k &&k--, j = sa[rnk[i] - 1]; s[i + k] == s[j + k]; k++)
				;
	}
};
