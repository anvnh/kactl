/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Thêm và xóa các đoạn khỏi một tập hợp các đoạn rời nhau.
 * Khi thêm, đoạn mới sẽ được gộp với tất cả các đoạn giao hoặc tiếp giáp với
 * nó. Các đoạn có dạng [đầu trái, đầu phải), tức là lấy đầu trái và không lấy
 * đầu phải.
 * Time: O(log N)
 * Status: stress-tested
 */
#pragma once

set<pii>::iterator addInterval(set<pii> &is, int L, int R) {
	if (L == R)
		return is.end();
	auto it = is.lower_bound({L, R}), before = it;
	while (it != is.end() && it->first <= R) {
		R = max(R, it->second);
		before = it = is.erase(it);
	}
	if (it != is.begin() && (--it)->second >= L) {
		L = min(L, it->first);
		R = max(R, it->second);
		is.erase(it);
	}
	return is.insert(before, {L, R});
}

void removeInterval(set<pii> &is, int L, int R) {
	if (L == R)
		return;
	auto it = addInterval(is, L, R);
	auto r2 = it->second;
	if (it->first == L)
		is.erase(it);
	else
		(int &)it->second = L;
	if (R != r2)
		is.emplace(R, r2);
}
