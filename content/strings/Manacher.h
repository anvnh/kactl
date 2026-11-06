/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: Với mỗi vị trí trong chuỗi, tính:
 *  p[0][i] = bán kính palindrome chẵn dài nhất có tâm tại vị trí i.
 *  p[1][i] = bán kính palindrome lẻ dài nhất có tâm tại vị trí i
 *  (không tính ký tự ở chính giữa).
 * Time: O(N)
 * Status: Đã kiểm thử bằng stress test
 */
#pragma once

array<vi, 2> manacher(const string &s) {
	int n = sz(s);
	array<vi, 2> p = {vi(n + 1), vi(n)};
	rep(z, 0, 2) for (int i = 0, l = 0, r = 0; i < n; i++) {
		int t = r - i + !z;
		if (i < r)
			p[z][i] = min(t, p[z][l + t]);
		int L = i - p[z][i], R = i + p[z][i] - !z;
		while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
			p[z][i]++, L--, R++;
		if (R > r)
			l = L, r = R;
	}
	return p;
}
