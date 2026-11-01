/**
 * Author: Anvnh
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: nCr mod an arbitrary M. Splits M into prime powers $p^k$,
 *  computes nCr mod each $p^k$ (n! with factors of $p$ removed, times $p^e$),
 *  then combines with CRT. Every $p^k$ of M must be at most about 1e7 (table
 *  of size $p^k$), and M must be factorizable by trial division (M at most
 *  about 1e12). For a large prime M use nCr from Combinatorics.h.
 * Time: O(sum p^k + log_p n) per query
 * Status: Tested against Pascal's triangle and Python bigints
 */
#pragma once

#include "euclid.h"
#include "CRT.h"
#include "ModInverse.h"
ll powmod(ll b, ll e, ll m) {
	ll r = 1 % m; b %= m;
	for (; e; b = b * b % m, e >>= 1) if (e & 1) r = r * b % m;
	return r;
}
// n! with all factors of p removed, mod pk
ll factNoP(ll n, ll p, ll pk, const vector<ll>& f) {
	ll res = 1;
	while (n) {
		res = res * powmod(f[pk-1], n / pk, pk) % pk * f[n % pk] % pk;
		n /= p;
	}
	return res;
}
ll nCrPk(ll n, ll r, ll p, ll k, ll pk) {
	ll e = 0;
	for (ll t = n; t; ) t /= p, e += t;
	for (ll t = r; t; ) t /= p, e -= t;
	for (ll t = n-r; t; ) t /= p, e -= t;
	if (e >= k) return 0;
	vector<ll> f(pk);
	f[0] = 1;
	rep(i,1,pk) f[i] = i % p ? f[i-1] * i % pk : f[i-1];
	ll num = factNoP(n, p, pk, f);
	ll den = factNoP(r, p, pk, f) * factNoP(n-r, p, pk, f) % pk;
	return num * modinv(den, pk) % pk * powmod(p, e, pk) % pk;
}
ll nCrAny(ll n, ll r, ll M) {
	if (r < 0 || r > n) return 0;
	ll ans = 0, m = 1, x = M;
	for (ll p = 2; p * p <= x; p++) if (x % p == 0) {
		ll k = 0, pk = 1;
		while (x % p == 0) x /= p, k++, pk *= p;
		ans = crt(ans, m, nCrPk(n, r, p, k, pk), pk); m *= pk;
	}
	if (x > 1) { ans = crt(ans, m, nCrPk(n, r, x, 1, x), x); m *= x; }
	return ans % M;
}
