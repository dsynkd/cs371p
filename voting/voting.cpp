#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

void winner(int n, string candidates[], vector<vector<int>> ballots, int votes[], bool elim[], int b) {

	// check winner
	// do it in beginning bcuz there can be a winner/tie after first round
	int sum = 0;
	int tie = true, v = 0;
	for(int x = 0; x < n; x++) {
		if(elim[x])
			continue;
		sum += votes[x];
		if(votes[x] > b/2) {
			// DEBUG
			//cout << "== WINNER ==" << endl;
			
			cout << candidates[x] << endl;
			return;
		}

		// DEBUG
		//cout << candidates[x] << " -> " << votes[x] << endl;

		if(!v)
			v = votes[x];
		else if(votes[x] && votes[x] != v)
			tie = false;
		
	}
	assert(sum == b);
	if(tie) {

		// DEBUG
		//cout << "== WINNER ==" << endl;
		
		for(int x = 0; x < n; x++) {
			if(elim[x] || !votes[x])
				continue;
			cout << candidates[x] << endl;
		}
		return;
	}

	// find min vote
	int min_votes = 1000;
	for(int x = 0; x < n; ++x) {
		if(elim[x]) continue; // 0 doesnt count
		if(votes[x] < min_votes)
			min_votes = votes[x];
	}

	// DEBUG
	assert(min_votes != 1000);
	//cout << endl << "MIN VOTES: " << min_votes << endl<< endl;

	// identify losers and put them in array
	vector<int> losers;
	for(int x = 0; x < ballots.size(); ++x) {

		int candidate_index = ballots[x][0]-1;

		if(votes[candidate_index] > min_votes || elim[candidate_index])
			continue;

		// possibly a better way to avoid duplicates than using find()
		if(find(losers.begin(), losers.end(), candidate_index) != losers.end())
			continue;

		if(votes[candidate_index] == min_votes)
			losers.push_back(candidate_index);

		// DEBUG
		//cout << "LOSER FOUND: " << candidates[candidate_index] << endl;
	}

	for(int l = 0; l < losers.size(); ++l) {

		int loser_index = losers[l];

		// DEBUG
		//cout << endl << "RECOUNTING " << candidates[loser_index] << " VOTES" << endl << endl;

		for(int i = 0; i < ballots.size(); ++i) {

			// DEBUG
			//for(int j = 0; j < n; ++j) {
			//	cout << ballots[i][j] << ",";
			//}
			//cout << endl;

			int candidate_index = -1;
			for(int j = 0; j < n; ++j) {
				int index = ballots[i][j]-1;
				if(elim[index]) continue;
				candidate_index = index;

				// DEBUG
				if(j > 0 && candidate_index == loser_index) {

					// DEBUG
					//cout << "== NO BALLOT ELIMS! == " << loser_index+1 << endl;
					//for(int j = 0; j < n; ++j) {
					//	cout << ballots[i][j] << ",";
					//}
					//cout << endl;
				}
				
				break;
			}
			assert(candidate_index != -1);
			// we have to iterate through this and find 


			if(candidate_index != loser_index || elim[candidate_index]) // NEED TO CATCH THE CASE WHERE PREVIOUS CANDIDATE WAS A LOSER IN THE SAME ROUND
				continue;

			assert(votes[candidate_index] == min_votes);

			// loser found, find the next valid candidate
			for(int j = 1; j < n; ++j) {
				int c = ballots[i][j]-1;
				if(elim[c] || votes[c] == min_votes) {
					
					// DEBUG
					//cout << candidates[c] << " is not eligible for vote" << endl;

					continue; // either about to lose or already eliminated
				}

				++votes[c];

				// DEBUG
				//cout << candidates[c] << " GETS A VOTE (" << votes[c] << ")" << endl;
				
				if(votes[c] > b/2) {
					//cout << "== WINNER ==" << endl;
					cout << candidates[c] << endl;
					return;
				}

				break;
			}
		}

		assert(!elim[loser_index]);

		// DEBUG
	}
	
	for(int l = 0; l < losers.size(); ++l) {
		int loser_index = losers[l];
		elim[loser_index] = 1;
		// DEBUG
		//cout << endl << candidates[loser_index] << " ELIMINATED" << endl;
	}

	// code should return winner before here
	winner(n, candidates, ballots, votes, elim, b);
}

int main() {
	// get number of cases
	int t;
	cin >> t;
	assert(t > 0 && t < 100);
	while(t-->0) { // loop through each case

		// store candidate names in array of strings
		int n;
		cin >> n;
		assert(n > 0 && n < 21);
		string candidates[n], tmp;
		getline(cin, tmp); // this line just discards the empty newline
		assert(tmp.empty());
		for(int x = 0; x < n; ++x)
			getline(cin, candidates[x]); // have to use getline to record the full name instead of just the first name

		// DEBUG
		//cout << "== INIT ==" << endl;
		//for(int x = 0; x < n; ++x) cout << x+1 << ": " << candidates[x] << endl;

		// store ballots, count total votes and count votes per candidate
		vector<vector<int>> ballots;
		
		// pair of candidate index + their total number of votes
		int votes[n] = {};
		string ballot_line;
		getline(cin, ballot_line);

		// read and store ballots
		while(!ballot_line.empty()) {
			stringstream stream_ballot(ballot_line); // used to tokenize the given line into individual votes
			vector<int> ballot;
			for(int x = 0; x < n; ++x) { // loop through votes in a ballot
				int vote;
				stream_ballot >> vote;
				ballot.push_back(vote);
			}
			ballots.push_back(ballot);
			getline(cin, ballot_line); // once again have to use getline because there is no `b` given
		}

		int b = ballots.size();
		assert(b > 0 && b < 1001);

		// count votes per column
		for(int i = 0; i < b; ++i)
			++votes[ballots[i][0]-1];
	
		// DEBUG
		//cout << endl <<  "== COUNT ==" << endl;
		//for(int i = 0; i < n; ++i)
		//	cout << candidates[i] << ": " << votes[i] << endl;
		//cout << endl;
		//cout << "b = " << b << endl << endl;

		bool elim[n] = {};
		// eliminate candidates with 0 votes right away
		for(int x = 0; x < n; ++x)
			if(!votes[x])
				elim[x] = 1;

		winner(n, candidates, ballots, votes, elim, b);

		if (t != 0)
			cout << endl;
	}
}
