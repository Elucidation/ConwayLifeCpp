#include <iostream>	
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
using namespace std;

#define FRAMERATE 25
//#define DO_VISUALS

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

	if ( (world = (bool**)malloc(sizeof(bool*) * size)) == NULL ) exit(-1);
	for (int i = 0; i < size; ++i)
		if ( (world[i] = (bool*)malloc(sizeof(bool*) * size)) == NULL ) exit(-1);
		
	if ( (next = (bool**)malloc(sizeof(bool*) * size)) == NULL ) exit(-1);
	for (int i = 0; i < size; ++i)
		if ( (next[i] = (bool*)malloc(sizeof(bool*) * size)) == NULL ) exit(-1);	

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
	for (int i=0;i<size;++i)
		cout << "X";
	cout << endl;
	for (int i = 1; i < size-1; ++i)
	{
		cout <<"X";
		for (int j = 1; j < size-1; ++j)
		{
			if (world[i][j])
				cout << "#";
			else
				cout << " ";
		}
		cout << "X"<< endl;
	}
	for (int i=0;i<size;++i)
		cout << "X";
	cout << endl;
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
	int size = 32;
	int turns = 100;
	if (argc > 1) {
		size = atoi(argv[1]); // C++ 11 has stoi, but not this compiler apparently
		if (size < 0)
			size = 0;
		if (argc > 2) {
			turns = atoi(argv[2]); // C++ 11 has stoi, but not this compiler apparently
			if (turns < 0)
				turns = 0;
		}
	}
	float dt = 1.0/FRAMERATE * 1000; // frames/sec -> ms per step
	srand(seed);
	Life x(size);

#ifdef DO_VISUALS
	COORD cur1 = {0, 0};
	COORD cur = {0, 2};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur1);
	system("cls");
	cout << "SEED: " << seed << endl;
	cout << "Life("<<size<<"), DT: "<< dt << "ms per turn, for " << turns << " turns." << endl;
	x.print();
#endif
	
	long t = clock();
	int tStart;
	int tstepStart;
	int tstep;
	float stepTimes = 0;
	for (int i = 1; i <= turns; ++i)
	{
		tStart = clock();
		tstepStart = clock();
		x.step();
		tstep = clock()-tstepStart; // clicks
		stepTimes += tstep; // clicks
#ifdef DO_VISUALS
		cout << "Step " << i << ": Step time (ms): " << (float)tstep/(CLOCKS_PER_SEC/1000) << "              " << endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
		x.print();
		while ((float)(clock()-tStart)/CLOCKS_PER_SEC*1000 < dt) {};
#endif
	}
	stepTimes /= turns;
	cout << "Avg Step Time: (" << stepTimes/CLOCKS_PER_SEC*1000 << ") ms                " << endl;
	return 0;
}