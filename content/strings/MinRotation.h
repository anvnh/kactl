/**
 * Author: Stjepan Glavina
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Tìm phép xoay vòng có thứ tự từ điển nhỏ nhất của một chuỗi.
 * Time: O(N)
 * Usage:
 *  rotate(v.begin(), v.begin()+minRotation(v), v.end());
 * Status: Stress-tested
 */
#pragma once

int minRotation(string s) {
	int a = 0, N = sz(s);
	s += s;
	rep(b, 0, N) rep(k, 0, N) {
		if (a + k == b || s[a + k] < s[b + k]) {
			b += max(0, k - 1);
			break;
		}
		if (s[a + k] > s[b + k]) {
			a = b;
			break;
		}
	}
	return a;
}
