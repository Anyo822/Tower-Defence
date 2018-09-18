#pragma once
#include "map.h"
#include <vector>

#define Coord pair<int, int>
#define CoordVector vector<pair<int, int>>

using namespace std;

class LeePathfinder
{
	int *field;
	Coord start;
	Coord end;
	int size_x;
	int size_y;
	int *indexes;
	CoordVector path;

	void Backtrace(); 
	bool MarkPoint(int i, int j, int n); 
public:
	LeePathfinder(std::unique_ptr<Map>& atlas, int size_x, int size_y, int i_start, int j_start, int i_end, int j_end);
	LeePathfinder();
	CoordVector* CalculatePath();
	~LeePathfinder();
};

