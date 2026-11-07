/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Tìm tập chỉ số của số đoạn ít nhất cần chọn để phủ kín một đoạn
 * cho trước. Các đoạn có dạng [đầu trái, đầu phải). Để hỗ trợ dạng [đầu trái,
 * đầu phải], thay điều kiện (A) bằng `|| R.empty()`. Trả về tập rỗng nếu không
 * thể phủ kín (hoặc nếu G rỗng).
 * Time: O(N log N)
 * Status: Tested on kattis:intervalcover
 */
#pragma once

template <class T> vi cover(pair<T, T> G, vector<pair<T, T>> I) {
	vi S(sz(I)), R;
	iota(all(S), 0);
	sort(all(S), [&](int a, int b) { return I[a] < I[b]; });
	T cur = G.first;
	int at = 0;
	while (cur < G.second) { // (A)
		pair<T, int> mx = make_pair(cur, -1);
		while (at < sz(I) && I[S[at]].first <= cur) {
			mx = max(mx, make_pair(I[S[at]].second, S[at]));
			at++;
		}
		if (mx.second == -1)
			return {};
		cur = mx.first;
		R.push_back(mx.second);
	}
	return R;
}
