# Allocator

### Input Format

`t`: positive integer: number of test cases.

Blank line.

Blank line between two consecutive test cases.

`n` lines: integers: either an allocation request or a deallocation request.

Positive integers are the number of objects to allocate.

Negative integers are the number of the busy block to free (one-based).

### Constraints

~~~~~
t <=  100
n <= 1000
~~~~~

The heap size is `1,000` bytes.

The object size is `8` bytes.

Allocation requests must be first come, first served.

### Output Format

One line: several integers: the values of all the sentinels.

### Sample Input 0

~~~~~
4

5

5
3

5
3
-1

5
3
3
-1
-1
~~~~~

### Sample Output 0

~~~~~
-40 944
-40 -24 912
40 -24 912
72 -24 880
~~~~~

### Explanation 0

~~~~~
allocate 5 objects: 8 + (5 * 8) = 48 bytes
bytes left: 1000 - 48 = 952 bytes
first  sentinel: -40
second sentinel: 944

allocate 5 objects: 8 + (5 * 8) = 48 bytes
allocate 3 objects: 8 + (3 * 8) = 32 bytes
bytes left: 1000 - 48 - 32 = 920 bytes
first  sentinel: -40
second sentinel: -24
third  sentinel: 912

allocate 5 objects: 8 + (5 * 8) = 48 bytes
allocate 3 objects: 8 + (3 * 8) = 32 bytes
deallocate first busy block
bytes left: 1000 - 48 - 32 = 920 bytes
first  sentinel: 40
second sentinel: -24
third  sentinel: 912

allocate 5 objects: 8 + (5 * 8) = 48 bytes
allocate 3 objects: 8 + (3 * 8) = 32 bytes
allocate 3 objects: 8 + (3 * 8) = 32 bytes
deallocate first busy block
deallocate first busy block, used to be the second busy block
coalesce old first and second busy blocks: 48 + 32 = 80 bytes
bytes left: 1000 - 48 - 32 - 32 = 888 bytes
first  sentinel: 72
second sentinel: -24
third  sentinel: 880
~~~~~
