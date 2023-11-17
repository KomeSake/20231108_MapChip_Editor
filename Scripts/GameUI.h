#pragma once
#include <ctime>
#include "LoadRes.h"
#include "MyBase.h"
class GameUI :
	public MyBase
{
public:
	Vector2 _pos;
	float _width, _height;
	unsigned int _color;
protected:
	//UIの描画関数は左上から描画する
	void UITexture(float x, float y, LoadRes::Sprite sprite, unsigned int color);
	void UITexture(float x, float y, map<int, LoadRes::SpriteList> sprite, int index, unsigned int color);
	void UIAnimation(float x, float y, map<int, LoadRes::SpriteList> sprite, float angle, int frameTime, int index);
	//ストップウォッチ(３０番)
	int MyTimers(int milli, int index);
	clock_t _timeStart[31] = { 0 };
	clock_t _timeEnd[31] = { 0 };
	bool _isTimeOpen[31] = { 0 };
	//アニメーションのための変数
	int FrameTimers(int milli, int index);
	int _frameAniIndex[31] = { 0 };//指定したいフレイムからプレイする(例えば、０フレームから)
	clock_t _frame_timeStart[31] = { 0 };
	clock_t _frame_timeEnd[31] = { 0 };
	bool _frame_isTimeOpen[31] = { 0 };
};

class UI_Start :
	public GameUI
{
public:
	bool _isStart;
	UI_Start();
	void UIOpen(char prekeys[], char keys[]);
};

class UI_Game :
	public GameUI
{
public:
	inline static enum MapEditorIndex
	{
		nothing,
		bg1,
		box1,
		bg2,
		box2,
		enemyMother
	}_mapEditorIndex;

	UI_Game();
	void UIOpen(int hp, bool isMapEditor);
};

class UI_GameOver :
	public GameUI
{
public:
	bool _isRestart;//是否重试
	bool _isBackMenu;//是否回到主菜单
	UI_GameOver();
	void UIOpen(Vector2 mousePos, char prekeys[], char keys[]);
};