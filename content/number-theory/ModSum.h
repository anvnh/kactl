/**
 * Author: Simon Lindholm
 * Date: 2015-06-23
 * License: CC0
 * Source: mã nguồn tự viết
 * Description: Tính tổng của các cấp số cộng sau khi lấy modulo.
 *
 *  \texttt{modsum(to, c, k, m)} = $\sum_{i=0}^{\mathrm{to}-1}{(ki+c) \% m}$.
 *  \texttt{divsum} có chức năng tương tự, nhưng sử dụng phép chia lấy phần
 * nguyên. Time: $O(\log m)$, với hằng số khá lớn. Status: Đã kiểm thử với mọi
 * $|k|, |c|, to, m \le 50$ và trên Kattis: aladin.
 */
#pragma once

typedef unsigned long long ull;
ull sumsq(ull to) { return to / 2 * ((to - 1) | 1); }
/// ^ written in a weird way to deal with overflows correctly

ull divsum(ull to, ull c, ull k, ull m) {
	ull res = k / m * sumsq(to) + c / m * to;
	k %= m;
	c %= m;
	if (!k)
		return res;
	ull to2 = (to * k + c) / m;
	return res + (to - 1) * to2 - divsum(to2, m - 1 - c, m, k);
}

ll modsum(ull to, ll c, ll k, ll m) {
	c = ((c % m) + m) % m;
	k = ((k % m) + m) % m;
	return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}
