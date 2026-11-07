/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Description: Nghịch đảo modulo. Case 1: M nguyên tố (Fermat). Case 2: M bất
 * kỳ, cần $\gcd(a, M) = 1$ (euclid mở rộng). Case 3: nghịch đảo của $1..n$
 * trong
 * $\mathcal{O}(n)$ khi M nguyên tố, dùng
 * $\text{inv}[i] = -\lfloor M/i \rfloor \cdot \text{inv}[M \bmod i] \bmod M$.
 * Time: $\mathcal{O}(\log M)$ cho Case 1, 2; $\mathcal{O}(n)$ cho Case 3.
 */
#pragma once
#include "euclid.h"
#include <cassert>

// Case 1: M is prime.
ll modinvPrime(ll a, ll M) {
	ll r = 1, e = M - 2;
	a %= M;
	if (a < 0)
		a += M;
	for (; e; a = a * a % M, e >>= 1)
		if (e & 1)
			r = r * a % M;
	return r;
}
// Case 2: M is arbitrary. Need gcd(a, M) == 1
ll modinv(ll a, ll M) {
	a = (a % M + M) % M;
	ll x, y, g = euclid(a, M, x, y);
	assert(g == 1); // g != 1 => no inverse
	return (x % M + M) % M;
}

// Case 3: M is prime, need inverses of 1..n (n < M) in O(n).
vector<ll> inv1n(int n, ll M) {
	vector<ll> inv(n + 1, 1);
	for (int i = 2; i <= n; i++)
		inv[i] = (M - M / i) * inv[M % i] % M;
	return inv;
}
