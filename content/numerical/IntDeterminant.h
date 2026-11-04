/**
 * Author: Unknown
 * Date: 2014-11-27
 * Source: somewhere on github
 * Description:
 * Tính định thức của ma trận bằng các phép toán số học modulo.
 * Có thể bỏ phép lấy modulo để thu được phiên bản tính định thức
 * trên số nguyên thông thường.
 * Time: O(N^3)
 * Status: Đã kiểm thử vét cạn với N <= 3, mod <= 7.
 */
#pragma once

const ll mod = 12345;
ll det(vector<vector<ll>> &a) {
	int n = sz(a);
	ll ans = 1;
	rep(i, 0, n) {
		rep(j, i + 1, n) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i];
				if (t)
					rep(k, i, n) a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i] % mod;
		if (!ans)
			return 0;
	}
	return (ans + mod) % mod;
}
