/**
 * Author: Lukas Polacek, Joshua Andersson
 * Date: 2009-09-28
 * License: CC0
 * Source: kiến thức phổ biến (folklore)
 * Description: Các phép toán số học modulo.
 *  Trước tiên cần thiết lập giá trị {\tt mod}, sau đó có thể sử dụng cấu trúc
 * này.
 */
#pragma once
#include <cassert>

#include "euclid.h"

const ll mod = 17; // change to something else
struct Mod {
	ll x;
	Mod(ll y) : Mod(y % mod + mod, 0) {}
	Mod(ll y, int) : x(y < mod ? y : y - mod) {}
	Mod operator+(Mod b) { return {x + b.x, 0}; }
	Mod operator-(Mod b) { return {x - b.x + mod, 0}; }
	Mod operator*(Mod b) { return {x * b.x % mod, 0}; }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1);
		return x;
	}
	Mod operator^(ll e) {
		if (!e)
			return 1;
		Mod r = *this ^ (e / 2);
		r = r * r;
		return e & 1 ? *this * r : r;
	}
};
