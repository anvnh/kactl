/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source:
 * https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Tính $a\cdot b\bmod c$ (hoặc $a^b\bmod c$) với
 *  $0 \le a,b \le c \le 7.2\cdot 10^{18}$.
 * Time: O(1) đối với \texttt{modmul}, O(\log b) đối với \texttt{modpow}.
 * Status: Đã kiểm thử áp lực (stress-test), tính đúng đắn đã được chứng minh.
 * Details:
 *  Cách này nhanh hơn khoảng 2 lần so với cách tính thông thường
 *  \texttt{(\_\_int128\_t)a * b \% M}.
 *  Chứng minh tính đúng đắn được trình bày trong doc/modmul-proof.tex.
 *  Một phiên bản chứng minh cũ hơn, từ thời điểm code sử dụng
 *  \texttt{a * b / (long double)M}, nằm trong doc/modmul-proof.md.
 *  Chứng minh giả sử long double được triển khai dưới dạng số thực 80-bit x87.
 *  Nếu long double chỉ có độ chính xác 64-bit, chẳng hạn trên MSVC,
 *  thì cách cài đặt này chỉ đúng khi
 *  $0 \le a,b \le c < 2^{52} \approx 4.5\cdot 10^{15}$.
 */
#pragma once

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1)
			ans = modmul(ans, b, mod);
	return ans;
}
