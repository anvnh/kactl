/**
 * Author: Nhiiu
 * Date: 2002-09-15
 * Source: Có từ trước khi tinyKACTL ra đời
 * Description: Tìm hai số nguyên $x$ và $y$ sao cho
 *  $ax+by=\gcd(a,b)$.
 *  Nếu chỉ cần tính GCD, hãy sử dụng hàm có sẵn \texttt{\_\_gcd}.
 *  Nếu $a$ và $b$ nguyên tố cùng nhau thì $x$ chính là nghịch đảo
 *  của $a$ modulo $b$.
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b)
		return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;
}
