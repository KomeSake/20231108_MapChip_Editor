#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <Novice.h>
#include "MyTools.h"
#include "GameUI.h"
using namespace std;

class Map :
	public MyTools
{
public:
	inline static const int _mapLine = 25;
	inline static const int _mapRow = 50;
	inline static vector<vector<char>> _mapData;
	inline static char _mapFileName[] = "./Resources/Csv/mapSample.csv";

	inline static bool _isEditor = false;

	static void LoaclMapLoad(string name, vector<vector<char>>& mapData);
	static void LoaclMapSave(string name, vector<vector<char>>& mapData);
	void MapShowDown(vector<vector<char>>& mapData, float minMapSize);
	void MapShow(vector<vector<char>>& mapData, float minMapSize);
	static bool IsThrough(vector<vector<char>> mapData, int line, int row);
	void MapEditorShow(int bgW, int bgH, float minMapSize, UI_Game::MapEditorIndex mapEditorIndex);
	static void MapEditor(vector<vector<char>>& mapData, int bgH, float minMapSize, int screenW, int screenH, UI_Game::MapEditorIndex mapEditorIndex);
};

