#pragma once
#include <Novice.h>
#include <map>
using namespace std;

class LoadRes
{
public:
	//スライドの構造体
	static struct Sprite
	{
		int path = 0;//フォルダにどこがある
		int w = 0;//横幅
		int h = 0;//縦幅
	}structSP;
	//スライドシート構造体
	static struct SpriteList
	{
		int path = 0;//フォルダのどこにある
		int x = 0;//スライドの左上はシートにどこがある、X座標
		int y = 0;//Y座標
		int w = 0;//スライドの横幅
		int h = 0;//スライドの縦幅
		int listW = 0;//シートの横幅
		int listH = 0;//シードの縦幅
	}structSL;

	//Player
	inline static map<int, SpriteList> _sl_playerIdle_L;
	inline static map<int, SpriteList> _sl_playerIdle_R;
	inline static map<int, SpriteList> _sl_playerRun_L;
	inline static map<int, SpriteList> _sl_playerRun_R;

	//Bullet
	inline static Sprite _sp_Bullet;
	inline static Sprite _sp_BulletShell;

	//Enemy
	inline static Sprite _sp_EnemyMother;
	inline static map<int, SpriteList> _sl_Enemy_L;
	inline static map<int, SpriteList> _sl_Enemy_R;

	//Map
	inline static map<int, SpriteList> _sl_map;
	inline static map<int, SpriteList> _sl_map2;

	//UI
	inline static map<int, SpriteList> _slUI_screenDead;
	inline static Sprite _spUI_title;
	inline static Sprite _spUI_start;
	inline static Sprite _spUI_restart;
	inline static Sprite _spUI_hp;
	inline static Sprite _spUI_hp2;
	inline static Sprite _spUI_hpBox;
	inline static Sprite _spUI_mapEditor;
	inline static Sprite _spUI_mapEditor_yes;
	inline static Sprite _spUI_message_save;
	inline static Sprite _spUI_message_reset;

	//Sounds
	inline static int _audio_bgm;
	inline static int _audio_keySpace;
	inline static int _audio_attack;
	inline static int _audio_enemyDead;
	inline static int _audio_enemyJump;
	inline static int _audio_playerDead;
	inline static int _audio_playerDamage;
	inline static int _audio_jump;



















	static void LoadResNovice();//リソースをLoadする関数。最初に参照しなければならない
	static void UnLoadResNovice();//UnLoadしたいテクスチャを保存している（HotLoad機能の為）
};

