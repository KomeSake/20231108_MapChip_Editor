#include "Map.h"

void Map::LoaclMapLoad(string name, vector<vector<char>>& mapData)
{
	ifstream file(name);

	if (!file.is_open()) {
		throw runtime_error("ERRO:File load is erro!!" + name);
	}
	else {
		const char* cname = name.c_str();
		Novice::ConsolePrintf("%s file opened\n", cname);
	}

	string line;
	while (getline(file, line)) {
		vector<char> rowVector;
		stringstream sstream(line);
		string cell;
		while (getline(sstream, cell, ',')) {
			if (!cell.empty()) {
				rowVector.push_back(cell[0]);
			}
		}

		mapData.push_back(rowVector);
	}

	file.close();
}

void Map::MapShow(vector<vector<char>>& mapData, float minMapSize)
{
	int mapLine = int(mapData.size());
	int mapRow = int(mapData[0].size());
	float bgH = mapLine * minMapSize;
	for (int i = 0; i < mapLine; i++) {
		for (int j = 0; j < mapRow; j++) {
			switch (mapData[i][j]) {
			case '0':
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_map0, WHITE);
				break;
			case '1':
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_map1, WHITE);
				break;
			}
		}
	}
}

