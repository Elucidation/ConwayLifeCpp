#include <iostream>	
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

#define FRAMERATE 25

class Life
{
	bool **world; // pointer to pointer
	bool **next;
	int steps;
public:
	Life(int size_in);
	~Life();

	void step();
	bool checkLife(int x, int y);
	int neighbors(int x, int y);
	int size;

	void print();
};

Life::Life(int size_in) {
	size = size_in;

	world = (bool**)malloc(sizeof(bool*) * size);
	if (world)
		for (int i = 0; i < size; ++i)
			world[i] = (bool*)malloc(sizeof(bool*) * size);
		
	next = (bool**)malloc(sizeof(bool*) * size);
	if (next)
		for (int i = 0; i < size; ++i)
			next[i] = (bool*)malloc(sizeof(bool*) * size);
	
	if (world == NULL || next == NULL) {
		cout << "Malloc failed." <<endl;
		return;
	}
	

	steps = 0;
	for (int i = 0; i < size-1; ++i)
	{
		// Borders
		world[0][i]=false;
		world[size-1][i+1]=false;
		world[i+1][0]=false;
		world[i][size-1]=false;
	}

	for (int i = 1; i < size-1; ++i)
	{
		for (int j = 1; j < size-1; ++j) {
			world[i][j] = ((float)rand() / RAND_MAX > 0.5) ? true : false;

		}
	}
}

Life::~Life() {
	free(world);
	free(next);
}

void Life::print() {
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
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
	for (int i = 1; i < size-1; ++i)
		for (int j = 1; j < size-1; ++j)
			next[i][j] = checkLife(i,j);

	// Swap buffer onto actual
	for (int i = 1; i < size-1; ++i)
		for (int j = 1; j < size-1; ++j)
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
	int seed = time(NULL);
	int size = 64;	
	int turns = 10;
	float dt = 1.0/FRAMERATE * 1000; // frames/sec -> ms per step
	srand(seed);
	cout << "SEED: " << seed << endl;
	cout << "Life("<<size<<"), DT: "<< dt << "ms per turn, for " << turns << " turns." << endl;
	Life x(size);
	long t = clock();
	long tstepStart;
	float tstep;
	for (int i = 1; i <= turns; ++i)
	{
		cout << "Step " << i <<  endl;	
		tstepStart = clock();
		x.step();
		tstep = (float)(clock()-tstepStart)/CLOCKS_PER_SEC;
		//x.print();
		cout << "Step took: " << tstep << " seconds." << endl;
	}
	

	cout << "Done" << endl;	
	return 0;
}