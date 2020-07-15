#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

enum class Direction {east = 'e', north = 'n', west = 'w', south = 's'};
enum class Instruction {hop, left, right, infect, if_empty, if_wall, if_random, if_enemy, go};
enum class SpeciesType {food = 'f', hopper = 'h', rover = 'r', trap = 't'};

class Species {
	private:
		// stores the instruction and potential argument (set to -1 if instruction does not take arg)
		SpeciesType species_type;
		vector<pair<Instruction, int>> instructions;
	public:
		Species(SpeciesType _species_type) {
			species_type = _species_type;
		}
		void addInstruction(Instruction i, int n) {
			instructions.push_back(pair<Instruction, int>(i,n));
		}
		Instruction getNextAction(int pc) {
			while(instructions[pc].second != -1)
				pc = instructions[pc].second;
			return instructions[pc].first;
		}
};

class Creature {

	private:
		Species* s;
		Direction d;
		int pc;

	public:

		Creature(Species* _s, Direction _d) {
			s = _s;
			d = _d;
			pc = 0;
		}

		Instruction move() {
			Instruction i = s->getNextAction(pc);
			if(i == Instruction::left)
				d = static_cast<Direction>((d+1)%4);
			if(i == Instruction::right)
				d = static_cast<Direction>((d-1)%4);
			return i;
		}

		Direction getDirection() {
			return d;
		}
		Species* getSpecies() {
			return s;
		}
		void convertToNewSpecies(Species* newSpecies) {
			s = newSpecies;
			pc = 0;
		}
};

class Grid {
	private:
		vector<vector<Creature*>> grid;
		vector<Creature> creatures;
		unordered_map<Creature*, bool> turnGiven; // set to true once a creature has been given a turn to prevent giving a creature two turns when scanning them twice after a move
	public:
		Grid(int r, int c, int n) {
			grid.reserve(r);
			for(int i = 0; i < r; ++i) {
				vector<Creature*> row(c);
				for(int j = 0; j < c; ++j) {
					row.push_back(nullptr);
				}
				grid.push_back(row);
			}
			creatures.reserve(n);
		}
		void addCreature(Creature& c, pair<int, int> loc) {
			creatures.push_back(c);
			grid[loc.first][loc.second] = &c;
			turnGiven[&c] = false;
		}
		void printState() {
			for(int i = 0; i < grid.size(); ++i) {
				for(int j = 0; j < grid[i].size(); ++j) {
					if(grid[i][j] == nullptr)
						cout << ".";
					else {
						// TO BE DONE
						// need to find a way to compare species of current creature to species defined below (food, rover, etc)
						// to be done: getName()
					}
				}
			}
		}
		void updateGrid() {
			int rows = grid.size();

			// set all turns to false
			for(int x = 0; x < creatures.size(); ++x) {
				turnGiven[&creatures[x]] = false;
			}

			for(int i = 0; i < rows; ++i) {
				int columns = grid[i].size();
				for(int j = 0; j < columns; ++j) {
					if(grid[i][j] != nullptr && !turnGiven[grid[i][j]]) { // creature found
						Creature* c = grid[i][j];
						Instruction action = c->move(); // action instruction returned
						Direction d = c->getDirection();
						switch(action) {
							case Instruction::hop:
								if(d == Direction::west && j > 0 && grid[i][j-1] == nullptr) {
									grid[i][j] = nullptr;
									grid[i][j-1] = c;
								}
								if(d == Direction::east && j < columns-1 && grid[i][j+1] == nullptr) {
									grid[i][j] = nullptr;
									grid[i][j+1] = c;
								}
								if(d == Direction::north && i > 0 && grid[i-1][j] == nullptr) {
									grid[i][j] = nullptr;
									grid[i-1][j] = c;
								}
								if(d == Direction::south && i < rows-1 && grid[i+1][j] == nullptr) {
									grid[i][j] = nullptr;
									grid[i+1][j] = c;
								}
								break;
							case Instruction::left:
							case Instruction::right:
								break;
							case Instruction::infect:
								if(d == Direction::west && j > 0 && grid[i][j-1] != nullptr && grid[i][j-1]->getSpecies() != c->getSpecies()) {
									grid[i][j-1]->convertToNewSpecies(c->getSpecies());
								}
								if(d == Direction::east && j < columns-1 && grid[i][j+1] != nullptr && grid[i][j+1]->getSpecies() != c->getSpecies()) {
									grid[i][j+1]->convertToNewSpecies(c->getSpecies());
								}
								if(d == Direction::north && i > 0 && grid[i-1][j] != nullptr && grid[i-1][j]->getSpecies() != c->getSpecies()) {
									grid[i-1][j]->convertToNewSpecies(c->getSpecies());
								}
								if(d == Direction::south && i < rows-1 && grid[i+1][j] != nullptr && grid[i+1][j]->getSpecies() != c->getSpecies()) {
									grid[i+1][j]->convertToNewSpecies(c->getSpecies());
								}
							break;
						}
						turnGiven[c] = true;
					}
				}

			}

		}
};

int main() {

	Species food(SpeciesType::food);
	food.addInstruction(Instruction::left, -1);
	food.addInstruction(Instruction::go, 0);

	Species hopper(SpeciesType::hopper);
	hopper.addInstruction(Instruction::hop, -1);
	hopper.addInstruction(Instruction::go, 0);

	Species rover(SpeciesType::rover);
	rover.addInstruction(Instruction::if_enemy, 9);
	rover.addInstruction(Instruction::if_empty, 7);
	rover.addInstruction(Instruction::if_random, 5);
	rover.addInstruction(Instruction::left, -1);
	rover.addInstruction(Instruction::go, 0);
	rover.addInstruction(Instruction::right, -1);
	rover.addInstruction(Instruction::go, 0);
	rover.addInstruction(Instruction::hop, -1);
	rover.addInstruction(Instruction::go, 0);
	rover.addInstruction(Instruction::infect, -1);
	rover.addInstruction(Instruction::go, 0);

	Species trap(SpeciesType::trap);
	trap.addInstruction(Instruction::if_enemy, 3);
	trap.addInstruction(Instruction::left, -1);
	trap.addInstruction(Instruction::go, 0);
	trap.addInstruction(Instruction::infect, -1);
	trap.addInstruction(Instruction::go, 0);

	int t,r,c,n,s,f;
	char p,d;
	cin >> t;
	while(t-->0) {
		cin >> r >> c >> n;
		Grid darwin(r, c, n);

		// add creatures
		while(n-->0) {
			cin >> p >> r >> c >> d;
			Direction direction = static_cast<Direction>(d);
			SpeciesType species_type = static_cast<SpeciesType>(p);
			Species species(species_type);
			Creature creature(&species, direction);
			darwin.addCreature(creature, pair<int, int>(r,c));
		}

		cin >> s >> f;
	}
}
