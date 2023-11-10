#include "LoadRes.h"

void LoadRes::LoadResNovice()
{
	int path = 0;
	int listW = 0, listH = 0;
	int w = 0, h = 0, x = 0, y = 0;

	//スライドシート
	for (int i = 0; i < 5; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Player_run.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 160, listH = 32;
		_sl_playerRun[i] = { path,x,y,w,h,listW,listH };
	}

	//map
	_map0 = { Novice::LoadTexture("./Resources/Textures/map_0.png"),32,32 };
	_map1 = { Novice::LoadTexture("./Resources/Textures/map_1.png"),32,32 };
}
