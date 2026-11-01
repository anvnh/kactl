import sys
sys.setrecursionlimit(10000000)
from collections import deque, Counter, defaultdict
from bisect import bisect_left, bisect_right, insort
from heapq import (
    heapify, heappush, heappop,
    heappushpop, heapreplace,
    nlargest, nsmallest
)
from itertools import (
    accumulate, permutations, combinations,
    combinations_with_replacement,
    product, groupby, chain
)
from functools import lru_cache, cmp_to_key, reduce
from operator import itemgetter, mul, xor
# Only need when problem state
from fractions import Fraction
from decimal import Decimal, getcontext
from array import array
