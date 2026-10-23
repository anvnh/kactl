/**
 * Author: Vo Nguyen Hoang An
 * Date: 2026-10-22
 * License: CC0
 * Source: folklore
 * Description: Binary Trie (0-1 Trie) for dynamic insertion, deletion,
 * and bitwise XOR queries (maximum, minimum, and count <= k) on non-negative integers.
 * Time: O(B) per operation, where B is the bit length (B = 30 for <= 1e9).
 * Usage:
 *   BinaryTrie tr;
 *   tr.insert(x); tr.erase(x);
 *   tr.maxXor(x); // returns max (x ^ y) for y in trie
 *   tr.minXor(x); // returns min (x ^ y) for y in trie
 *   tr.countLeq(x, k); // count y in trie such that (x ^ y) <= k
 * Status: stress-tested
 */
#pragma once
#include <cassert>

struct BinaryTrie {
	static const int B = 30; // 30 bits for values < 2^30 (~1e9)
	struct Node {
		int ch[2] = {0, 0};
		int cnt = 0;
	};
	vector<Node> t = {Node()};
	void insert(int x, int v = 1) { // v = -1 to erase
		int u = 0;
		t[u].cnt += v;
		for (int i = B - 1; i >= 0; --i) {
			int b = (x >> i) & 1;
			if (!t[u].ch[b]) {
				t[u].ch[b] = sz(t);
				t.emplace_back();
			}
			u = t[u].ch[b];
			t[u].cnt += v;
		}
	}
	void erase(int x) { insert(x, -1); }
	int maxXor(int x) {
		assert(t[0].cnt > 0);
		int u = 0, res = 0;
		for (int i = B - 1; i >= 0; --i) {
			int b = (x >> i) & 1;
			if (t[u].ch[!b] && t[t[u].ch[!b]].cnt > 0) {
				res |= (1 << i);
				u = t[u].ch[!b];
			} else {
				u = t[u].ch[b];
			}
		}
		return res;
	}
	int minXor(int x) {
		assert(t[0].cnt > 0);
		int u = 0, res = 0;
		for (int i = B - 1; i >= 0; --i) {
			int b = (x >> i) & 1;
			if (t[u].ch[b] && t[t[u].ch[b]].cnt > 0) {
				u = t[u].ch[b];
			} else {
				res |= (1 << i);
				u = t[u].ch[!b];
			}
		}
		return res;
	}
	// Count number of elements y in trie such that (x ^ y) <= k
	int countLeq(int x, int k) {
        if (k < 0) return 0;
        if (k >= (1 << B)) return t[0].cnt;

        int u = 0, ans = 0;
        for (int i = B - 1; i >= 0; --i) {
            int bx = (x >> i) & 1, bk = (k >> i) & 1;
            if (bk) {
                if (t[u].ch[bx]) ans += t[t[u].ch[bx]].cnt;
                u = t[u].ch[!bx];
            } else {
                u = t[u].ch[bx];
            }
            if (!u) return ans;
        }
        return ans + t[u].cnt;
    }
};
