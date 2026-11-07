/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: Dùng khi cần cấp phát động nhiều đối tượng và không cần giải
 * phóng chúng. "new X" thông thường có chi phí phụ khoảng 0.05us + 16 byte cho
 * mỗi lần cấp phát.
 * Status: tested
 */
#pragma once
#include <cassert>

// Either globally or in a single class:
static char buf[450 << 20];
void *operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void *)&buf[i -= s];
}
void operator delete(void *) {}
