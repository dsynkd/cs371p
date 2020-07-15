#include <vector>
#include <string>

using namespace std;

class Grid;
class AbstractCell;
class FredkinCell;
class ConwayCell;
class Cell;

class AbstractCell {
protected:
	int neighborCount;
	bool alive;
public:
	AbstractCell();
	virtual void revive();
	virtual void kill();
	virtual bool isDead();
	virtual void incNeighborCount();
	virtual void incNeighbors(int, int, Grid&) = 0; // increments its neighbor count according to live neighbors
	virtual string printNeighborCount(); // for debug purposes
	virtual std::string print() = 0;
	virtual bool live() = 0; // performs one round of decisions
	virtual bool evolvable() = 0; // returns true when its time to evolve
};

class ConwayCell: public AbstractCell {
public:
	void incNeighbors(int, int, Grid&);
	string print();
	bool live();
	bool evolvable();
};

class FredkinCell: public AbstractCell {
private:
	int age;
public:
	FredkinCell();
	void incNeighbors(int, int, Grid&);
	string print();
	bool live();
	void incAge();
	bool evolvable();
};

class Cell { // wrapper around AbstractCell because we cant make instances of abstract classes
private:
	// only stores a pointer, the actual instance of AbstractCell (ConwayCell|FredkinCell) is stored on the heap using `new`
	// the grid then stores the Cell
	AbstractCell* cell;
public:
	Cell(ConwayCell*);
	Cell(FredkinCell*);
	AbstractCell& operator*();
	void evolve();
};

class Grid {
protected:
	vector<vector<Cell>> grid;
	int rows, cols, pop;
public:
	Grid(int, int);
	AbstractCell& getCell(int x, int y);
	Cell* getCellWrapper(int x, int y);
	void delCell(int x, int y);
	void addCell(int x, int y);
	void countNeighbors();
	void runRound();
	void printNeighbors();
	void printState(int);
};
