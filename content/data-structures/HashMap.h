/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map có API gần giống \text{unordered\_map} nhưng thường
 * nhanh hơn khoảng 3 lần, đổi lại sử dụng nhiều bộ nhớ hơn khoảng 1.5 lần. Dung
 * lượng ban đầu (nếu chỉ định) phải là lũy thừa của 2.
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
// To use most bits rather than just the lowest ones:
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({}, {}, {}, {}, {1 << 16});
