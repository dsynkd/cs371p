# Life

http://www.cs.utexas.edu/users/downing/cs371p/projects/Life.html

Input Format

t: positive integer: number of test cases.

Blank line.

Blank line between two consecutive test cases.

r, c: positive integers: number of rows and cols.

n: positive integer: number of live cells

n lines

s, f: positive integers: number of simulations and frequency of output

Constraints

1 <= t <=  200
1 <= r <=  200
1 <= c <=  200
1 <= n <=  200
1 <= s <= 2000
1 <= f <=  200

Output Format

The grid.

Sample Input 0

5

4 4
4
1 1
1 2
2 1
2 2
1 1

5 5
3
2 1
2 2
2 3
2 1

5 5
4
1 2
2 1
2 3
3 2
1 1

5 6
6
1 2
1 3
2 1
2 4
3 2
3 3
1 1

6 6
5
1 2
2 3
3 1
3 2
3 3
4 1

Sample Output 0

*** Life<ConwayCell> 4x4 ***

Generation = 0, Population = 4.
....
.**.
.**.
....

Generation = 1, Population = 4.
....
.**.
.**.
....

*** Life<ConwayCell> 5x5 ***

Generation = 0, Population = 3.
.....
.....
.***.
.....
.....

Generation = 1, Population = 3.
.....
..*..
..*..
..*..
.....

Generation = 2, Population = 3.
.....
.....
.***.
.....
.....

*** Life<ConwayCell> 5x5 ***

Generation = 0, Population = 4.
.....
..*..
.*.*.
..*..
.....

Generation = 1, Population = 4.
.....
..*..
.*.*.
..*..
.....

*** Life<ConwayCell> 5x6 ***

Generation = 0, Population = 6.
......
..**..
.*..*.
..**..
......

Generation = 1, Population = 6.
......
..**..
.*..*.
..**..
......

*** Life<ConwayCell> 6x6 ***

Generation = 0, Population = 5.
......
..*...
...*..
.***..
......
......

Generation = 1, Population = 5.
......
......
.*.*..
..**..
..*...
......

Generation = 2, Population = 5.
......
......
...*..
.*.*..
..**..
......

Generation = 3, Population = 5.
......
......
..*...
...**.
..**..
......

Generation = 4, Population = 5.
......
......
...*..
....*.
..***.
......

