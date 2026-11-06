/**
 * Author: chilli
 * License: CC0
 * Description: z[i] tính độ dài tiền tố chung dài nhất của hai chuỗi
 *  s[i:] và s, ngoại trừ z[0] = 0.
 *  Ví dụ: abacaba -> 0010301.
 * Time: O(n)
 * Status: Đã kiểm thử bằng stress test
 */
#pragma once
vi Z(const string &S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i, 1, sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
