/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment Tree động hỗ trợ cộng hoặc gán một giá trị trên
 *  một đoạn, đồng thời truy vấn giá trị lớn nhất trên đoạn.
 *  Các node chỉ được tạo khi cần thiết, phù hợp với miền chỉ số rất lớn.
 *  Có thể thay đổi để hỗ trợ các phép toán khác.
 *  Nên sử dụng cùng Bump Allocator để tăng tốc độ cấp phát bộ nhớ,
 *  và SmallPtr hoặc chỉ số ngầm định để tiết kiệm bộ nhớ.
 * Time: O(\log N) cho mỗi thao tác.
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of -inf
	Node(vi &v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid);
			r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		} else
			val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L)
			return -inf;
		if (L <= lo && hi <= R)
			return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L)
			return;
		if (L <= lo && hi <= R)
			mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L)
			return;
		if (L <= lo && hi <= R) {
			if (mset != inf)
				mset += x;
			else
				madd += x;
			val += x;
		} else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo) / 2;
			l = new Node(lo, mid);
			r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
		else if (madd)
			l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
	}
};
