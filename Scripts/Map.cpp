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
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_sl_map, 0, WHITE);
				break;
			case '1':
				//FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_map1, WHITE);
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_sl_map, 1, WHITE);
				break;
			case '2':
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_sl_map2, 0, WHITE);
				break;
			case '3':
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_sl_map2, 1, WHITE);
				break;
			case 'e':
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_sl_map, 0, WHITE);
				FrameTexture(j * minMapSize + minMapSize / 2, bgH - i * minMapSize - minMapSize / 2, LoadRes::_sp_EnemyMother, WHITE);
				break;
			}
		}
	}
}

bool Map::IsThrough(vector<vector<char>> mapData, int line, int row)
{
	//首先要判断行列是否超过了容器的大小
	if (line > mapData.size()) {
		return false;
	}
	if (row > mapData[0].size()) {
		return false;
	}
	switch (mapData[line][row]) {
		//可以穿过的东西多得多，所以只有不可穿过的才记录下来了
	case '1'://墙壁
	case '3':
		return false;
	}
	return true;
}

void Map::LoaclMapSave(string name, vector<vector<char>>& mapData)
{
	ofstream file(name, ios::trunc);//将保存的文件的数据都清空

	if (!file.is_open()) {
		throw runtime_error("ERRO:File load is erro!!" + name);
	}
	else {
		const char* cname = name.c_str();
		Novice::ConsolePrintf("%s file opened\n", cname);
	}

	for (const auto& row : mapData) {
		for (const char& cell : row) {
			file.write(&cell, sizeof(cell));
			file.put(',');
		}
		if (!row.empty()) {
			file.seekp(-1, ios::cur);
		}
		file.put('\n');
	}

	file.close();
}

void Map::MapEditorShow(int bgW, int bgH, float minMapSize, UI_Game::MapEditorIndex mapEditorIndex)
{
	int line = int(bgH / minMapSize);
	int row = int(bgW / minMapSize);
	for (int i = 0; i < line; i++) {
		Vector2 screenPos1 = MyTools::WorldToScreen(0, minMapSize * i);
		Vector2 screenPos2 = MyTools::WorldToScreen(float(bgW), minMapSize * i);
		Novice::DrawLine(int(screenPos1.x), int(screenPos1.y), int(screenPos2.x), int(screenPos2.y), WHITE);
	}
	for (int i = 0; i < row; i++) {
		Vector2 screenPos1 = MyTools::WorldToScreen(minMapSize * i, 0);
		Vector2 screenPos2 = MyTools::WorldToScreen(minMapSize * i, float(bgH));
		Novice::DrawLine(int(screenPos1.x), int(screenPos1.y), int(screenPos2.x), int(screenPos2.y), WHITE);
	}

	//Mouse Map
	int mouseX{}, mouseY{};
	Novice::GetMousePosition(&mouseX, &mouseY);
	Vector2 worldPos = MyTools::ScreenToWorld(float(mouseX), float(mouseY));
	switch (mapEditorIndex)
	{
	case UI_Game::nothing:
		break;
	case UI_Game::bg1:
		FrameTexture(worldPos.x, worldPos.y, LoadRes::_sl_map, 0, WHITE);
		break;
	case UI_Game::box1:
		FrameTexture(worldPos.x, worldPos.y, LoadRes::_sl_map, 1, WHITE);
		break;
	case UI_Game::bg2:
		FrameTexture(worldPos.x, worldPos.y, LoadRes::_sl_map2, 0, WHITE);
		break;
	case UI_Game::box2:
		FrameTexture(worldPos.x, worldPos.y, LoadRes::_sl_map2, 1, WHITE);
		break;
	case UI_Game::enemyMother:
		FrameTexture(worldPos.x, worldPos.y, LoadRes::_sp_EnemyMother, WHITE);
		break;
	}
}


void Map::MapEditor(vector<vector<char>>& mapData, int bgH, float minMapSize, int screenW, int screenH, UI_Game::MapEditorIndex mapEditorIndex)
{
	int mouseX{}, mouseY{};
	Novice::GetMousePosition(&mouseX, &mouseY);
	Vector2 worldPos = MyTools::ScreenToWorld(float(mouseX), float(mouseY));
	int mouseLine = (int)((bgH - worldPos.y) / minMapSize);
	int mouseRow = (int)(worldPos.x / minMapSize);
	//在MapEditor菜单的时候不要有反应，而且要在屏幕之内
	if (mouseY > 0 && mouseY < 110 && mouseX>0 && mouseX < screenW
		|| mouseY>110 && mouseY < 450 && mouseX>140 && mouseX < screenW
		|| mouseY>450 && mouseY < screenH && mouseX>0 && mouseX < screenW)
	{
		switch (mapEditorIndex)
		{
		case UI_Game::nothing:
			break;
		case UI_Game::bg1:
			if (Novice::IsTriggerMouse(0)) {
				mapData[mouseLine][mouseRow] = '0';
			}
			break;
		case UI_Game::box1:
			if (Novice::IsTriggerMouse(0)) {
				mapData[mouseLine][mouseRow] = '1';
			}
			break;
		case UI_Game::bg2:
			if (Novice::IsTriggerMouse(0)) {
				mapData[mouseLine][mouseRow] = '2';
			}
			break;
		case UI_Game::box2:
			if (Novice::IsTriggerMouse(0)) {
				mapData[mouseLine][mouseRow] = '3';
			}
			break;
		case UI_Game::enemyMother:
			if (Novice::IsTriggerMouse(0)) {
				mapData[mouseLine][mouseRow] = 'e';
			}
			break;
		}
	}
}