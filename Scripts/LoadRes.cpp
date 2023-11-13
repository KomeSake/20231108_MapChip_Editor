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
	for (int i = 0; i < 2; i++) {
		path = Novice::LoadTexture("./Resources/Textures/map_list.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 64, listH = 32;
		_sl_map[i] = { path,x,y,w,h,listW,listH };
	}

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

	_spUI_hp = { Novice::LoadTexture("./Resources/Textures/UI/hp.png"),34,28 };
	_spUI_hp2 = { Novice::LoadTexture("./Resources/Textures/UI/hp2.png"),34,28 };
	_spUI_hpBox = { Novice::LoadTexture("./Resources/Textures/UI/hpBox.png"),204,44 };

	//Sounds
	_audio_bgm = Novice::LoadAudio("./Resources/Sounds/MusMus-BGM-173.mp3");
	_audio_keySpace = Novice::LoadAudio("./Resources/Sounds/btn07.mp3");
	_audio_attack = Novice::LoadAudio("./Resources/Sounds/maou_se_battle16.mp3");
	_audio_enemyDead = Novice::LoadAudio("./Resources/Sounds/cncl06.mp3");
}

void LoadRes::UnLoadResNovice()
{
	const int bufMax = 10;
	int buf[bufMax]{};
	buf[0] = _sl_map[0].path;
	buf[1] = _sl_Enemy_L[0].path;
	buf[2] = _sl_Enemy_R[0].path;
	buf[3] = _sl_playerIdle_L[0].path;
	buf[4] = _sl_playerIdle_R[0].path;
	buf[5] = _sl_playerRun_L[0].path;
	buf[6] = _sl_playerRun_R[0].path;

	for (int i = 0; i < bufMax; i++) {
		if (buf[i] != NULL) {
			Novice::UnloadTexture(buf[i]);
		}
	}
}
