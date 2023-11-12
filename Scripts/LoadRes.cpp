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

	//UI
	path = Novice::LoadTexture("./Resources/Textures/UI/Dead/List.png");
	listW = 800, listH = 382;
	w = 316, h = 318, x = 409, y = 0;
	_slUI_screenDead[0] = { path,x,y,w,h,listW,listH };
	w = 409, h = 321, x = 0, y = 0;
	_slUI_screenDead[1] = { path,x,y,w,h,listW,listH };
	w = 171, h = 62, x = 409, y = 318;
	_slUI_screenDead[2] = { path,x,y,w,h,listW,listH };
	w = 171, h = 62, x = 579, y = 318;
	_slUI_screenDead[3] = { path,x,y,w,h,listW,listH };
	w = 171, h = 61, x = 0, y = 321;
	_slUI_screenDead[4] = { path,x,y,w,h,listW,listH };
	w = 75, h = 38, x = 725, y = 0;
	_slUI_screenDead[5] = { path,x,y,w,h,listW,listH };
	w = 110, h = 37, x = 171, y = 322;
	_slUI_screenDead[6] = { path,x,y,w,h,listW,listH };

	_spUI_title = { Novice::LoadTexture("./Resources/Textures/UI/title.png"),701,301 };
	_spUI_start = { Novice::LoadTexture("./Resources/Textures/UI/start.png"),583,67 };
	_spUI_restart = { Novice::LoadTexture("./Resources/Textures/UI/restart.png"),647,67 };
}
