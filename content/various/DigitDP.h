/**
 * Author: Vo Nguyen Hoang An
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Digit DP template to count numbers in range [0, N]
 * satisfying certain conditions. For range [L, R], compute solve(R) - solve(L - 1).
 * Time: O(D * S * 10). D is number of digits, S is state size.
 * Status: tested
 */
#pragma once

struct DigitDP {
	int memo[20][200]; // Change base on problem
	vi dig;
	int dfs(int pos, int st, bool tight, bool lz) {
		if (pos == sz(dig)) {
			return (st == 0); // Base case
		}
		if (!tight && !lz && memo[pos][st] != -1) {
			return memo[pos][st];
		}
		int lim = tight ? dig[pos] : 9;
		int res = 0;
		for (int d = 0; d <= lim; ++d) {
			bool nlz = lz && (d == 0);
			int nst = transition(st, d, nlz); // Change status function
			res += dfs(pos + 1, nst, tight && (d == lim), nlz);
		}
		if (!tight && !lz) {
			memo[pos][st] = res;
		}
		return res;
	}
	int transition(int st, int d, bool nlz) {
    	// Customize the state transition formula according to the problem.
    	// For example: calculate the digit sum, count occurrences of a specific digit, etc.
    	if (nlz) return st; // If still processing leading zeros, keep the state unchanged.
    	return st + d;
	}
	int solve(long long n) {
    	if (n < 0) return 0;
    	if (n == 0) return 1; // Adjust depending on whether zero should be counted as valid.
    	dig.clear();
    	for (; n > 0; n /= 10) dig.push_back(n % 10);
    	reverse(all(dig));
    	memset(memo, -1, sizeof(memo));
    	return dfs(0, 0, true, true);
	}
};
