/**
 * Author: Anvnh
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Factorials, inverse factorials and nCr modulo a prime M.
 *  Call initFact() once before using nCr.
 * Time: O(MAXN) precomputation, O(1) per query
 * Status: Tested against Pascal's triangle and Python bigints
 */
#pragma once

#include "ModInverse.h"

const ll mod = 1000000007;
const int MAXN = 1000001;
ll fact[MAXN], invfact[MAXN];
void initFact() {
	fact[0] = 1;
	rep(i,1,MAXN) fact[i] = fact[i-1] * i % mod;
	invfact[MAXN-1] = modinvPrime(fact[MAXN-1], mod);
	for (int i = MAXN-1; i > 0; i--) invfact[i-1] = invfact[i] * i % mod;
}
ll nCr(int n, int r) {
	if (r < 0 || r > n) return 0;
	return fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}
