/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: O(logM)
 * Status: Works
 */
#pragma once
#include <cassert>
#include "euclid.h"

// Case 1: M is prime.
ll modinvPrime(ll a, ll M) {
	ll r = 1, e = M - 2;
	a %= M; if (a < 0) a += M;
	for (; e; a = a * a % M, e >>= 1)
		if (e & 1) r = r * a % M;
	return r;
}
// Case 2: M is arbitrary. Need gcd(a, M) == 1
ll modinv(ll a, ll M) {
	a = (a % M + M) % M;
	ll x, y, g = euclid(a, M, x, y);
	assert(g == 1); // g != 1 => no inverse
	return (x % M + M) % M;
}
