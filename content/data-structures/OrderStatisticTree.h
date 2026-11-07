/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: Ordered Set (không hỗ trợ phần tử trùng lặp), cho phép tìm
 *  phần tử đứng thứ k và xác định thứ hạng của một phần tử.
 *  Muốn tạo map, thay \texttt{null\_type} bằng kiểu dữ liệu tương ứng.
 * Time: O(log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T>
using Tree =
	tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void example() {
	Tree<int> t, t2;
	t.insert(8);
	auto it = t.insert(10).first;
	assert(it == t.lower_bound(9));
	assert(t.order_of_key(10) == 1);
	assert(t.order_of_key(11) == 2);
	assert(*t.find_by_order(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
