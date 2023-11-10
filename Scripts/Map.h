#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <Novice.h>
#include "MyTools.h"
using namespace std;

class Map :
	public MyTools
{
public:
	inline static const int _mapLine = 25;
	inline static const int _mapRow = 50;
	inline static vector<vector<char>> _mapData;
	inline static char _mapFileName[] = "./Resources/Csv/mapSample.csv";

	static void LoaclMapLoad(string name, vector<vector<char>>& mapData);
	void MapShow(vector<vector<char>>& mapData, float minMapSize);
};

