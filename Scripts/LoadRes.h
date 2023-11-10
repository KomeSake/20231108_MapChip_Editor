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
	inline static map<int, SpriteList> _sl_playerRun;

	//Map
	inline static Sprite _map0;
	inline static Sprite _map1;



















	static void LoadResNovice();//リソースをLoadする関数。最初に参照しなければならない
};

