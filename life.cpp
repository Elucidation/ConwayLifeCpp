#include <iostream>	
#include <stdlib.h>
using namespace std;

#define SIZE 32

class Life
{
	bool world[SIZE][SIZE];
	bool next[SIZE][SIZE];
	int steps;
public:
	Life();
	~Life() {};

	void step();
	bool checkLife(int x, int y);
	int neighbors(int x, int y);

	void print();
};

Life::Life() {
	steps = 0;
	for (int i = 0; i < SIZE-1; ++i)
	{
		// Borders
		world[0][i]=false;
		world[SIZE-1][i+1]=false;
		world[i+1][0]=false;
		world[i][SIZE-1]=false;
	}

	for (int i = 1; i < SIZE-1; ++i)
	{
		for (int j = 1; j < SIZE-1; ++j) {
			world[i][j] = ((float)rand() / RAND_MAX > 0.5) ? true : false;

		}
	}
}

void Life::print() {
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (world[i][j])
				cout << "#";
			else
				cout << "-";
		}
		cout << endl;
	}
}

void Life::step() {
	// Write next step to buffer
	for (int i = 1; i < SIZE-1; ++i)
		for (int j = 1; j < SIZE-1; ++j)
			next[i][j] = checkLife(i,j);

	// Swap buffer onto actual
	for (int i = 1; i < SIZE-1; ++i)
		for (int j = 1; j < SIZE-1; ++j)
			world[i][j] = next[i][j];
		
	steps++;
}

bool Life::checkLife(int x, int y) {
	bool c = world[x][y]; // cell
	int n = neighbors(x,y); // neighbors
	if (n==3 || (world[x][y] && n==2))
		return true;
	else
		return false;
}

int Life::neighbors(int x, int y) {
	int sum = world[x][y] ? -1 : 0;
	for (int i = x-1; i < x+2; ++i) {
		for (int j = y-1; j < y+2; ++j) {
			if (world[i][j])
				sum++;
		}
	}
	return sum;
}

int main(int argc, char const *argv[])
{
	int seed = 235;//time(NULL);
	srand(seed);
	cout << "SEED: " << seed << endl;
	cout << "Life" << endl;
	Life x;
	x.print();
	for (int i = 1; i <= 10; ++i)
	{
		cout << "Step " << i <<  endl;	
		x.step();
		x.print();
	}
	

	cout << "Done" << endl;	
	return 0;
}