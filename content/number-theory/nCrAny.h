/**
 * Author: Anvnh
 * Date: 2026-10-23
 * License: CC0
 * Source:
 * Time:
 * Description: Tính nCr modulo một số nguyên dương M bất kỳ.
 * Phân tích M thành các lũy thừa nguyên tố p\textsuperscript{k},
 * tính nCr modulo từng p\textsuperscript{k} (tính n! sau khi loại bỏ các thừa
 * số p, rồi nhân lại với p\textsuperscript{e}), sau đó kết hợp kết quả bằng
 * CRT. Mỗi p\textsuperscript{k} phải không vượt quá khoảng 1e7 (do cần tạo bảng
 * kích thước p\textsuperscript{k}), và M phải có thể phân tích bằng phương pháp
 * thử chia (M tối đa khoảng 1e12). Nếu M là số nguyên tố lớn, hãy sử dụng nCr
 * trong Combinatorics.h.
 * Time: O(sum of p^k + log_p(n)) per query
 * Status: Đã kiểm thử bằng cách so sánh với tam giác
 * Pascal và số nguyên lớn trong Python
 **/
#pragma once

#include "CRT.h"
#include "ModInverse.h"
#include "euclid.h"
ll powmod(ll b, ll e, ll m) {
	ll r = 1 % m;
	b %= m;
	for (; e; b = b * b % m, e >>= 1)
		if (e & 1)
			r = r * b % m;
	return r;
}
// n! with all factors of p removed, mod pk
ll factNoP(ll n, ll p, ll pk, const vector<ll> &f) {
	ll res = 1;
	while (n) {
		res = res * powmod(f[pk - 1], n / pk, pk) % pk * f[n % pk] % pk;
		n /= p;
	}
	return res;
}
ll nCrPk(ll n, ll r, ll p, ll k, ll pk) {
	ll e = 0;
	for (ll t = n; t;)
		t /= p, e += t;
	for (ll t = r; t;)
		t /= p, e -= t;
	for (ll t = n - r; t;)
		t /= p, e -= t;
	if (e >= k)
		return 0;
	vector<ll> f(pk);
	f[0] = 1;
	rep(i, 1, pk) f[i] = i % p ? f[i - 1] * i % pk : f[i - 1];
	ll num = factNoP(n, p, pk, f);
	ll den = factNoP(r, p, pk, f) * factNoP(n - r, p, pk, f) % pk;
	return num * modinv(den, pk) % pk * powmod(p, e, pk) % pk;
}
ll nCrAny(ll n, ll r, ll M) {
	if (r < 0 || r > n)
		return 0;
	ll ans = 0, m = 1, x = M;
	for (ll p = 2; p * p <= x; p++)
		if (x % p == 0) {
			ll k = 0, pk = 1;
			while (x % p == 0)
				x /= p, k++, pk *= p;
			ans = crt(ans, m, nCrPk(n, r, p, k, pk), pk);
			m *= pk;
		}
	if (x > 1) {
		ans = crt(ans, m, nCrPk(n, r, x, 1, x), x);
		m *= x;
	}
	return ans % M;
}
