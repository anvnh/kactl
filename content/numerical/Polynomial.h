/**
 * Author: (KACTL-style, built on NumberTheoreticTransform.h)
 * Date: 2026-11-04
 * License: CC0
 * Source: folklore (phương pháp lặp Newton)
 * Description: Các phép toán trên chuỗi lũy thừa modulo $x^n$ trên
 * $\mathbb{Z}_{998244353}$. Đa thức được lưu trong vector vl, hệ số có bậc thấp
 * nhất đứng trước. polyMul(a, b): Tính tích hai đa thức (tích chập thông
 * thường). polyInv(a, n): Tìm $b$ sao cho $ab \equiv 1 \pmod{x^n}$, yêu cầu
 * $a[0] \neq 0$. polyLog(a, n): Tính $\ln a \bmod x^n$, yêu cầu $a[0] = 1$.
 *  polyExp(a, n): Tính $e^a \bmod x^n$, yêu cầu $a[0] = 0$.
 *  Kết quả của các hàm đều có đúng n phần tử (ngoại trừ polyMul).
 * Usage: vl f = {1, 1, 1}; vl g = polyInv(f, 8); // g = 1 - x + x^3 - x^4 + ...
 * Time: O(n \log n) cho phép nhân, nghịch đảo và log; exp có hằng số lớn hơn
 * (khoảng gấp 3 lần log). Status: đã kiểm thử trên Library Checker (Inv/Log/Exp
 * of Formal Power Series)
 */
#pragma once
#include "NumberTheoreticTransform.h"
vl polyMul(const vl &a, const vl &b) { return conv(a, b); }
vl polyInv(const vl &a, int n) {
	vl b = {modpow(a[0], mod - 2)};
	for (int m = 1; m < n; m *= 2) { // b <- b * (2 - a * b) mod x^{2m}
		vl ap(a.begin(), a.begin() + min(sz(a), 2 * m));
		vl t = conv(conv(b, b), ap);
		t.resize(2 * m);
		b.resize(2 * m);
		rep(i, 0, 2 * m) b[i] = ((2 * b[i] - t[i]) % mod + mod) % mod;
	}
	b.resize(n);
	return b;
}
vl polyDeriv(vl a) {
	rep(i, 1, sz(a)) a[i - 1] = a[i] * i % mod;
	a.pop_back();
	return a;
}
vl polyInteg(vl a) {
	int n = sz(a) + 1;
	vl iv(n + 1, 1); // iv[i] = i^{-1} mod p
	rep(i, 2, n + 1) iv[i] = (mod - (mod / i) * iv[mod % i] % mod) % mod;
	a.insert(a.begin(), 0);
	rep(i, 1, n) a[i] = a[i] * iv[i] % mod;
	return a;
}
vl polyLog(const vl &a, int n) {
	vl r = polyInteg(conv(polyDeriv(a), polyInv(a, n)));
	r.resize(n);
	return r;
}
vl polyExp(const vl &a, int n) {
	vl b = {1};
	for (int m = 1; m < n; m *= 2) { // b <- b * (1 + a - ln b) mod x^{2m}
		vl l = polyLog(b, 2 * m), f(2 * m);
		rep(i, 0, 2 * m) f[i] = ((i < sz(a) ? a[i] : 0) - l[i] + mod) % mod;
		f[0] = (f[0] + 1) % mod;
		b = conv(b, f);
		b.resize(2 * m);
	}
	b.resize(n);
	return b;
}
