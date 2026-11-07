/**
 * Author: Simon Lindholm
 * Date: 2020-05-30
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Tính $a \% b$ nhanh hơn khoảng 5 lần so với cách thông thường,
 * với $b$ là hằng số nhưng không biết tại thời điểm biên dịch. Trả về một giá
 * trị đồng dư với $a \pmod b$ trong khoảng $[0, 2b)$.
 * Status: proven correct,
 * stress-tested Đo được độ trễ thấp hơn 4 lần và thông lượng cao hơn 8 lần, xem
 * stress-test.
 * Details: Cụ thể hơn, có thể chứng minh kết quả bằng 0 chỉ khi $a
 * = 0$, và ngược lại nằm trong khoảng $[1, (1 + a/2^64) * b)$.
 */
#pragma once

typedef unsigned long long ull;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};
