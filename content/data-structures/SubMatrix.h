/**
 * Author: Johan Sannemo
 * Date: 2014-11-28
 * License: CC0
 * Source: Folklore
 * Description: Tính nhanh tổng các phần tử trong ma trận con, xác định
 *  bởi góc trên bên trái và góc dưới bên phải (đoạn nửa kín).
 * Usage:
 * SubMatrix<int> m(matrix);
 * m.sum(0, 0, 2, 2); // tổng 4 phần tử ở góc trên bên trái
 * Time: O(N^2 + Q)
 * Status: Tested on Kattis
 */
#pragma once

template <class T> struct SubMatrix {
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>> &v) {
		int R = sz(v), C = sz(v[0]);
		p.assign(R + 1, vector<T>(C + 1));
		rep(r, 0, R) rep(c, 0, C) p[r + 1][c + 1] =
			v[r][c] + p[r][c + 1] + p[r + 1][c] - p[r][c];
	}
	T sum(int u, int l, int d, int r) {
		return p[d][r] - p[d][l] - p[u][r] + p[u][l];
	}
};
