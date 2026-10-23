/**
 * Author: Anvnh
 * Date: 2026-10-23
 * License: CC0
 * Source: folklore
 * Description: Iterates over maximal blocks [l, r] on which floor(n / i)
 *  is constant.
 * Time: O(sqrt(n))
 * Status: Standard loop, not separately tested
 */
#pragma once

for (ll l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// for every i in [l, r]: n / i == n / l
}
