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

	//新たなリソースを入れる仕方
	//1.　宣言：inline static + Sprite/map<int, SpriteList> + 名前
	//1.1　Spriteは普通のリソース用。map<int, SpriteList>は連番動画とUI用
	//2.　LoadRes.cppにリソースの要素を書いてください
	//3.　参照：使いたい所に、LoadRes::名前で参照してください

	//例：
	//スライドは一つ目の様子、スライドシートは二つ目の様子、変数名だけを変えるといい
	inline static Sprite _spriteTemplate;
	inline static map<int, SpriteList> _spriteListTemplate;
	inline static map<int, SpriteList> _spriteListTemplate_UI;
















	static void LoadResNovice();//リソースをLoadする関数。最初に参照しなければならない
};

