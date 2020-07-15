# Hybrid

Input Format

t: positive integer: number of test cases.

Blank line.

Blank line between two consecutive test cases.

r, c: positive integers: number of rows and cols.

n: positive integer: number of live cells

n lines

s, f: positive integers: number of simulations and frequency of output

Constraints

1 <= t <=  100
1 <= r <=  200
1 <= c <=  200
1 <= n <=  700
1 <= s <= 2000
1 <= f <=  200

Output Format

The grid.

### Sample Input 0

~~~~~
1

9 9
3
4 3
4 4
4 5
3 1
~~~~~

### Sample Output 0

~~~~~
*** Life<Cell> 9x9 ***

Generation = 0, Population = 3.
---------
---------
---------
---------
---000---
---------
---------
---------
---------

Generation = 1, Population = 10.
---------
---------
---------
---000---
--01-10--
---000---
---------
---------
---------

Generation = 2, Population = 12.
---------
---------
---000---
---------
-01*-*10-
---------
---000---
---------
---------

Generation = 3, Population = 28.
---------
---000---
--01-10--
-00-0-00-
01-.-.-10
-00-0-00-
--01-10--
---000---
---------
~~~~~
