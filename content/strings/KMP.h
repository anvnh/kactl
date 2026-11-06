/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] tính độ dài của tiền tố dài nhất của s kết thúc tại vị trí
 * x, nhưng không được bằng chính s[0...x] (abacaba -> 0010123). Có thể dùng để
 * tìm tất cả các vị trí xuất hiện của một chuỗi con. Time: O(n) Status: Đã kiểm
 * chứng trên kattis:stringmatching
 */
#pragma once

vi pi(const string &s) {
	vi p(sz(s));
	rep(i, 1, sz(s)) {
		int g = p[i - 1];
		while (g && s[i] != s[g])
			g = p[g - 1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}
vi match(const string &s, const string &pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i, sz(p) - sz(s), sz(p)) if (p[i] == sz(pat))
		res.push_back(i - 2 * sz(pat));
	return res;
}
