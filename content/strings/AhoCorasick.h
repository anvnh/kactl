/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: Code của marian (TopCoder)
 * Description: Dùng để tìm kiếm nhiều mẫu (pattern) cùng lúc. Khởi tạo bằng
 * AhoCorasick ac(patterns); trạng thái gốc của automaton có chỉ số 0.
 * find(word) trả về tại mỗi vị trí ID của từ dài nhất kết thúc tại đó, hoặc -1
 * nếu không có từ nào kết thúc tại vị trí đó. findAll(-, word) tìm tất cả các
 * từ (tối đa O(N * sqrt(N)) từ nếu không có pattern trùng nhau), nhóm theo vị
 * trí bắt đầu và sắp xếp từ ngắn đến dài. Cho phép các pattern trùng nhau;
 * không cho phép pattern rỗng. Muốn tìm từ dài nhất bắt đầu tại mỗi vị trí, hãy
 * đảo ngược tất cả đầu vào. Với bảng chữ cái lớn, chia mỗi ký tự thành các nhóm
 * bit và dùng bit đánh dấu để phân biệt ranh giới giữa các ký tự. Time:
 *  - Xây dựng: O(26N), với N là tổng độ dài các pattern.
 *  - find(x): O(N), với N là độ dài x.
 *  - findAll: O(NM).
 * Status: stress-tested
 */
#pragma once
#include <cassert>
struct AhoCorasick {
	enum { alpha = 26, first = 'A' }; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string &s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int &m = N[n].next[c - first];
			if (m == -1) {
				n = m = sz(N);
				N.emplace_back(-1);
			} else
				n = m;
		}
		if (N[n].end == -1)
			N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string> &pat) : N(1, -1) {
		rep(i, 0, sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i, 0, alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1)
					ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) =
						N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word) {
		int n = 0;
		vi res; // ll count = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string> &pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i, 0, sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};
