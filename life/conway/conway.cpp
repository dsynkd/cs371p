#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Grid {
private:
	vector<vector<bool>> grid;
	vector<vector<int>> neighborCount;
	int rows, cols, pop;
public:
	Grid(int r, int c) {
		rows = r;
		cols = c;
		pop = 0;
		r += 2;
		c += 2;
		grid.reserve(r);
		neighborCount.reserve(r);
		for(int i = 0; i < r; ++i) {
			vector<bool> cellRow;
			vector<int> neighborRow;
			cellRow.reserve(c);
			neighborRow.reserve(c);
			for(int j = 0; j < c; ++j) {
				cellRow.push_back(0);
				neighborRow.push_back(0);
			}
			neighborCount.push_back(neighborRow);
			grid.push_back(cellRow);
		}
	}
	bool getCell(int x, int y) {
		return grid[x+1][y+1];
	}
	void addCell(int x, int y) {
		if(getCell(x, y)) return;
		grid[x+1][y+1] = 1;
		++pop;
	}
	void delCell(int x, int y) {
		if(!getCell(x, y)) return;
		grid[x+1][y+1] = 0;
		--pop;
	}
	int getNeighborCount(int x, int y) {
		return neighborCount[x+1][y+1];
	}
	void incNeighborCount(int x, int y) {
		++neighborCount[x+1][y+1];
	}
	void incNeighbors(int x, int y) {
		incNeighborCount(x-1, y);
		incNeighborCount(x+1, y);
		incNeighborCount(x, y+1);
		incNeighborCount(x, y-1);
		incNeighborCount(x-1, y-1);
		incNeighborCount(x-1, y+1);
		incNeighborCount(x+1, y-1);
		incNeighborCount(x+1, y+1);
	}
	void countNeighbors() {
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if(getCell(i, j))
					incNeighbors(i, j);
			}
		}
	}
	void resetNeighborCount(int x, int y) {
		neighborCount[x+1][y+1] = 0;
	}
	void runRound() {
		countNeighbors();
		//printNeighbors();
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				int count = getNeighborCount(i, j);
				bool cell = getCell(i, j);
				if(count == 3 && !cell) {
					addCell(i, j);
				}
				else if((count < 2 || count > 3) && cell) {
					delCell(i, j);
				}
				resetNeighborCount(i, j);
			}
		}
	}
	void printNeighbors() {
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				cout << getNeighborCount(i, j);
			}
			cout << endl;
		}
	}
	void printState(int gen) {
		cout << "Generation = " << gen << ", Population = " << pop << "." << endl;
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if(getCell(i, j))
					cout << "*";
				else
					cout << ".";
			}
			cout << endl;
		}
	}
};

int main () {
	int t,r,c,n,s,f;
	cin >> t;
	while(t-->0) {
		cin >> r >> c >> n;
		Grid life(r, c);
		cout << "*** Life<ConwayCell> " << r << "x" << c << " ***" << endl << endl;
		while(n-->0) {
			int cr, cc;
			cin >> cr >> cc;
			life.addCell(cr, cc);
		}
		cin >> s >> f;
		s -= s % f;
		for(int a = 0; a <= s; a++) {
			if(a % f == 0) {
				life.printState(a);
				if(!(a == s && t == 0))cout << endl;
			}
			life.runRound();
		}
	}
}
