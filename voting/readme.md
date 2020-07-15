# Australian Ballot

Australian ballots require that the voter rank the candidates in order of choice.

Initially only the first choices are counted and if one candidate receives more than `50%` of the vote, that candidate is elected.

If no candidate receives more than `50%`, all candidates tied for the lowest number of votes are eliminated.

Ballots ranking these candidates first are recounted in favour of their highest ranked candidate who has not been eliminated.

This process continues, that is, the lowest candidate is eliminated and each ballot is counted in favour of its ranked non-eliminated candidate, until **one** candidate receives more than `50%` of the vote or until all candidates are **tied**.

### Input Format

The input begins with a single positive integer, `t`, on a line by itself indicating the number of the cases following, each of them as described below.

This line is followed by a blank line, and there is also a blank line between two consecutive inputs.

The first line of input is an integer `n` indicating the number of candidates.

The next `n` lines consist of the names of the candidates in order.

Names may be up to `80` characters in length and may contain any printable characters.

The next `b` lines consist of ballots.

Each line contains the numbers from `1` to `n` in some order.

The first number indicates the candidate of **first** choice; the second number indicates candidate of **second** choice, and so on.

### Constraints

~~~~~
0 < t <= 100
0 < n <= 20
0 < b <= 1000
~~~~~

### Output Format

For each test case, the output must follow the description below.

The outputs of **two** consecutive cases will be separated by a blank line.

The output consists of either a single line containing the name of the winner or several lines containing the names of the candidates who tied.

### Sample Input 0

~~~~~
1

3
John Doe
Jane Smith
Sirhan Sirhan
1 2 3
2 1 3
2 3 1
1 2 3
3 1 2
~~~~~

### Sample Output 0

~~~~~
John Doe
~~~~~

### Explanation 0

~~~~~
John got two 1st place votes
Jane got two 1st place votes
Sirhan got one 1st place votes
Sirhan loses
The ballot that voted for Sirhan in 1st place voted for John in 2nd place
John wins
~~~~~
