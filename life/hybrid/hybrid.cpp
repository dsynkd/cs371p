#include <iostream>
#include <vector>
#include <string>
#include "hybrid.h"

using namespace std;

AbstractCell::AbstractCell() {
	alive = false;
	neighborCount = 0;
}

FredkinCell::FredkinCell() {
	age = 0;
}

void AbstractCell::incNeighborCount() {
	++neighborCount;
}

bool AbstractCell::isDead() {
	return alive == false;
}

void AbstractCell::revive() {
	alive = true;
}

void AbstractCell::kill() {
	alive = false;
}

string AbstractCell::printNeighborCount() {
	return to_string(neighborCount);
}

void ConwayCell::incNeighbors(int x, int y, Grid& grid) {
	if(!grid.getCell(x-1, y).isDead()) incNeighborCount();
	if(!grid.getCell(x+1, y).isDead()) incNeighborCount();
	if(!grid.getCell(x-1, y-1).isDead()) incNeighborCount();
	if(!grid.getCell(x+1, y-1).isDead()) incNeighborCount();
	if(!grid.getCell(x-1, y+1).isDead()) incNeighborCount();
	if(!grid.getCell(x+1, y+1).isDead()) incNeighborCount();
	if(!grid.getCell(x, y-1).isDead()) incNeighborCount();
	if(!grid.getCell(x, y+1).isDead()) incNeighborCount();
}

string ConwayCell::print() {
	if(isDead())
		return ".";
	return "*";
}

void FredkinCell::incNeighbors(int x, int y, Grid& grid) {
	if(!grid.getCell(x-1, y).isDead()) incNeighborCount();
	if(!grid.getCell(x+1, y).isDead()) incNeighborCount();
	if(!grid.getCell(x, y-1).isDead()) incNeighborCount();
	if(!grid.getCell(x, y+1).isDead()) incNeighborCount();
}

string FredkinCell::print() {
	if(isDead())
		return "-";
	return to_string(age);
}

Cell::Cell(ConwayCell* _cell) {
	cell = _cell;
}

Cell::Cell(FredkinCell* _cell) {
	cell = _cell;
}

AbstractCell& Cell::operator*() {
	return *cell;
}

// converts FredkinCell to ConwayCell
void Cell::evolve() {
	delete cell;
	cell = new ConwayCell();
	cell->revive();
}

// conway cell can no longer evolve, therefore this always returns false
bool ConwayCell::evolvable() {
	return false;
}

bool ConwayCell::live() {
	if(neighborCount == 3 && isDead())
		revive();
	else if(neighborCount < 2 || neighborCount > 3)
		kill();
	neighborCount = 0;
	return isDead();
}

// FredkinCells evolve at the age of 2 according to specs
bool FredkinCell::evolvable() {
	return age == 2;
}

void FredkinCell::incAge() {
	++age;
}

bool FredkinCell::live() {
	if(neighborCount == 1 || neighborCount == 3)
		if(isDead())
			revive();
		else
			incAge();
	else if(neighborCount == 0 || neighborCount == 2 || neighborCount == 4)
		kill();
	neighborCount = 0;
	return isDead();
}

Grid::Grid(int r, int c) {
	// rows and cols need to be stored 
	rows = r;
	cols = c;
	pop = 0;
	// building a 'moat' around the grid to avoid getting out of bounds access without having to check coordinates each time
	// accessor methods are later modified to add 1 to x/y coordinates to account for this
	r += 2;
	c += 2;
	grid.reserve(r);
	for(int i = 0; i < r; ++i) {
		vector<Cell> cellRow;
		vector<int> neighborRow;
		cellRow.reserve(c);
		neighborRow.reserve(c);
		for(int j = 0; j < c; ++j) {
			// initialize grid with dead FredkinCells
			cellRow.push_back(Cell(new FredkinCell()));
			neighborRow.push_back(0);
		}
		grid.push_back(cellRow);
	}
}

AbstractCell& Grid::getCell(int x, int y) {
	return *grid[x+1][y+1];
}

// AbstractCell wrapper needs to be used for evolve()
Cell* Grid::getCellWrapper(int x, int y) {
	return &grid[x+1][y+1];
}

// kind of a misleading name since grid has already been filled with dead cells. simply revives a cell if it is dead
void Grid::addCell(int x, int y) {
	AbstractCell& cell = getCell(x, y);
	if(!cell.isDead()) return;
	cell.revive();
	++pop;
}

void Grid::delCell(int x, int y) {
	AbstractCell& cell = getCell(x, y);
	if(cell.isDead()) return;
	cell.kill();
	--pop;
}

// always run at the beginning of runRound() as cells need to know their corresponding number of neighbors before making decisions
// still unsure whether i like the no braces style or not. it is shorter but it is also inconsistent
void Grid::countNeighbors() {
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < cols; ++j)
			getCell(i, j).incNeighbors(i, j, *this);
}

void Grid::printNeighbors() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j)
			cout << getCell(i, j).printNeighborCount();
		cout << endl;
	}
}

void Grid::runRound() {
	countNeighbors();
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			AbstractCell& cell = getCell(i, j);
			bool wasDead = cell.isDead();
			bool isDead = cell.live();
			if(wasDead && !isDead)
				++pop;
			if(!wasDead && isDead)
				--pop;
			if(cell.evolvable())
				getCellWrapper(i, j)->evolve();
		}
	}
}

void Grid::printState(int gen) {
	cout << "Generation = " << gen << ", Population = " << pop << "." << endl;
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			cout << getCell(i, j).print();
		}
		cout << endl;
	}
}

int main () {
	int t,r,c,n,s,f;
	cin >> t;
	while(t-->0) {
		cin >> r >> c >> n;
		Grid life(r, c);
		cout << "*** Life<Cell> " << r << "x" << c << " ***" << endl << endl;
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
				if(!(a == s && t == 0)) cout << endl;
			}
			life.runRound();
		}
	}
}
