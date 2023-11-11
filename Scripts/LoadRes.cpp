#include "LoadRes.h"

void LoadRes::LoadResNovice()
{
	int path = 0;
	int listW = 0, listH = 0;
	int w = 0, h = 0, x = 0, y = 0;

	//スライドシート
	//Player
	for (int i = 0; i < 6; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Player_idle_L.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 192, listH = 32;
		_sl_playerIdle_L[i] = { path,x,y,w,h,listW,listH };
	}
	for (int i = 0; i < 6; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Player_idle_R.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 192, listH = 32;
		_sl_playerIdle_R[i] = { path,x,y,w,h,listW,listH };
	}
	for (int i = 0; i < 5; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Player_run_L.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 160, listH = 32;
		_sl_playerRun_L[i] = { path,x,y,w,h,listW,listH };
	}
	for (int i = 0; i < 5; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Player_run_R.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 160, listH = 32;
		_sl_playerRun_R[i] = { path,x,y,w,h,listW,listH };
	}
	//Enemy
	for (int i = 0; i < 5; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Enemy1_L.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 160, listH = 32;
		_sl_Enemy_L[i] = { path,x,y,w,h,listW,listH };
	}
	for (int i = 0; i < 5; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Enemy1_R.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 160, listH = 32;
		_sl_Enemy_R[i] = { path,x,y,w,h,listW,listH };
	}

	//map
	_map0 = { Novice::LoadTexture("./Resources/Textures/map_0.png"),32,32 };
	_map1 = { Novice::LoadTexture("./Resources/Textures/map_1.png"),32,32 };
}
